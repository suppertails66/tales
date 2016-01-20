#include "gamedata/LevelHeaders.h"
#include "gamedata/SubMaps.h"
#include "gamedata/PrimaryMaps.h"
#include "structs/KeyedAddressTableBuilder.h"
#include "structs/Taddress.h"
#include "gamedata/TailsAdvAddresses.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"
#include <iostream>

using namespace Luncheon;

namespace Tales {


LevelHeaders::LevelHeaders() {
  
}

LevelHeaders::LevelHeaders(
                     LoadedROM& rom,
                     Taddress address,
                     const RawLevelHeaders& rawHeaders,
                     const MetatileStructures&
                       metatileStructures,
                     const MapLayouts& mapLayouts,
                     const YTableAddresses& yTableAddresses)
  : keyedAccess_(SubMaps::subMapCounts,
                 SubMaps::subMapCountsSize) {
  // Read address table
  KeyedAddressTableBuilder::buildKeyedAddressTable(
      rom,
      address,
      keyedAccess_);
  
  int indexNum = 0;
  for (AddressRawLevelHeaderMap::const_iterator it = rawHeaders.cbegin();
       it != rawHeaders.cend();
       it++) {
    // Create index->address mapping
    indexToAddress_.insert(
      IndexLevelHeaderAddressMap::PairType(
        indexNum++,
        it->first));
    
    // Get the width of the level
    int width = yTableAddresses.widthOfInitialAddress(
                          it->second.yTableAddress());

    AddressLevelHeaderPair newPair(
          it->first,
          LevelHeader(metatileStructures.indexOfInitialAddress(
                          it->second.metatileStructureAddress()),
                      mapLayouts.indexOfInitialAddress(
                          it->second.mapLayoutAddress()),
                      width,
                      it->second.cameraLeftLimit(),
                      it->second.cameraTopLimit(),
                      it->second.cameraRightLimit(),
                      it->second.cameraBottomLimit(),
                      yTableAddresses.addressOfWidth(
                          width)));
    
//    std::cerr << "here" << std::endl;

    // Insert into storage
    primaryStorage_.insert(newPair);
  }
      
/*  for (AddressRawLevelHeaderMap::const_iterator it = rawHeaders.cbegin();
       it != rawHeaders.cend();
       it++) {
//    std::cerr << it->second.metatileStructureAddress() << std::endl;
//    std::cerr << it->second.mapLayoutAddress() << std::endl;
//    std::cerr << it->second.visualWidth() << std::endl;
//    std::cerr << it->second.yTableAddress() << std::endl;
//    std::cerr << std::endl;
    
    // Get the width of the level
    int width = yTableAddresses.widthOfInitialAddress(
                          it->second.yTableAddress());

    AddressLevelHeaderPair newPair(
          it->first,
          LevelHeader(metatileStructures.indexOfInitialAddress(
                          it->second.metatileStructureAddress()),
                      mapLayouts.indexOfInitialAddress(
                          it->second.mapLayoutAddress()),
                      width,
                      it->second.cameraLeftLimit(),
                      it->second.cameraTopLimit(),
                      it->second.cameraRightLimit(),
                      it->second.cameraBottomLimit(),
                      yTableAddresses.addressOfWidth(
                          width)));
    
//    std::cerr << "here" << std::endl;

    // Insert into storage
    primaryStorage_.insert(newPair);
  } */
  
/*  // Create primary storage
  for (int i = TwoKeyedAddress::primaryKeyBase;
       i < keyedAccess_.numPrimaryKeys();
       i++) {
    // Iterate over subkeys
    int numSubKeys = keyedAccess_.subKeyTable()[i];
    
    for (int j = 0;
          j < numSubKeys;
          j++) {
      // Insert empty data at key (if it doesn't exist)
      primaryStorage_.insert(AddressLevelHeaderPair(
        keyedAccess_.refDataByKeys(i, j + TwoKeyedAddress::subKeyBase),
        LevelHeader()));
    }
  } */
  
  // Insert placeholder entries for all headers in the table. There are 51
  // headers in total.
  // Note that we can't just use the address table to do
  // this because several headers are not referenced by the table.
  // The unreferenced headers seem to be for cutscenes (intro, dock) and the
  // alternate boss areas used when a boss arena is re-entered once the boss
  // is defeated. Presumably, they are hardcoded for those circumstances.
/*  for (int i = 0;
       i < TailsAdvAddresses::LevelHeaderTableContentEntries;
       i++) {
      // Generate insertion pair of address and (empty) header
      AddressLevelHeaderPair newPair(
            TailsAdvAddresses::LevelHeaderTableContent 
              + (i * LevelHeader::dataSize),
            LevelHeader());
      
      // Insert into storage
      primaryStorage_.insert(newPair);
  } */
  
/*  AddressLevelHeaderMap allheaders;
  for (int i = 0;
       i < TailsAdvAddresses::LevelHeaderTableContentEntries;
       i++) {
    AddressLevelHeaderPair pairz(
          TailsAdvAddresses::LevelHeaderTableContent 
            + (i * LevelHeader::dataSize),
          LevelHeader(rom,
                      TailsAdvAddresses::LevelHeaderTableContent 
                      + (i * LevelHeader::dataSize)));
      allheaders.insert(pairz);
      
      std::cout << "Entry " << i << std::endl;
      std::cout << '\t' << "Header address: " << pairz.first << std::endl;
      std::cout << '\t' << "Graphics header address: "
        << pairz.second.levelGraphicsID_ << std::endl;
      std::cout << '\t' << "Layout address: " 
        << pairz.second.mapLayoutID_ << std::endl;
      std::cout << '\t' << "Visual width: " 
        << pairz.second.visualWidth_ << std::endl;
      std::cout << '\t' << "Camera left limit: " 
        << pairz.second.cameraLeftLimit_ << std::endl;
      std::cout << '\t' << "Camera top limit: " 
        << pairz.second.cameraTopLimit_ << std::endl;
      std::cout << '\t' << "Camera right limit: " 
        << pairz.second.cameraRightLimit_ << std::endl;
      std::cout << '\t' << "Camera bottom limit: " 
        << pairz.second.cameraBottomLimit_ << std::endl;
      std::cout << std::endl;
  } */
  
  // Set address and length
/*  if (primaryStorage_.size()) {
    // Lowest address = base
    address_ = primaryStorage_.begin()->first;
    
  }
  // Length = numHeaders * dataSize
  length_ = primaryStorage_.size() * LevelHeader::dataSize; */
  
  // Read level headers into primary storage
/*  for (AddressLevelHeaderMap::iterator it = primaryStorage_.begin();
       it != primaryStorage_.end();
       it++) {
    it->second.readFromData(rom.directRead(it->first));
    
//    Tbyte buffer[LevelHeader::dataSize];
//    it->second.writeToData(buffer);
//    it->second.readFromData(buffer);
  } */
  
/*  for (AddressLevelHeaderMap::iterator it = allheaders.begin();
       it != allheaders.end();
       it++) {
    bool matched = false;
    for (AddressLevelHeaderMap::iterator jt = primaryStorage_.begin();
         jt != primaryStorage_.end();
         jt++) {
      if (it->first == jt->first) {
        matched = true;
      }
    }
    
    if (!matched) {
      std::cout << it->first << " is unreferenced" << std::endl;
    }
  } */
  
//    std::cout << primaryStorage_.size() << std::endl;
}

void LevelHeaders::save(std::string& data) {
  // Buffer to hold converted header count
  Tbyte headerCount[ByteSizes::uint16Size];
  
  // Convert number of headers to byte representation
  ByteConversion::toBytes(primaryStorage_.size(),
                          headerCount,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);

  // Write number of headers to string
  data += std::string((char*)headerCount, ByteSizes::uint16Size);

  // Write out all loaded headers
  for (AddressLevelHeaderMap::iterator it = primaryStorage_.begin();
       it != primaryStorage_.end();
       it++) {
    // Write header address
       
    // Buffer to hold converted address of data
    Tbyte address[ByteSizes::uint32Size];
    
    // Convert address to raw byte representation
    ByteConversion::toBytes(it->first,
                            address,
                            ByteSizes::uint32Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
                            
    // Write header address to string
    data += std::string((char*)address, ByteSizes::uint32Size);
    
    // Write header data

    it->second.save(data);
  }
  
  // Write index->address mapping
  indexToAddress_.save(data);
  
  // Write map lookup table to string
  keyedAccess_.writeToData(data);
}

int LevelHeaders::load(const Tbyte* data) {
  // Count of read bytes
  int count = 0;
  
  // Clear existing stored data
  indexToAddress_.clear();
  primaryStorage_.clear();

  // Get number of headers
  int numHeaders = ByteConversion::fromBytes(
                          data + count,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  count += ByteSizes::uint16Size;
  
  // Read headers
  for (int i = 0; i < numHeaders; i++) {
    // Get header address
    Taddress headerAddress = ByteConversion::fromBytes(
                          data + count,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
    count += ByteSizes::uint32Size;
    
    // Read header
    LevelHeader header;
    count += header.load(data + count);
    
    // Add to primary storage
    primaryStorage_.insert(AddressLevelHeaderPair(
                              headerAddress,
                              header));
  }
  
  // Read index->address mapping
  count += indexToAddress_.load(data + count);
  
  // Read map lookup table
  count += keyedAccess_.readFromData(data + count);

  return count;
}

void LevelHeaders::exportToROM(
                       WritableROM& rom,
                       const MetatileStructures&
                         metatileStructures,
                       const MapLayouts& mapLayouts,
                       const YTableAddresses& yTableAddresses) {
  // Write each header to its corresponding address
  for (AddressLevelHeaderMap::iterator it = primaryStorage_.begin();
       it != primaryStorage_.end();
       it++) {
     // Buffer to hold raw header
     Tbyte buffer[LevelHeader::dataSize];
     
     // Write header to buffer
     it->second.writeToData(buffer,
                            metatileStructures.metatileStructureSet(
                              it->second.tileStructureID())
                              .address(),
                            mapLayouts.mapAtIndex(
                              it->second.mapLayoutID())
                              .address(),
                            yTableAddresses.addressOfWidth(
                              it->second.width()));
      
      // Write header to ROM      
      rom.directWrite(it->first,
                      buffer,
                      LevelHeader::dataSize);
      
    // Buffer to hold header
/*    Tbyte header[LevelHeader::dataSize];
    
    // Write header
    it->second.writeToData(header);
    
    // Write header to ROM
    // TODO: copy full header once its export code is completed
    // for testing, copy only camera limits
    rom.directWrite(it->first + 12,
                    header + 12,
                    8);
//    rom.directWrite(it->first,
//                    header,
//                    LevelHeader::dataSize); */
  }
}

int LevelHeaders::size() const {
  return primaryStorage_.size();
}

LevelHeader& LevelHeaders::levelHeader(int primaryMap,
                                               int subMap) {
  // Get address of target data
  Taddress address = keyedAccess_.refDataByKeys(primaryMap, subMap);
  
  // Return corresponding key
  return primaryStorage_.findValueOrThrow(address);
}

int LevelHeaders::levelHeaderIndex(int primaryMap, int subMap) {
  Taddress address = keyedAccess_.refDataByKeys(primaryMap, subMap);
  
  // Linear search for corresponding ID (poor planning ahoy!)
  for (IndexLevelHeaderAddressMap::iterator it = indexToAddress_.begin();
       it != indexToAddress_.end();
       it++) {
    if (it->second == address) {
      return it->first;
    }
  }
  
  return -1;
}

AreaMapReference LevelHeaders::areaMapNumOfIndex(int levelHeaderIndexNum) {
  // Special-case boss arena indices
  switch (levelHeaderIndexNum) {
  case worldMapDupeHeaderIndex:  // World map dupe?
    return AreaMapReference(16, 1);
    break;
  case introDupeHeaderIndex:  // duplicate of intro forest (on fire)
    return AreaMapReference(19, 2);
    break;
  case lakeRocky1HeaderIndex:  // Dupe of escape from coco island?
    return AreaMapReference(20, 2);
    break;
  case lakeRockyBossHeaderIndex:  // Lake Rocky boss
    return AreaMapReference(6, 3);
    break;
  case lakeRocky2HeaderIndex:  // Lake Rocky 5, after entering coco island
    return AreaMapReference(6, 5);
    break;
  case pollyMt1BossHeaderIndex:  // Polly Mt 1 boss
    return AreaMapReference(4, 3);
    break;
  case cavernIslandBossHeaderIndex:  // Cavern Island boss
    return AreaMapReference(9, 3);
    break;
  default:
    break;
  }

  for (int i = 0; i < SubMaps::subMapCountsSize; i++) {
    for (int j = 0; j < SubMaps::subMapCounts[i]; j++) {
      int index = levelHeaderIndex(i + TwoKeyedAddress::primaryKeyBase,
                                   j + TwoKeyedAddress::subKeyBase);
      if (index == levelHeaderIndexNum) {
        return AreaMapReference(i + TwoKeyedAddress::primaryKeyBase,
                                j + TwoKeyedAddress::subKeyBase);
      }
    }
  }
  
  return AreaMapReference(0, 0);
}

LevelHeader& LevelHeaders::levelHeaderByIndex(int levelHeaderIndexNum) {
  Taddress address = indexToAddress_.findValueOrThrow(levelHeaderIndexNum);
  
  return primaryStorage_.findValueOrThrow(address);
}

AddressLevelHeaderMap::iterator LevelHeaders::begin() {
  return primaryStorage_.begin();
}

AddressLevelHeaderMap::iterator LevelHeaders::end() {
  return primaryStorage_.end();
}


}; 
