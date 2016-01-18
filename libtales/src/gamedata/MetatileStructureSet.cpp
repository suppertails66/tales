#include "gamedata/MetatileStructureSet.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"
#include "util/StringConversion.h"
#include "exception/TGenericException.h"
#include <iostream>

using namespace Luncheon;

namespace Tales {


MetatileStructureSet::MetatileStructureSet()
  : address_(0) { };

MetatileStructureSet::MetatileStructureSet(
                                 LoadedROM& rom,
                                 Taddress address__)
  : address_(0) {
  readFromData(rom,
               address__);
}
  
int MetatileStructureSet::readFromData(LoadedROM& rom,
                                               Taddress address__) {
  address_ = address__;
  
  // Count of read bytes
  int byteCount = 0;
                                               
  // Get bank number of the table
  int tableBankNum = LoadedROM::directToBankNum(address__);
  
  // Compute table size.
  // The first address in the index always points to the first
  // structure definition
  Taddress contentStartBankedAddress = ByteConversion::fromBytes(
        rom.directRead(address__),
        ByteSizes::uint16Size,
        EndiannessTypes::little,
        SignednessTypes::nosign);
  
  // Convert to direct address
  Taddress contentStartAddress = 0;
  if (contentStartBankedAddress == invalidStructureToken) {
    contentStartAddress = invalidRepairAddress;
  }
  else {
    contentStartAddress = LoadedROM::getDirectAddress(
                                              tableBankNum,
                                              contentStartBankedAddress);
  }
  
  // Get size of index, given by ((tableStart - indexStart) / entrySize)
  int indexEntries = (contentStartAddress - address__) / ByteSizes::uint16Size;
  
  // Read the index.
  // Remember the highest index we encounter
  int highestIndex = 0;
  for (int i = 0; i < indexEntries; i++) {
    // Get banked address
    Taddress entryBankedAddress = ByteConversion::fromBytes(
          rom.directRead(address__ + (i * ByteSizes::uint16Size)),
          ByteSizes::uint16Size,
          EndiannessTypes::little,
          SignednessTypes::nosign);
    byteCount += ByteSizes::uint16Size;
    
    // Convert to direct address
    int entryAddress = 0;
    // If address is invalid, repair
    if (entryBankedAddress == invalidStructureToken) {
//      std::cout << contentStartAddress << std::endl;
      entryAddress = invalidRepairAddress
                             + (i * MetatileStructure::dataSize);
    }
    else {
      entryAddress = LoadedROM::getDirectAddress(
                                        tableBankNum,
                                        entryBankedAddress);
    }
    
    // Compute the actual index this address corresponds to
    int structureIndex = (entryAddress - contentStartAddress)
          / MetatileStructure::dataSize;
    
    // Add mapping to index map
    index_.insert(MetatileIndexToStructurePair(i, structureIndex));
    
    if (structureIndex > highestIndex) {
      highestIndex = structureIndex;
    }
  }
  
  // Increment highest index (we're using it as a limit for the read loop)
  ++highestIndex;
  
  // Read the structure definitions.
  // The highest index indicates the actual number of structure definitions
  // in the table
  for (int i = 0; i < highestIndex; i++) {
    // Read each metatile
    MetatileStructure metatile;
    metatile.readFromData(rom.directRead(contentStartAddress
                            + (i * MetatileStructure::dataSize)));
    
    // If reading invalid table, repair tiles
    if (contentStartAddress == invalidRepairAddress) {
//      std::cout << highestIndex << std::endl;
      metatile.upperLeft() = TileReference(invalidRepairTile);
      metatile.upperRight() = TileReference(invalidRepairTile);
      metatile.lowerLeft() = TileReference(invalidRepairTile);
      metatile.lowerRight() = TileReference(invalidRepairTile);
    }
    
    // Add to content
    primaryStorage_.push_back(metatile);
    
    byteCount += MetatileStructure::dataSize;
  }
  
  // HACK: (sort of) Add dummy entries to fill rest of set.
  // This fixes issues that I think are caused by out-of-range
  // values in the index.
//  while (primaryStorage_.size() < 256) {
//    primaryStorage_.push_back(MetatileStructure());
//  }
  
  return byteCount;
}

void MetatileStructureSet::save(std::string& data) {
  // Write buffer
  char buffer[ByteSizes::uint32Size];

  // Write start address
  ByteConversion::toBytes(address_,
                          buffer,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string(buffer, ByteSizes::uint32Size);

  // Write number of index entries
  ByteConversion::toBytes(index_.size(),
                          buffer,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string(buffer, ByteSizes::uint16Size);
  
//  std::cerr << '\t' << index_.size() << std::endl;
  
  // Write each index entry
  for (MetatileIndexToStructureMap::iterator it = index_.begin();
       it != index_.end();
       it++) {
    // Write index number
    ByteConversion::toBytes(it->first,
                            buffer,
                            ByteSizes::uint16Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    data += std::string(buffer, ByteSizes::uint16Size);
    
    // Write structure index
    ByteConversion::toBytes(it->second,
                            buffer,
                            ByteSizes::uint16Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    data += std::string(buffer, ByteSizes::uint16Size);
    
//    std::cerr << '\t' << it->first << " " << it->second << std::endl;
  }
  
  // Write number of metatile structure definitions
  ByteConversion::toBytes(primaryStorage_.size(),
                          buffer,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string(buffer, ByteSizes::uint16Size);
  
//  std::cout << primaryStorage_.size() << std::endl;
  
  // Write metatile structure definitions
//  int num = 0;
  for (MetatileStructureCollection::iterator it = primaryStorage_.begin();
       it != primaryStorage_.end();
       it++) {
 //   std::cerr << "\ttile " << num << std::endl;
//    ++num;
    
    // Write definition to data
    Tbyte metatile[MetatileStructure::dataSize];
    it->writeToData(metatile);
    
    // Write to string
    data += std::string((char*)metatile, MetatileStructure::dataSize);
  }
}
  
int MetatileStructureSet::load(const Tbyte* data) {
  // Count of bytes written
  int byteCount = 0;
  
  // Clear existing storage
  primaryStorage_.clear();
  index_.clear();
  
  // Read start address
  address_ = ByteConversion::fromBytes(data + byteCount,
                                       ByteSizes::uint32Size,
                                       EndiannessTypes::little,
                                       SignednessTypes::nosign);
  byteCount += ByteSizes::uint32Size;
  
  // Read number of index entries
  int numIndexEntries = ByteConversion::fromBytes(data + byteCount,
                                                  ByteSizes::uint16Size,
                                                  EndiannessTypes::little,
                                                  SignednessTypes::nosign);
  byteCount += ByteSizes::uint16Size;
  
  // Read index entries
  for (int i = 0; i < numIndexEntries; i++) {
    // Read index number
    int indexNum = ByteConversion::fromBytes(data + byteCount,
                                             ByteSizes::uint16Size,
                                             EndiannessTypes::little,
                                             SignednessTypes::nosign);
    byteCount += ByteSizes::uint16Size;
  
    // Read mapping
    int structureNum = ByteConversion::fromBytes(data + byteCount,
                                             ByteSizes::uint16Size,
                                             EndiannessTypes::little,
                                             SignednessTypes::nosign);
    byteCount += ByteSizes::uint16Size;
    
    // Add to index
    index_.insert(MetatileIndexToStructurePair(indexNum,
                                               structureNum));
  }
  
  // Read number of metatile structure definitions
  int numStructureEntries = ByteConversion::fromBytes(
                                                  data + byteCount,
                                                  ByteSizes::uint16Size,
                                                  EndiannessTypes::little,
                                                  SignednessTypes::nosign);
  byteCount += ByteSizes::uint16Size;
  
//  std::cout << numStructureEntries << std::endl;
  
  // Read metatile structure definitions
  for (int i = 0; i < numStructureEntries; i++) {
    // Read structure definition
    MetatileStructure metatile;
    metatile.readFromData(data + byteCount);
    
    // Add to count
    byteCount += MetatileStructure::dataSize;
    
    // Add structure definition to table
    primaryStorage_.push_back(metatile);
  }
  
  // Add dummy entries to fill up set
//  while (primaryStorage_.size() < 256) {
//    primaryStorage_.push_back(MetatileStructure());
//  }

  return byteCount;
}
  
void MetatileStructureSet::exportToROM(WritableROM& rom) {
  // TODO: support for adding metatile definitions
  // search freespace &c
  
  int writeAddress = address_;
  
//  std::cout << "addr: " << writeAddress << std::endl;
  
  // Starting address of structure definitions
  int contentStartAddress = writeAddress
        + (index_.size() * ByteSizes::uint16Size);

  // Write the index
  for (MetatileIndexToStructureMap::iterator it = index_.begin();
       it != index_.end();
       it++) {
    int contentIndex = it->second;
    
    // Compute the address of the content
    Taddress contentAddress = (contentStartAddress 
                  + (contentIndex * MetatileStructure::dataSize));
    
    // Convert to banked address
    Taddress contentBankedAddress = LoadedROM
          ::directToBankedAddress(contentAddress);
    
    // Write to index
    Tbyte buffer[ByteSizes::uint16Size];
    ByteConversion::toBytes(contentBankedAddress,
                            buffer,
                            ByteSizes::uint16Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    rom.directWrite(writeAddress + (it->first * ByteSizes::uint16Size),
                    buffer,
                    ByteSizes::uint16Size);
  }
  
  // Write content
  int metatileNum = 0;
  for (MetatileStructureCollection::iterator it = primaryStorage_.begin();
       it != primaryStorage_.end();
       it++) {
    // Write metatile to buffer
    Tbyte buffer[MetatileStructure::dataSize];
    it->writeToData(buffer);
    // Write buffer to table
    rom.directWrite(contentStartAddress
                      + (metatileNum * MetatileStructure::dataSize),
                    buffer,
                    MetatileStructure::dataSize);
    ++metatileNum;
  }
  
//  std::cout << "metatiles: " << metatileNum << std::endl;
//  std::cout << std::endl;
}
  
int MetatileStructureSet::numMetatileMappings() const {
  return index_.size();
}

MetatileStructure& MetatileStructureSet
      ::metatileMapping(int indexNum) {
  // Throw if out of range
  if ((unsigned int)(indexNum) >= index_.size()) {
    throw TGenericException(TALES_SRCANDLINE,
                           "MetatileStructureSet::metatileMapping("
                           "int)",
                           std::string("Out of range index: ")
                             + StringConversion::toString(indexNum));
  }
  
  MetatileIndexToStructureMap::iterator it = index_.findOrThrow(indexNum);
  
  return primaryStorage_[it->second];
}

const MetatileStructure& MetatileStructureSet
      ::metatileMapping(int indexNum) const {
  // Throw if out of range
  if ((unsigned int)(indexNum) >= index_.size()) {
    throw TGenericException(TALES_SRCANDLINE,
                           "MetatileStructureSet::metatileMapping("
                           "int) const",
                           std::string("Out of range index: ")
                             + StringConversion::toString(indexNum));
  }
  
  MetatileIndexToStructureMap::const_iterator it
    = index_.findOrThrow(indexNum);
  
  return primaryStorage_[it->second];
}

MetatileStructureCollection::iterator MetatileStructureSet
    ::metatileStructuresBegin() {
  return primaryStorage_.begin();
}

MetatileStructureCollection::iterator MetatileStructureSet
    ::metatileStructuresEnd() {
  return primaryStorage_.end();
}

MetatileStructureCollection::const_iterator MetatileStructureSet
    ::metatileStructuresCbegin() const {
  return primaryStorage_.cbegin();
}

MetatileStructureCollection::const_iterator MetatileStructureSet
    ::metatileStructuresCend() const {
  return primaryStorage_.cend();
}
  
Taddress MetatileStructureSet::address() const {
  return address_;
}
  
MetatileStructure& MetatileStructureSet
    ::operator[](int tileNum) {
  return metatileMapping(tileNum);
}
  
int MetatileStructureSet::size() const {
  return primaryStorage_.size();
}


};
