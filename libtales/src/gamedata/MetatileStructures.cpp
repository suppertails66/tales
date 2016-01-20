#include "gamedata/MetatileStructures.h"
#include "structs/Tmap.h"
#include "structs/Taddress.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"
#include "exception/TGenericException.h"
#include "util/StringConversion.h"
#include <string>
#include <iostream>

namespace Tales {



MetatileStructures::MetatileStructures() { };

/*MetatileStructures::MetatileStructures(
      LoadedROM& rom,
      int address) {
  
} */

MetatileStructures::MetatileStructures(
      LoadedROM& rom,
      const RawLevelHeaders& rawLevelHeaders) {
  
  int tableNum = 0;
  for (AddressRawLevelHeaderMap::const_iterator it = rawLevelHeaders.cbegin();
       it != rawLevelHeaders.cend();
       it++) {
    // Get address of next table to read
    Taddress addr = it->second.metatileStructureAddress();
       
    // Check if we've already read this table
    AddressMetatileStructureIndexMap::iterator checkIterator
      = indexMap_.find(addr);
     
    // Read table if not already read 
    if (checkIterator == indexMap_.end()) {
//      std::cout << "reading structure table at " << addr << std::endl;
//      std::cout << '\t' << "source header address: " << it->first << std::endl;
    
      // Add a new MetatileStructureSet to hold new metatile
      // definitions
      metatileStructureSets_.push_back(MetatileStructureSet());
      
      // Get the target set
      MetatileStructureSet& targetSet
        = metatileStructureSets_[metatileStructureSets_.size() - 1];
    
      // Get base address of table
      Taddress tableBaseAddress = it->second.metatileStructureAddress();
      
      // Some headers for irregular levels -- world map, Tails' House --
      // point to invalid tables for whatever reason, so we check to make
      // sure that the entry is not one of those valid
      if (tableBaseAddress == invalidTableAddress) {
//        std::cout << '\t' << "table is bad: cancelling read" << std::endl;
//        continue;
          // "Move" the table to a new address, where we will later add
          // a proper tileset. This works because the invalid
          // address points to the middle of some bank filler
//          tableBaseAddress = 0x53600;
      }
        
      targetSet.readFromData(rom,
                             addr);
      
      // Get bank number of table address
/*      int tableBankNum = LoadedROM::directToBankNum(tableBaseAddress);
      
      // First address = start of table content
      Taddress tableContentBankedAddress = ByteConversion::fromBytes(
                      rom.directRead(tableBaseAddress),
                      ByteSizes::uint16Size,
                      EndiannessTypes::little,
                      SignednessTypes::nosign);
      
      // Convert banked address to direct
      Taddress tableContentAddress = LoadedROM::getDirectAddress(
                                  tableBankNum,
                                  tableContentBankedAddress);
                                  
      // Calculate number of entries in table (size of index divided by
      // bytes per index entry)
      int numTableEntries =
        (tableContentAddress - tableBaseAddress) / ByteSizes::uint16Size;
        
      // Due to FUCKING SHIT, the tiles structures are not in the same order
      // as the indices. Thus we now have to somehow keep a map of everything.
      
      // Read each tile in table
      for (int i = 0; i < numTableEntries; i++) {
        // Get address of current metatile definition
        Taddress metatileAddress
          = tableContentAddress + (i * bytesPerMetatile);
        
        // Get raw VRAM references for each corner of the metatile
        
        unsigned int upperLeft = ByteConversion::fromBytes(
                        rom.directRead(metatileAddress + 0),
                        ByteSizes::uint16Size,
                        EndiannessTypes::little,
                        SignednessTypes::nosign);
        
        unsigned int upperRight = ByteConversion::fromBytes(
                        rom.directRead(metatileAddress + 2),
                        ByteSizes::uint16Size,
                        EndiannessTypes::little,
                        SignednessTypes::nosign);
        
        unsigned int lowerLeft = ByteConversion::fromBytes(
                        rom.directRead(metatileAddress + 4),
                        ByteSizes::uint16Size,
                        EndiannessTypes::little,
                        SignednessTypes::nosign);
        
        unsigned int lowerRight = ByteConversion::fromBytes(
                        rom.directRead(metatileAddress + 6),
                        ByteSizes::uint16Size,
                        EndiannessTypes::little,
                        SignednessTypes::nosign);
        
        // Create metatile and add to set
        targetSet.push_back(MetatileStructure(
                                  upperLeft,
                                  upperRight,
                                  lowerLeft,
                                  lowerRight));
      } */
      
//      std::cout << '\t' << "size: " << targetSet.size() << std::endl;
      
      // Mark table as read
      indexMap_.insert(AddressMetatileStructureIndexPair(
          tableBaseAddress,
          tableNum));
      ++tableNum;
    }
  }
}

int MetatileStructures::indexOfAddress(Taddress address) const {
  return indexMap_.findOrThrow(address)->second;
}

MetatileStructureSet& MetatileStructures::metatileStructureSet(
      int index){
  // Throw if index out of range
  if ((unsigned int)index >= metatileStructureSets_.size()) {
    throw TGenericException(TALES_SRCANDLINE,
                           "MetatileStructures::metatileStructureSet"
                           "(int)",
                           std::string("Out of range index: ")
                           + StringConversion::toString(index));
  }
      
  return metatileStructureSets_[index];
}

const MetatileStructureSet&
    MetatileStructures::metatileStructureSet(int index) const {
  // Throw if index out of range
  if ((unsigned int)index >= metatileStructureSets_.size()) {
    throw TGenericException(TALES_SRCANDLINE,
                           "MetatileStructures::metatileStructureSet"
                           "(int)",
                           std::string("Out of range index: ")
                           + StringConversion::toString(index));
  }
  
  return metatileStructureSets_[index];
}

void MetatileStructures::save(std::string& data) {
  // Output buffer
  char outbuffer[ByteSizes::uint64Size];
  
  // Write structure tables
  
  // Write number of structure tables
  ByteConversion::toBytes(metatileStructureSets_.size(),
                          outbuffer,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string(outbuffer, ByteSizes::uint16Size);

  // Write each structure table
//  int num = 0;
  for (MetatileStructureTableCollection::iterator it
          = metatileStructureSets_.begin();
       it != metatileStructureSets_.end();
       it++) {
//    std::cerr << "set " << num << std::endl;
//    ++num;
    
    // Get the structure collection
    MetatileStructureSet& metatiles = *it;
    
    // Save the set
    metatiles.save(data);
    
    // Write number of metatiles in collection
/*    ByteConversion::toBytes(metatiles.size(),
                            outbuffer,
                            ByteSizes::uint16Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    data += std::string(outbuffer, ByteSizes::uint16Size);
    
    // Write each metatile structure in collection
    for (MetatileStructureSet::iterator jt = metatiles.begin();
         jt != metatiles.end();
         jt++) {
      Tbyte outtiles[MetatileStructure::dataSize];
      jt->writeToData(outtiles);
      data += std::string((char*)outtiles,
                          MetatileStructure::dataSize);
    } */
  }
  
  // Write index table
  
  // Write number of entries
  ByteConversion::toBytes(indexMap_.size(),
                          outbuffer,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string(outbuffer, ByteSizes::uint16Size);
  
  // Write each entry
  for (AddressMetatileStructureIndexMap::iterator it = indexMap_.begin();
       it != indexMap_.end();
       it++) {
    
    // Write address
    ByteConversion::toBytes(it->first,
                            outbuffer,
                            ByteSizes::uint32Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    data += std::string(outbuffer, ByteSizes::uint32Size);
    
    // Write index
    ByteConversion::toBytes(it->second,
                            outbuffer,
                            ByteSizes::uint32Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    data += std::string(outbuffer, ByteSizes::uint32Size);
    
  }
}

int MetatileStructures::load(const Tbyte* data) {
  // Count of read bytes
  int byteCount = 0;
  
  // Read metatile structure tables
  
  // Destroy existing data
  indexMap_.clear();
  metatileStructureSets_.clear();
  
  // Get number of structure tables
  int numStructureTables = ByteConversion::fromBytes(
                              data + byteCount,
                              ByteSizes::uint16Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign);
  byteCount += ByteSizes::uint16Size;
   
  // Read each structure table
  for (int i = 0; i < numStructureTables; i++) {
    // Add set
    metatileStructureSets_.push_back(MetatileStructureSet());
    
    // Get added set
    MetatileStructureSet& metatiles = metatileStructureSets_[
        metatileStructureSets_.size() - 1];
        
    // Load set
    byteCount += metatiles.load(data + byteCount);
    
    // Get number of tiles in set
/*    int numMetatiles = ByteConversion::fromBytes(
                              data + byteCount,
                              ByteSizes::uint16Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign);
    byteCount += ByteSizes::uint16Size;
    
    for (int j = 0; j < numMetatiles; j++) {
      // Create metatile
      MetatileStructure metatile;
      
      // Read structure
      metatile.readFromData(data + byteCount);
      byteCount += MetatileStructure::dataSize;
      
      // Add to set
      metatiles.push_back(metatile);
    } */
  }
  
  // Read index table
  
  // Get number of entries
  int numIndexEntries = ByteConversion::fromBytes(
                              data + byteCount,
                              ByteSizes::uint16Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign);
  byteCount += ByteSizes::uint16Size;
  
  // Read each entry
  for (int i = 0; i < numIndexEntries; i++) {
    // Read address
    int address = ByteConversion::fromBytes(
                                data + byteCount,
                                ByteSizes::uint32Size,
                                EndiannessTypes::little,
                                SignednessTypes::nosign);
    byteCount += ByteSizes::uint32Size;
    
    // Read index
    int index = ByteConversion::fromBytes(
                                data + byteCount,
                                ByteSizes::uint32Size,
                                EndiannessTypes::little,
                                SignednessTypes::nosign);
    byteCount += ByteSizes::uint32Size;
    
    // Insert into map
    indexMap_.insert(AddressMetatileStructureIndexPair(
        address, index));
  }
  
  return byteCount;
}

void MetatileStructures::exportToROM(WritableROM& rom) {
  // Write each structure table
  for (AddressMetatileStructureIndexMap::iterator it = indexMap_.begin();
       it != indexMap_.end();
       it++) {
    // Throw if index out of range
    if ((unsigned int)(it->second) >= metatileStructureSets_.size()) {
      throw TGenericException(TALES_SRCANDLINE,
                             "MetatileStructures::exportToROM"
                             "(WritableROM&)",
                             std::string("Out of range index: ")
                             + StringConversion::toString(it->second));
    }
       
    // Get structure table at index
    MetatileStructureSet& metatiles
      = metatileStructureSets_[it->second];
    
    metatiles.exportToROM(rom);
    
    // Write each metatile structure
/*    int metatileNum = 0;
    for (MetatileStructureSet::iterator jt = metatiles.begin();
         jt != metatiles.end();
         jt++) {
      // Get base address of table content
      Taddress address = it->first
        + (metatiles.size() * ByteSizes::uint16Size);
      
      // Add data position of metatile to address
      address += (metatileNum * MetatileStructure::dataSize);
      
      // Create buffer to hold data
      Tbyte output[MetatileStructure::dataSize];
      
      // Write to buffer
      jt->writeToData(output);
      
      // Write to ROM
      rom.directWrite(address,
                      output,
                      MetatileStructure::dataSize);
      
      // Move to next metatile
      ++metatileNum;
    }
    std::cout << metatileNum << std::endl; */
  }
  
}

int MetatileStructures::indexOfInitialAddress(
    Taddress initialAddress) const {
  // Check for invalid map
/*  if (initialAddress == invalidTableAddress) {
    // just return "default" value and worry about it later
    // TODO: worry about it
    return 0;
  } */
  
  return indexMap_.findOrThrow(initialAddress)->second;
}

int MetatileStructures::size() const {
  return metatileStructureSets_.size();
}


}; 
