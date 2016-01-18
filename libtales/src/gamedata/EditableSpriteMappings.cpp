#include "gamedata/EditableSpriteMappings.h"
#include "exception/UnrecognizedVersionException.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"
#include <iostream>

using namespace Luncheon;

namespace Tales {


EditableSpriteMappings::EditableSpriteMappings()
  : mappingTableAddress_(0),
    numObjects_(0) { };

EditableSpriteMappings::EditableSpriteMappings(
                         LoadedROM& rom,
                         Taddress mappingTableAddress__,
                         int numObjects__)
  : mappingTableAddress_(mappingTableAddress__),
    numObjects_(numObjects__) {
  int byteCount = 0;
  
  // Get bank number of mapping table
  int mappingTableBankNum = LoadedROM::directToBankNum(mappingTableAddress__);
  
  ObjectIDToMappingAddresses objectIDToMappingAddresses;
  
  // Read all object addresses
  MappingTableAddressCollection mappingTableAddresses;
//  ObjectIDToAddress objectIDToAddress;
  for (int i = 0; i < numObjects__; i++) {
    Taddress bankedAddress = ByteConversion::fromBytes(
                              rom.directRead(mappingTableAddress__
                                                + byteCount),
                              ByteSizes::uint16Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign);
    byteCount += ByteSizes::uint16Size;
    
    // Convert banked to direct address
    Taddress address = LoadedROM::getDirectAddress(
                                mappingTableBankNum,
                                bankedAddress);
    
    // Add to storage
    mappingTableAddresses.push_back(address);
    
    objectIDToMappingAddresses.push_back(MappingAddressCollection());
//    objectIDToAddress.push_back(address);
    
//    std::cout << std::hex << i << ": " << address << std::endl;
  }
  
  // Create mapping of addresses to heuristically determined number of
  // spritestates
  MappingTableAddressToSize addressToSubtableEntries;
//  Tmap<Taddress, int> addressToObjectID;
  Tmap<Taddress, std::vector<int> > addressToObjectIDs;
  for (int i = 0; i < mappingTableAddresses.size(); i++) {
    int subtableSize = 0;
    int numSubtableEntries = 0;
    
//    std::cout << "obj id: " << std::hex << i << std::endl;
  
    if (i + 1 == mappingTableAddresses.size()) {
      // If at last entry of table, treat as having zero entries (we can
      // get away with this because there happen to be several unused
      // entries at the end of the table)
    }
    else {
      // Size of subtable = difference between the next entry's address
      // and this one
      subtableSize = mappingTableAddresses[i + 1]
                      - mappingTableAddresses[i];
                      
      // Number of entries = total size / number of bytes per address
//      numSubtableEntries = subtableSize / ByteSizes::uint16Size;
      
//      if (numSubtableEntries > 0) {
      // Unfortunately for us, sprite mappings are interspersed with table
      // indices, so this approach doesn't work. Instead, we have to try
      // to guess where the entries end by looking for an invalid address.
//      for (int j = 0; j < numSubtableEntries; j++) {

      // Loop for up to 0x100 addresses (we'll break once a bad one is found)
      int count = 0;
      while (count <= 0x100) {
        Taddress bankedAddress = ByteConversion::fromBytes(
                              rom.directRead(mappingTableAddresses[i]
                                              + (count * ByteSizes::uint16Size)),
                              ByteSizes::uint16Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign);
        
        // Invalid addresses are outside of 0x8000-0xBFFF range
        if ((bankedAddress < LoadedROM::slot2StartAddress)
            || (bankedAddress >= (LoadedROM::slot2StartAddress
                                    + LoadedROM::bankSize))) {
//          std::cout << "\taddr: " << mappingTableAddresses[i] << std::endl;
//          std::cout << "\tterminate: " << bankedAddress << std::endl;
          numSubtableEntries = count;
//          std::cout << "\tentries: " << numSubtableEntries << std::endl;
          break;
        }
        else {
          ++count;
        }
      }
//      }
      
    }
    
//    std::cout << numSubtableEntries << std::endl;

//    addressToObjectID.insert(
//      Tmap<Taddress, int>::PairType(
//        mappingTableAddresses[i],
//        i));
        
    addressToObjectIDs.insert(
         Tmap<Taddress, std::vector<int> >::PairType(
            mappingTableAddresses[i],
            std::vector<int>()));
    addressToObjectIDs.findValueOrThrow(mappingTableAddresses[i])
      .push_back(i);
        
      
    // If number of entries invalid, don't insert
    if (numSubtableEntries <= 0) {
      
      continue;
    }
    else {
      if (!(addressToSubtableEntries.insert(
            MappingTableAddressToSize::PairType(
              mappingTableAddresses[i],
              numSubtableEntries))).second) {
//          std::cout << std::hex << '\t' << i << ": "
//            << mappingTableAddresses[i]
//              << " " << numSubtableEntries << std::endl;
      }
      else {
        
      }
    }
  }
  
  AddressToRawMapping addressToRawMapping;
  for (MappingTableAddressToSize::iterator it
         = addressToSubtableEntries.begin();
       it != addressToSubtableEntries.end();
       it++) {
//    std::cout << std::hex << it->first << " " << it->second << std::endl;
    
//    std::cout << "address: " << it->first << std::endl;
//    std::cout << "\tsize: " << it->second << std::endl;

    Taddress tableAddress = it->first;
//    std::cout << std::hex << tableAddress << std::endl;
    for (int i = 0; i < it->second; i++) {
      Taddress readBankedAddress = ByteConversion::fromBytes(
                              rom.directRead(tableAddress),
                              ByteSizes::uint16Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign);
      
      Taddress readAddress = LoadedROM::getDirectAddress(
                                      mappingTableBankNum,
                                      readBankedAddress);
                                      
//      std::cout << std::hex << readAddress << std::endl;
    
      // Read raw mapping
      RawSpriteMapping mapping(rom.directRead(readAddress));
      
      if (!(addressToRawMapping.insert(
              AddressToRawMapping::PairType(
                readAddress,
                mapping))).second) {
//        std::cout << "bad: " << '\n';
//        std::cout << "\tRead address: " << readAddress << std::endl;
//        std::cout << "\tTable address: " << tableAddress << std::endl;
      }
      else {
//        std::cout << "good: " << readAddress << std::endl;

//          objectIDToMappingAddresses[
//            addressToObjectID.findValueOrThrow(it->first)]
//              .push_back(readAddress);
              
          std::vector<int> indices
            = addressToObjectIDs.findValueOrThrow(it->first);
          for (int j = 0; j < indices.size(); j++) {
            objectIDToMappingAddresses[indices[j]].push_back(readAddress);
          }
      }
      
      tableAddress += ByteSizes::uint16Size;
    }
    
    // Every sprite mapping is uniquely defined (except for the invalid
    // zero-sprite mappings used for certain entries), so we can safely
    // tie them together in our representation
    
  }
  
  // Produce maps for coordinate and tile index tables.
  // Multiple mappings can and do cite the same table, so these must
  // be stored separately from the mappings themselves (at least until
  // full exporting is implemented).
  
  // Maps of addresses to table sizes
  CoordinateTableAddressToSize addressToCoordinateSize;
  TileIndexTableAddressToSize addressToTileIndexSize;
  for (AddressToRawMapping::iterator it = addressToRawMapping.begin();
       it != addressToRawMapping.end();
       it++) {
/*    std::cout << std::hex << it->first << " " << std::endl;
    std::cout << '\t' << "numSprites: "
      << it->second.numSprites() << std::endl;
    std::cout << '\t' << "collisionXLength: "
      << it->second.collisionXLength() << std::endl;
    std::cout << '\t' << "collisionYLength: "
      << it->second.collisionYLength() << std::endl;
    std::cout << '\t' << "coordinateTableBankedAddress: "
      << it->second.coordinateTableBankedAddress() << std::endl;
    std::cout << '\t' << "offsetY: "
      << it->second.offsetY() << std::endl;
    std::cout << '\t' << "offsetX: "
      << it->second.offsetX() << std::endl;
    std::cout << '\t' << "tileIndexTableBankedAddress: "
      << it->second.tileIndexTableBankedAddress() << std::endl; */
      
    Taddress coordinateBankedAddress
      = it->second.coordinateTableBankedAddress();
    Taddress tileIndexBankedAddress
      = it->second.tileIndexTableBankedAddress();
      
    Taddress coordinateAddress = LoadedROM::getDirectAddress(
                                      mappingTableBankNum,
                                      coordinateBankedAddress);
    Taddress tileIndexAddress = LoadedROM::getDirectAddress(
                                      mappingTableBankNum,
                                      tileIndexBankedAddress);
    
    int tableSizes = it->second.numSprites();
    
    // Insert coordinates into map
    std::pair<CoordinateTableAddressToSize::iterator,
              bool> coordinateStruct = addressToCoordinateSize.insert(
          CoordinateTableAddressToSize::PairType(
            coordinateAddress,
            tableSizes));
    if (!(coordinateStruct.second)) {
      // If the insert failed (due to an existing map to this address),
      // and the table size is larger than
      // the currently mapped size, increase the mapped value
      // to the new one (to ensure we get the full table and not
      // a subset used by some particular sprite mapping)
      if (tableSizes > coordinateStruct.first->second) {
        coordinateStruct.first->second = tableSizes;
      }
    }
    
    // Repeat for tile index
    std::pair<TileIndexTableAddressToSize::iterator,
              bool> tileIndexStruct = addressToTileIndexSize.insert(
          TileIndexTableAddressToSize::PairType(
            tileIndexAddress,
            tableSizes));
    if (!(tileIndexStruct.second)) {
      if (tableSizes > tileIndexStruct.first->second) {
        tileIndexStruct.first->second = tableSizes;
      }
    }
  }
  
  // Read coordinate tables to primary storage
  Tmap<Taddress, int> coordAddrToIndex;
  for (CoordinateTableAddressToSize::iterator it
         = addressToCoordinateSize.begin();
       it != addressToCoordinateSize.end();
       it++) {
    // Read table
    SpriteMappingCoordinateTable table;
    table.readFromData(rom.directRead(it->first),
                       it->second);
                       
    // Read flipped table
    SpriteMappingCoordinateTable flippedTable;
    flippedTable.readFromData(rom.directRead(it->first + offsetToHorizontalFlip),
                       it->second);
                       
    // Map index to address
    coordinateTableIndexToAddress_.insert(
      CoordinateTableIndexToAddress::PairType(
        spriteMappingCoordinateTables_.size(),
        it->first));
    
    coordAddrToIndex.insert(
      Tmap<Taddress, int>::PairType(
        it->first,
        spriteMappingCoordinateTables_.size()));
                       
    // Add to primary storage
    spriteMappingCoordinateTables_.push_back(table);
    spriteMappingFlipCoordinateTables_.push_back(flippedTable);
  }
  
  // Read tile index tables to primary storage
  Tmap<Taddress, int> tileindAddrToIndex;
  for (TileIndexTableAddressToSize::iterator it
         = addressToTileIndexSize.begin();
       it != addressToTileIndexSize.end();
       it++) {
    // Read table
    SpriteMappingTileIndexTable table;
    table.readFromData(rom.directRead(it->first),
                       it->second);
                       
    // Map index to address
    tileIndexTableIndexToAddress_.insert(
      TileIndexTableIndexToAddress::PairType(
        spriteMappingTileIndexTables_.size(),
        it->first));
    
    tileindAddrToIndex.insert(
      Tmap<Taddress, int>::PairType(
        it->first,
        spriteMappingTileIndexTables_.size()));
                       
    // Add to primary storage
    spriteMappingTileIndexTables_.push_back(table);
  }
  
  // Convert raw sprite mappings to regular (indexed)
  MappingTableAddressToIndex mappingAddressToIndex;
  for (AddressToRawMapping::iterator it = addressToRawMapping.begin();
       it != addressToRawMapping.end();
       it++) {
    // Map index to address
    mappingIndexToAddress_.insert(
      MappingIndexToAddress::PairType(
        spriteMappings_.size(),
        it->first));
        
    // Temporarily map address to index
    mappingAddressToIndex.insert(
      MappingTableAddressToIndex::PairType(
        it->first,
        spriteMappings_.size()));
    
    // Compute corresponding direct addresses of banked addresses
    Taddress coordinateAddress
      = LoadedROM::getDirectAddress(mappingTableBankNum,
                                    it->second.coordinateTableBankedAddress());
    Taddress tileIndexAddress
      = LoadedROM::getDirectAddress(mappingTableBankNum,
                                    it->second.tileIndexTableBankedAddress());
        
    SpriteMapping mapping(it->second.numSprites(),
                          it->second.collisionXLength(),
                          it->second.collisionYLength(),
                          coordAddrToIndex.findValueOrThrow(
                            coordinateAddress),
                          it->second.offsetX(),
                          it->second.offsetY(),
                          tileindAddrToIndex.findValueOrThrow(
                            tileIndexAddress));
                       
    // Add to primary storage
    spriteMappings_.push_back(mapping);
  }
  
  for (int i = 0; i < numObjects_; i++) {
    objectIDToMappingIndices_.push_back(MappingIndexCollection());
    
    for (int j = 0; j < objectIDToMappingAddresses[i].size(); j++) {
      objectIDToMappingIndices_[i].push_back(
        mappingAddressToIndex.findValueOrThrow(
          objectIDToMappingAddresses[i][j]));
    }
  }
  
  // Map object IDs to indices
/*  for (int i = 0; i < numObjects__; i++) {
     Taddress addr = objectIDToAddress[i];
     
     mappingsByID_.push_back(
       mappingAddressToIndex.findValueOrThrow(
         addr));
  } */
}

void EditableSpriteMappings::save(std::string& data) {
  Tbyte buffer[ByteSizes::uint32Size];
  SaveHelper saver(data,
                   DataChunkIDs::spriteMappings,
                   0);
  
  ByteConversion::toBytes(mappingTableAddress_,
                          buffer,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint32Size);
  
  ByteConversion::toBytes(numObjects_,
                          buffer,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint32Size);
  
  // Save sprite mappings count
  ByteConversion::toBytes(spriteMappings_.size(),
                          buffer,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint16Size);
  
  // Save data
  for (int i = 0; i < spriteMappings_.size(); i++) {
    spriteMappings_[i].save(data);
  }
  
  // Save index->address map
  for (MappingIndexToAddress::iterator it
         = mappingIndexToAddress_.begin();
       it != mappingIndexToAddress_.end();
       it++) {
    ByteConversion::toBytes(it->first,
                            buffer,
                            ByteSizes::uint32Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    data += std::string((char*)buffer, ByteSizes::uint32Size);
    
    ByteConversion::toBytes(it->second,
                            buffer,
                            ByteSizes::uint32Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    data += std::string((char*)buffer, ByteSizes::uint32Size);
  }
  
  // Save coordinate tables count
  ByteConversion::toBytes(spriteMappingCoordinateTables_.size(),
                          buffer,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint16Size);
  
  // Save data
  for (int i = 0; i < spriteMappingCoordinateTables_.size(); i++) {
    spriteMappingCoordinateTables_[i].save(data);
  }
  
  for (int i = 0; i < spriteMappingFlipCoordinateTables_.size(); i++) {
    spriteMappingFlipCoordinateTables_[i].save(data);
  }
  
  // Save index->address map
  for (CoordinateTableIndexToAddress::iterator it
         = coordinateTableIndexToAddress_.begin();
       it != coordinateTableIndexToAddress_.end();
       it++) {
    ByteConversion::toBytes(it->first,
                            buffer,
                            ByteSizes::uint32Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    data += std::string((char*)buffer, ByteSizes::uint32Size);
    
    ByteConversion::toBytes(it->second,
                            buffer,
                            ByteSizes::uint32Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    data += std::string((char*)buffer, ByteSizes::uint32Size);
  }
  
  // Save tile index map
  ByteConversion::toBytes(spriteMappingTileIndexTables_.size(),
                          buffer,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint16Size);
  
  // Save data
  for (int i = 0; i < spriteMappingTileIndexTables_.size(); i++) {
    spriteMappingTileIndexTables_[i].save(data);
  }
  
  // Save index->address map
  for (TileIndexTableIndexToAddress::iterator it
         = tileIndexTableIndexToAddress_.begin();
       it != tileIndexTableIndexToAddress_.end();
       it++) {
    ByteConversion::toBytes(it->first,
                            buffer,
                            ByteSizes::uint32Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    data += std::string((char*)buffer, ByteSizes::uint32Size);
    
    ByteConversion::toBytes(it->second,
                            buffer,
                            ByteSizes::uint32Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    data += std::string((char*)buffer, ByteSizes::uint32Size);
  }
  
  for (int i = 0; i < numObjects_; i++) {
    ByteConversion::toBytes(objectIDToMappingIndices_[i].size(),
                            buffer,
                            ByteSizes::uint32Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    data += std::string((char*)buffer, ByteSizes::uint32Size);
    
    for (int j = 0; j < objectIDToMappingIndices_[i].size(); j++) {
      ByteConversion::toBytes(objectIDToMappingIndices_[i][j],
                              buffer,
                              ByteSizes::uint32Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign);
      data += std::string((char*)buffer, ByteSizes::uint32Size);
    }
  }
  
  saver.finalize();
}

int EditableSpriteMappings::load(const Tbyte* data) {
  spriteMappings_.clear();
  spriteMappingCoordinateTables_.clear();
  spriteMappingFlipCoordinateTables_.clear();
  spriteMappingTileIndexTables_.clear();
  mappingIndexToAddress_.clear();
  coordinateTableIndexToAddress_.clear();
  tileIndexTableIndexToAddress_.clear();
//  mappingsByID_.clear();
  objectIDToMappingIndices_.clear();
  int byteCount = 0;
  LoadHelper loader(data,
                    byteCount);
                    
  if (loader.version() > 0) {
    throw UnrecognizedVersionException(TALES_SRCANDLINE,
                                       "EditableSpriteMappings::load("
                                       "const Tbyte*)",
                                       DataChunkIDs::spriteMappings,
                                       "EditableSpriteMappings",
                                       loader.version(),
                                       0);
  }
  
  mappingTableAddress_ = ByteConversion::fromBytes(
                              data + byteCount,
                              ByteSizes::uint32Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign);
  byteCount += ByteSizes::uint32Size;
  
  numObjects_ = ByteConversion::fromBytes(
                              data + byteCount,
                              ByteSizes::uint32Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign);
  byteCount += ByteSizes::uint32Size;
  
  // Read number of mappings
  int numSpriteMappings = ByteConversion::fromBytes(
                              data + byteCount,
                              ByteSizes::uint16Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign);
  byteCount += ByteSizes::uint16Size;
  
  // Read data
  for (int i = 0; i < numSpriteMappings; i++) {
    SpriteMapping mapping;
    byteCount += mapping.load(data + byteCount);
    
    spriteMappings_.push_back(mapping);
  }
  
  // Read index->address mapping
  for (int i = 0; i < numSpriteMappings; i++) {
    int index = ByteConversion::fromBytes(
                              data + byteCount,
                              ByteSizes::uint32Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign);
    byteCount += ByteSizes::uint32Size;
    
    Taddress address = ByteConversion::fromBytes(
                              data + byteCount,
                              ByteSizes::uint32Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign);
    byteCount += ByteSizes::uint32Size;
    
    mappingIndexToAddress_.insert(
      MappingIndexToAddress::PairType(
        index,
        address));
  }
  
  // Read number of coordinate tables
  int numSpriteMappingCoordinateTables = ByteConversion::fromBytes(
                              data + byteCount,
                              ByteSizes::uint16Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign);
  byteCount += ByteSizes::uint16Size;
  
  // Read data
  for (int i = 0; i < numSpriteMappingCoordinateTables; i++) {
    SpriteMappingCoordinateTable coordinateTable;
    byteCount += coordinateTable.load(data + byteCount);
    
    spriteMappingCoordinateTables_.push_back(coordinateTable);
  }
  
  for (int i = 0; i < numSpriteMappingCoordinateTables; i++) {
    SpriteMappingCoordinateTable coordinateTable;
    byteCount += coordinateTable.load(data + byteCount);
    
    spriteMappingFlipCoordinateTables_.push_back(coordinateTable);
  }
  
  // Read index->address mapping
  for (int i = 0; i < numSpriteMappingCoordinateTables; i++) {
    int index = ByteConversion::fromBytes(
                              data + byteCount,
                              ByteSizes::uint32Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign);
    byteCount += ByteSizes::uint32Size;
    
    Taddress address = ByteConversion::fromBytes(
                              data + byteCount,
                              ByteSizes::uint32Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign);
    byteCount += ByteSizes::uint32Size;
    
//    std::cout << "index: " << index << '\t' << "address: " << address
//      << std::endl;
    
    coordinateTableIndexToAddress_.insert(
      CoordinateTableIndexToAddress::PairType(
        index,
        address));
  }
  
  // Read number of tile index tables
  int numSpriteMappingTileIndexTables = ByteConversion::fromBytes(
                              data + byteCount,
                              ByteSizes::uint16Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign);
  byteCount += ByteSizes::uint16Size;
  
  // Read data
  for (int i = 0; i < numSpriteMappingTileIndexTables; i++) {
    SpriteMappingTileIndexTable tileIndexTable;
    byteCount += tileIndexTable.load(data + byteCount);
    
    spriteMappingTileIndexTables_.push_back(tileIndexTable);
  }
  
  // Read index->address mapping
  for (int i = 0; i < numSpriteMappingTileIndexTables; i++) {
    int index = ByteConversion::fromBytes(
                              data + byteCount,
                              ByteSizes::uint32Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign);
    byteCount += ByteSizes::uint32Size;
    
    Taddress address = ByteConversion::fromBytes(
                              data + byteCount,
                              ByteSizes::uint32Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign);
    byteCount += ByteSizes::uint32Size;
    
    tileIndexTableIndexToAddress_.insert(
      TileIndexTableIndexToAddress::PairType(
        index,
        address));
  }
  
/*  for (int i = 0; i < numObjects_; i++) {
    int index = ByteConversion::fromBytes(
                              data + byteCount,
                              ByteSizes::uint32Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign);
    byteCount += ByteSizes::uint32Size;
    
    mappingsByID_.push_back(index);
  } */
  
  for (int i = 0; i < numObjects_; i++) {
    objectIDToMappingIndices_.push_back(MappingIndexCollection());
  
    int msize = ByteConversion::fromBytes(
                            data + byteCount,
                            ByteSizes::uint32Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    byteCount += ByteSizes::uint32Size;
    
    for (int j = 0; j < msize; j++) {
      int index = ByteConversion::fromBytes(
                              data + byteCount,
                              ByteSizes::uint32Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign);
      byteCount += ByteSizes::uint32Size;
      
      objectIDToMappingIndices_[i].push_back(index);
    }
  }
  
  return byteCount;
}

void EditableSpriteMappings::exportToROM(WritableROM& rom) {
  for (int i = 0; i < spriteMappingCoordinateTables_.size(); i++) {
    spriteMappingCoordinateTables_[i].writeToData(rom.directWrite(
                    coordinateTableIndexToAddress_.findValueOrThrow(i)));
  }
  
  for (int i = 0; i < spriteMappingFlipCoordinateTables_.size(); i++) {
    spriteMappingFlipCoordinateTables_[i].writeToData(
        rom.directWrite(
          coordinateTableIndexToAddress_.findValueOrThrow(i)
            + offsetToHorizontalFlip));
  }
  
  for (int i = 0; i < spriteMappingTileIndexTables_.size(); i++) {
    spriteMappingTileIndexTables_[i].writeToData(rom.directWrite(
                    tileIndexTableIndexToAddress_.findValueOrThrow(i)));
  }
  
  for (int i = 0; i < spriteMappings_.size(); i++) {
    spriteMappings_[i].writeToData(rom.directWrite(
                    mappingIndexToAddress_.findValueOrThrow(i)),
                    coordinateTableIndexToAddress_.findValueOrThrow(
                      spriteMappings_[i].coordinateTableIndex()),
                    tileIndexTableIndexToAddress_.findValueOrThrow(
                      spriteMappings_[i].tileIndexTableIndex()));
  }
}

int EditableSpriteMappings::numSpriteMappings() const {
  return spriteMappings_.size();
}

int EditableSpriteMappings::numCoordinateTables() const {
  return spriteMappingCoordinateTables_.size();
}

int EditableSpriteMappings::numTileIndexTables() const {
  return spriteMappingTileIndexTables_.size();
}
  
SpriteMapping& EditableSpriteMappings
    ::spriteMapping(int index) {
  return spriteMappings_[index];
}

SpriteMappingCoordinateTable& EditableSpriteMappings
    ::coordinateTable(int index) {
  return spriteMappingCoordinateTables_[index];
}
  
SpriteMappingCoordinateTable& EditableSpriteMappings
    ::flipCoordinateTable(int index) {
  return spriteMappingFlipCoordinateTables_[index];
}

SpriteMappingTileIndexTable& EditableSpriteMappings
    ::tileIndexTable(int index) {
  return spriteMappingTileIndexTables_[index];
}
  
const SpriteMapping& EditableSpriteMappings
    ::spriteMapping(int index) const {
  return spriteMappings_[index];
}

const SpriteMappingCoordinateTable& EditableSpriteMappings
    ::coordinateTable(int index) const {
  return spriteMappingCoordinateTables_[index];
}

const SpriteMappingCoordinateTable& EditableSpriteMappings
    ::flipCoordinateTable(int index) const {
  return spriteMappingFlipCoordinateTables_[index];
}

const SpriteMappingTileIndexTable& EditableSpriteMappings
    ::tileIndexTable(int index) const {
  return spriteMappingTileIndexTables_[index];
}
  
EditableSpriteMappings::MappingIndexCollection EditableSpriteMappings
    ::mappingsByObjectID(int objectID) {
  return objectIDToMappingIndices_[objectID];
}


};
