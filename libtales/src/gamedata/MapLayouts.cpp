#include "gamedata/MapLayouts.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"
#include "exception/OutOfRangeIndexException.h"
#include <iostream>

using namespace Luncheon;

namespace Tales {


MapLayouts::MapLayouts() { };

MapLayouts::MapLayouts(
          LoadedROM& rom,
          const RawLevelHeaders& headers) {
  // Iterate over headers
  int mapNum = 0;
  for (AddressRawLevelHeaderMap::const_iterator it = headers.cbegin();
       it != headers.cend();
       it++) {
    
    // Check if this map has been loaded
    AddressToMapIndexMap::iterator findIt
      = addressToIndex_.find(it->second.mapLayoutAddress());
    
    // Don't load if map already loaded
    if (findIt != addressToIndex_.end()) {
      continue;
    }
    
    // Add new map to storage
    mapLayouts_.push_back(MapLayout());
    MapLayout& map = mapLayouts_.back();
    
    // Read map data
    map.readFromData(rom,
                     it->second.mapLayoutAddress());
    
    // Add address mapping
    addressToIndex_.insert(AddressToMapIndexPair(
                it->second.mapLayoutAddress(),
                mapNum));
    
    ++mapNum;
  }
}

void MapLayouts::save(std::string& data) {
  // Output buffer
  char buffer[ByteSizes::uint32Size];

  // Write number of maps
  ByteConversion::toBytes(mapLayouts_.size(),
                          buffer,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string(buffer, ByteSizes::uint16Size);
  
  // Write each map
  for (MapLayoutCollection::iterator it
          = mapLayouts_.begin();
       it != mapLayouts_.end();
       it++) {
    it->save(data);
  }
}

int MapLayouts::load(const Tbyte* data) {
  // Count of read bytes
  int byteCount = 0;
  
  // Clear existing data
  mapLayouts_.clear();

  // Read number of maps
  int numMaps = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint16Size;
  
  // Read each map
  for (int i = 0; i < numMaps; i++) {
    // Add new map to storage
    mapLayouts_.push_back(MapLayout());
    MapLayout& map = mapLayouts_.back();
    
    // Read map data
    byteCount += map.load(data + byteCount);
  }
  
  return byteCount;
}

void MapLayouts::exportToROM(WritableROM& rom) {
  // Export each map
  int count = 0;
  for (MapLayoutCollection::iterator it
          = mapLayouts_.begin();
       it != mapLayouts_.end();
       it++) {
//    std::cout << "exporting " << count++ << std::endl;
    it->exportToFreeROM(rom);
  }
}

int MapLayouts::numMaps() {
  return mapLayouts_.size();
}

MapLayout& MapLayouts::mapAtIndex(int index) {
  // Throw if index out of range
  if ((unsigned int)index >= mapLayouts_.size()) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "MapLayouts::mapAtIndex(int)",
                                   index);
  }

  return mapLayouts_[index];
}

const MapLayout& MapLayouts::mapAtIndex(int index) const {
  // Throw if index out of range
  if ((unsigned int)index >= mapLayouts_.size()) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "MapLayouts::mapAtIndex(int) const",
                                   index);
  }

  return mapLayouts_[index];
}

int MapLayouts::indexOfInitialAddress(Taddress initialAddress)
       const {
  return addressToIndex_.findOrThrow(initialAddress)->second;
}


}; 
