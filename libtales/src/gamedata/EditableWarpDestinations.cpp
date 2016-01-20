#include "gamedata/EditableWarpDestinations.h"
#include "exception/UnrecognizedVersionException.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"
#include "structs/KeyedTableBuilder.h"
#include "gamedata/PrimaryMaps.h"
#include "gamedata/SubMaps.h"
#include <iostream>

using namespace Luncheon;

namespace Tales {


EditableWarpDestinations::EditableWarpDestinations()
  : TwoKeyEditableMappedData<WarpDestinationCollection,
                           BaseWarpDestinationCollection>() { };

EditableWarpDestinations::EditableWarpDestinations(
                         LoadedROM& rom,
                         Taddress tableHeaderAddress,
                         Taddress tableEndAddress)
  : TwoKeyEditableMappedData<WarpDestinationCollection,
                           BaseWarpDestinationCollection>(rom,
                                 tableHeaderAddress,
                                 tableEndAddress,
                                 SubMaps::subMapCounts,
                                 primaryMapLimit) {
  readAndConstruct(rom,
                   tableHeaderAddress,
                   tableEndAddress);
}
               
WarpDestinationCollection& EditableWarpDestinations::warpsByMapnum(
                                         int primaryMapNum,
                                         int subMapNum) {
  return dataByMapnum(primaryMapNum,
                      subMapNum);
}

int EditableWarpDestinations::dataSizeOfOneElement() {
  return WarpDestination::dataSize;
}

int EditableWarpDestinations::readElements(
                         BaseWarpDestinationCollection& dst,
                         const Tbyte* data,
                         int numElements) {
  int byteCount = 0;
  
  // Read each element
  for (int i = 0; i < numElements; i++) {
    // Read data
    WarpDestination warp(data + byteCount);
    
    // Add to base collection
    dst.push_back(warp);
    
    // Advance to next address
    byteCount += WarpDestination::dataSize;
  }
  
  return byteCount;
}

void EditableWarpDestinations::saveElement(std::string& data,
                          WarpDestinationCollection& src) {
  // Write buffer
  Tbyte buffer[ByteSizes::uint32Size];
                          
  // Write number of warps
  ByteConversion::toBytes(src.size(),
                          buffer,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint32Size);
  
  for (WarpDestinationCollection::iterator it = src.begin();
       it != src.end();
       ++it) {
    // Buffer for data
    Tbyte dataBuffer[WarpDestination::dataSize];
    
    // Write warp to data
    it->writeToData(dataBuffer);
    
    // Copy warp to output
    data += std::string((char*)dataBuffer, WarpDestination::dataSize);
  }
}

int EditableWarpDestinations::loadElement(
                        BaseWarpDestinationCollection& dst,
                        const Tbyte* data) {
  int byteCount = 0;
                          
  // Read number of warps
  int numElements = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint32Size;
  
  for (int i = 0; i < numElements; i++) {
    // Read data
    WarpDestination warp(data + byteCount);
    
    // Add to base collection
    dst.push_back(warp);
    
    // Advance to next address
    byteCount += WarpDestination::dataSize;
  }
  
  return byteCount;
}

void EditableWarpDestinations::exportElementToROM(WritableROM& rom,
                                Taddress address,
                                WarpDestinationCollection& src) {
  Taddress writeAddress = address;
  for (WarpDestinationCollection::iterator it = src.begin();
       it != src.end();
       ++it) {
//       if (writeAddress <= 16894) {
//        std::cout << writeAddress << std::endl;
//       }
    // Buffer for data
    Tbyte dataBuffer[WarpDestination::dataSize];
    
    // Write warp to data
    it->writeToData(dataBuffer);
    
    // Copy raw warp data to ROM
    rom.directWrite(writeAddress,
                    dataBuffer,
                    WarpDestination::dataSize);
    
    // Advance to next address
    writeAddress += WarpDestination::dataSize;
  }
}
  
DataChunkIDs::DataChunkID EditableWarpDestinations::dataChunkID() {
  return DataChunkIDs::warpDestinations;
}

std::string EditableWarpDestinations::dataChunkName() {
  return "EditableWarpDestinations";
}

int EditableWarpDestinations::chunkVersionNumber() {
  return 0;
}

int EditableWarpDestinations::maxRecognizedVersionNumber() {
  return 0;
}
                           
/*EditableWarpDestinations::EditableWarpDestinations() { };

EditableWarpDestinations::EditableWarpDestinations(
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
        AddressWarpsPair(address,
                          WarpDestinationCollection()));
    }
  }
  
  // Iterate over primary storage addresses and read corresponding arrays
  for (AddressWarpsMap::iterator it = primaryStorage_.begin();
       it != primaryStorage_.end();
       it++) {
//    std::cout << "start: " << it->first << std::endl;
       
    // Compute the size of the array using the start address of the next
    // array, or the end of the table header if at the last entry
    Taddress arrayStartAddress = it->first;
    Taddress arrayEndAddress = 0;
    
    // Check if at last entry of spawns map
    AddressWarpsMap::iterator nextEntry = it;
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
                        / WarpDestination::dataSize;
    
    // Read each element in array
    BaseWarpDestinationCollection baseWarps;
    Taddress readAddress = arrayStartAddress;
    
    for (int i = 0; i < numElements; i++) {
      // Read spawn data
      WarpDestination warp(rom.directRead(readAddress));
      
      // Add to base collection
      baseWarps.push_back(warp);
      
      // Advance to next address
      readAddress += WarpDestination::dataSize;
    }
    
    // Add read spawns to primary storage
    it->second = WarpDestinationCollection(baseWarps);
  }
}

void EditableWarpDestinations::save(std::string& data) {
  // Write buffer
  Tbyte buffer[ByteSizes::uint32Size];
  
  // Write number of WarpCollections
  ByteConversion::toBytes(primaryStorage_.size(),
                          buffer,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint32Size);
  
//  std::cout << "out numentries: " << primaryStorage_.size() << std::endl;

  // Write each WarpCollection
  for (AddressWarpsMap::iterator it = primaryStorage_.begin();
       it != primaryStorage_.end();
       it++) {
    // Write address
    ByteConversion::toBytes(it->first,
                            buffer,
                            ByteSizes::uint32Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    data += std::string((char*)buffer, ByteSizes::uint32Size);
    
    // Write number of warps
    ByteConversion::toBytes(it->second.size(),
                            buffer,
                            ByteSizes::uint32Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    data += std::string((char*)buffer, ByteSizes::uint32Size);
    
    // Write warps
    for (WarpDestinationCollection::iterator jt = it->second.begin();
         jt != it->second.end();
         jt++) {
      // Buffer for warp data
      Tbyte warpBuffer[WarpDestination::dataSize];
      
      // Write warp to data
      jt->writeToData(warpBuffer);
      
      // Copy warp to output
      data += std::string((char*)warpBuffer, WarpDestination::dataSize);
    }
  }
  
  // Write address table
  mapnumToAddress_.writeToData(data);
}

int EditableWarpDestinations::load(const Tbyte* data) {
  // Clear existing data
  primaryStorage_.clear();
//  mapnumToAddress_.clear();

  // Count of bytes read
  int byteCount = 0;
  
  // Read number of WarpCollections
  int numEntries
    = ByteConversion::fromBytes(data + byteCount,
                                ByteSizes::uint32Size,
                                EndiannessTypes::little,
                                SignednessTypes::nosign);
  byteCount += ByteSizes::uint32Size;
  
//  std::cout << "in numentries: " << numEntries << std::endl;
  
  // Read each WarpCollection
  for (int i = 0; i < numEntries; i++) {
    // Read address
    Taddress address
      = ByteConversion::fromBytes(data + byteCount,
                                  ByteSizes::uint32Size,
                                  EndiannessTypes::little,
                                  SignednessTypes::nosign);
    byteCount += ByteSizes::uint32Size;
    
    // Read number of warps
    int numWarps
      = ByteConversion::fromBytes(data + byteCount,
                                  ByteSizes::uint32Size,
                                  EndiannessTypes::little,
                                  SignednessTypes::nosign);
    byteCount += ByteSizes::uint32Size;
    
    // Read each spawn
    BaseWarpDestinationCollection baseWarps;
    for (int i = 0; i < numWarps; i++) {
      // Destination for data
      WarpDestination warp;
      
      // Read spawn data
      warp.readFromData(data + byteCount);
      byteCount += WarpDestination::dataSize;
      
      // Add to base collection
      baseWarps.push_back(warp);
    }
    
    // Convert base collection to SpawnPointCollection (fixed size)
    WarpDestinationCollection warps(baseWarps);
    
    // Add to primary storage
    primaryStorage_.insert(
      AddressWarpsPair(address,
                       warps));
  }
  
  // Read address table
  byteCount += mapnumToAddress_.readFromData(data + byteCount);
  
  // Return number of bytes read
  return byteCount;
}

void EditableWarpDestinations::exportToROM(WritableROM& rom) {
  // Export each WarpCollection to ROM
  for (AddressWarpsMap::iterator it = primaryStorage_.begin();
       it != primaryStorage_.end();
       it++) {
    // Address to write to
    Taddress address = it->first;
    
    for (WarpDestinationCollection::iterator jt = it->second.begin();
         jt != it->second.end();
         jt++) {
      // Buffer for warp data
      Tbyte warpBuffer[WarpDestination::dataSize];
      
      // Write warp to data
      jt->writeToData(warpBuffer);
      
      // Copy raw warp data to ROM
      rom.directWrite(address,
                      warpBuffer,
                      WarpDestination::dataSize);
      
      // Advance to next address
      address += WarpDestination::dataSize;
    }
  }
}

WarpDestinationCollection& EditableWarpDestinations::warpsByMapnum(
                                         int primaryMapNum,
                                         int subMapNum) {
  // Retrieve corresponding address
  Taddress address
    = mapnumToAddress_.refDataByKeys(
        primaryMapNum,
        subMapNum);
  
  // Use address to look up corresponding warps
  return primaryStorage_.findValueOrThrow(address);
} */


};
