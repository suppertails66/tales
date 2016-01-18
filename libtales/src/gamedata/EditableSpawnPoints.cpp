#include "gamedata/EditableSpawnPoints.h"
#include "exception/UnrecognizedVersionException.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"
#include "structs/KeyedTableBuilder.h"
#include "gamedata/PrimaryMaps.h"
#include "gamedata/SubMaps.h"
#include <iostream>

using namespace Luncheon;

namespace Tales {


EditableSpawnPoints::EditableSpawnPoints()
  : TwoKeyEditableMappedData<SpawnPointCollection,
                           BaseSpawnPointCollection>() { };

EditableSpawnPoints::EditableSpawnPoints(
                         LoadedROM& rom,
                         Taddress tableHeaderAddress,
                         Taddress tableEndAddress)
  : TwoKeyEditableMappedData<SpawnPointCollection,
                           BaseSpawnPointCollection>(rom,
                                 tableHeaderAddress,
                                 tableEndAddress,
                                 SubMaps::subMapCounts,
                                 PrimaryMaps::primaryMapTableSize) {
  readAndConstruct(rom,
                   tableHeaderAddress,
                   tableEndAddress);
}
               
SpawnPointCollection& EditableSpawnPoints::spawnsByMapnum(
                                         int primaryMapNum,
                                         int subMapNum) {
  return dataByMapnum(primaryMapNum,
                      subMapNum);
}

int EditableSpawnPoints::dataSizeOfOneElement() {
  return SpawnPoint::dataSize;
}

int EditableSpawnPoints::readElements(
                         BaseSpawnPointCollection& dst,
                         const Tbyte* data,
                         int numElements) {
  int byteCount = 0;
  
  // Read each element
  for (int i = 0; i < numElements; i++) {
    // Read data
    SpawnPoint spawn(data + byteCount);
    
    // Add to base collection
    dst.push_back(spawn);
    
    // Advance to next address
    byteCount += SpawnPoint::dataSize;
  }
  
  return byteCount;
}

void EditableSpawnPoints::saveElement(std::string& data,
                          SpawnPointCollection& src) {
  // Write buffer
  Tbyte buffer[ByteSizes::uint32Size];
                          
  // Write number of spawns
  ByteConversion::toBytes(src.size(),
                          buffer,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint32Size);
  
  for (SpawnPointCollection::iterator it = src.begin();
       it != src.end();
       it++) {
    // Buffer for data
    Tbyte dataBuffer[SpawnPoint::dataSize];
    
    // Write spawn to data
    it->writeToData(dataBuffer);
    
    // Copy spawn to output
    data += std::string((char*)dataBuffer, SpawnPoint::dataSize);
  }
}

int EditableSpawnPoints::loadElement(
                        BaseSpawnPointCollection& dst,
                        const Tbyte* data) {
  int byteCount = 0;
                          
  // Read number of spawns
  int numElements = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint32Size;
  
  for (int i = 0; i < numElements; i++) {
    // Read data
    SpawnPoint spawn(data + byteCount);
    
    // Add to base collection
    dst.push_back(spawn);
    
    // Advance to next address
    byteCount += SpawnPoint::dataSize;
  }
  
  return byteCount;
}

void EditableSpawnPoints::exportElementToROM(WritableROM& rom,
                                Taddress address,
                                SpawnPointCollection& src) {
  Taddress writeAddress = address;
  
  for (SpawnPointCollection::iterator it = src.begin();
       it != src.end();
       it++) {
//    std::cout << writeAddress << std::endl;
//    std::cout << '\t' << it->camX() << std::endl;
    // Buffer for data
    Tbyte dataBuffer[SpawnPoint::dataSize];
    
    // Write spawn to data
    it->writeToData(dataBuffer);
    
//    for (int i = 0; i < SpawnPoint::dataSize; i++) {
//      std::cout << (int)(dataBuffer[i]) <<  " ";
//    }
//    std::cout << std::endl;
    
    // Copy raw spawn data to ROM
    rom.directWrite(writeAddress,
                    dataBuffer,
                    SpawnPoint::dataSize);
    
    // Advance to next address
    writeAddress += SpawnPoint::dataSize;
  }
}
  
DataChunkIDs::DataChunkID EditableSpawnPoints::dataChunkID() {
  return DataChunkIDs::spawnPoints;
}

std::string EditableSpawnPoints::dataChunkName() {
  return "EditableSpawnPoints";
}

int EditableSpawnPoints::chunkVersionNumber() {
  return 0;
}

int EditableSpawnPoints::maxRecognizedVersionNumber() {
  return 0;
}

/*EditableSpawnPoints::EditableSpawnPoints() { };

EditableSpawnPoints::EditableSpawnPoints(
                    LoadedROM& rom,
                    Taddress tableHeaderAddress,
                    Taddress tableEndAddress,
                    const int subKeyTable[],
                    int numPrimaryKeys)
  : mapnumToAddress_(subKeyTable,
                     numPrimaryKeys) {
  // Read address table
  KeyedTableBuilder::buildKeyedAddressTable(
    rom,
    tableHeaderAddress,
    mapnumToAddress_);
                     
  // Iterate over each read address
  for (int i = 0; i < mapnumToAddress_.numPrimaryKeys(); i++) {
    for (int j = 0; j < mapnumToAddress_.subKeyTable()[i]; j++) {
      // Get the address of the target array
      Taddress address
        = mapnumToAddress_.refDataByKeys(i + TwoKeyedAddress::primaryKeyBase,
                                         j + TwoKeyedAddress::subKeyBase);
      
      // Add stub entry to primary storage.
      // Since primaryStorage_ is a map, this sorts by address
      // and eliminates duplicate entries
      primaryStorage_.insert(
        AddressSpawnsPair(address,
                          SpawnPointCollection()));
    }
  }
  
  // Iterate over primary storage addresses and read corresponding arrays
  for (AddressSpawnsMap::iterator it = primaryStorage_.begin();
       it != primaryStorage_.end();
       it++) {
//    std::cout << "start: " << it->first << std::endl;
       
    // Compute the size of the array using the start address of the next
    // array, or the end of the table header if at the last entry
    Taddress arrayStartAddress = it->first;
    Taddress arrayEndAddress = 0;
    
    // Check if at last entry of spawns map
    AddressSpawnsMap::iterator nextEntry = it;
    ++nextEntry;
    // If at end, use table content end address as next address
    if (nextEntry == primaryStorage_.end()) {
      arrayEndAddress = tableEndAddress;
    }
    // Otherwise, use start address of next array
    else {
      arrayEndAddress = nextEntry->first;
    }
//    std::cout << '\t' << "end: " << arrayEndAddress << std::endl;
    
    // Compute number of elements in array by dividing by dataSize
    int numElements = (arrayEndAddress - arrayStartAddress)
                        / SpawnPoint::dataSize;
    
    // Read each element in array
    BaseSpawnPointCollection baseSpawns;
    Taddress readAddress = arrayStartAddress;
    
    for (int i = 0; i < numElements; i++) {
      // Read spawn data
      SpawnPoint spawn(rom.directRead(readAddress));
      
      // Add to base collection
      baseSpawns.push_back(spawn);
      
      // Advance to next address
      readAddress += SpawnPoint::dataSize;
    }
    
    // Add read spawns to primary storage
    it->second = SpawnPointCollection(baseSpawns);
  }
}

void EditableSpawnPoints::save(std::string& data) {
  // Write buffer
  Tbyte buffer[ByteSizes::uint32Size];
  
  // Write number of SpawnCollections
  ByteConversion::toBytes(primaryStorage_.size(),
                          buffer,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint32Size);
  
//  std::cout << "out numentries: " << primaryStorage_.size() << std::endl;

  // Write each SpawnCollection
  for (AddressSpawnsMap::iterator it = primaryStorage_.begin();
       it != primaryStorage_.end();
       it++) {
    // Write address
    ByteConversion::toBytes(it->first,
                            buffer,
                            ByteSizes::uint32Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    data += std::string((char*)buffer, ByteSizes::uint32Size);
    
    // Write number of spawns
    ByteConversion::toBytes(it->second.size(),
                            buffer,
                            ByteSizes::uint32Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    data += std::string((char*)buffer, ByteSizes::uint32Size);
    
    // Write spawns
    for (SpawnPointCollection::iterator jt = it->second.begin();
         jt != it->second.end();
         jt++) {
      // Buffer for spawn data
      Tbyte spawnBuffer[SpawnPoint::dataSize];
      
      // Write spawn to data
      jt->writeToData(spawnBuffer);
      
      // Copy spawn to output
      data += std::string((char*)spawnBuffer, SpawnPoint::dataSize);
    }
  }
  
  // Write address table
  mapnumToAddress_.writeToData(data);
}

int EditableSpawnPoints::load(const Tbyte* data) {
  // Clear existing data
  primaryStorage_.clear();
//  mapnumToAddress_.clear();

  // Count of bytes read
  int byteCount = 0;
  
  // Read number of SpawnCollections
  int numEntries
    = ByteConversion::fromBytes(data + byteCount,
                                ByteSizes::uint32Size,
                                EndiannessTypes::little,
                                SignednessTypes::nosign);
  byteCount += ByteSizes::uint32Size;
  
//  std::cout << "in numentries: " << numEntries << std::endl;
  
  // Read each SpawnCollection
  for (int i = 0; i < numEntries; i++) {
    // Read address
    Taddress address
      = ByteConversion::fromBytes(data + byteCount,
                                  ByteSizes::uint32Size,
                                  EndiannessTypes::little,
                                  SignednessTypes::nosign);
    byteCount += ByteSizes::uint32Size;
    
    // Read number of spawns
    int numSpawns
      = ByteConversion::fromBytes(data + byteCount,
                                  ByteSizes::uint32Size,
                                  EndiannessTypes::little,
                                  SignednessTypes::nosign);
    byteCount += ByteSizes::uint32Size;
    
    // Read each spawn
    BaseSpawnPointCollection baseSpawns;
    for (int i = 0; i < numSpawns; i++) {
      // Destination for data
      SpawnPoint spawn;
      
      // Read spawn data
      spawn.readFromData(data + byteCount);
      byteCount += SpawnPoint::dataSize;
      
      // Add to base collection
      baseSpawns.push_back(spawn);
    }
    
    // Convert base collection to SpawnPointCollection (fixed size)
    SpawnPointCollection spawns(baseSpawns);
    
    // Add to primary storage
    primaryStorage_.insert(
      AddressSpawnsPair(address,
                        spawns));
  }
  
  // Read address table
  byteCount += mapnumToAddress_.readFromData(data + byteCount);
  
  // Return number of bytes read
  return byteCount;
}

void EditableSpawnPoints::exportToROM(WritableROM& rom) {
  // Export each SpawnCollection to ROM
  for (AddressSpawnsMap::iterator it = primaryStorage_.begin();
       it != primaryStorage_.end();
       it++) {
    // Address to write to
    Taddress address = it->first;
    
    for (SpawnPointCollection::iterator jt = it->second.begin();
         jt != it->second.end();
         jt++) {
      // Buffer for spawn data
      Tbyte spawnBuffer[SpawnPoint::dataSize];
      
      // Write spawn to data
      jt->writeToData(spawnBuffer);
      
      // Copy raw spawn data to ROM
      rom.directWrite(address,
                      spawnBuffer,
                      SpawnPoint::dataSize);
      
      // Advance to next address
      address += SpawnPoint::dataSize;
    }
  }
}

SpawnPointCollection& EditableSpawnPoints::spawnsByMapnum(
                                     int primaryMapNum,
                                     int subMapNum) {
  // Retrieve corresponding address
  Taddress address
    = mapnumToAddress_.refDataByKeys(
        primaryMapNum,
        subMapNum);
  
  // Use address to look up corresponding spawns
  return primaryStorage_.findValueOrThrow(address);
} */


};
