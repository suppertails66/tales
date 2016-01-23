#include "gamedata/EditableTileMaps.h"
#include "gamedata/TileMapInfos.h"
#include "exception/OutOfRangeIndexException.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"
#include "structs/DataChunkID.h"
#include "structs/SaveHelper.h"
#include "structs/LoadHelper.h"

using namespace Luncheon;

namespace Tales {


EditableTileMaps::EditableTileMaps() { };

EditableTileMaps::EditableTileMaps(LoadedROM& rom) {
  // Read tile maps
  for (int i = 0; i < TileMapInfos::numTileMaps(); i++) {
    TileMapInfo info = TileMapInfos::tileMapInfo(i);
    
    switch (info.format) {
    case TileMap::oneBytePerTile:
      {
      // 1bpt: use upper byte
      TileMap tile(rom.directRead(info.address),
                   info.format,
                   info.w,
                   info.h,
                   info.upperByte);
      primaryStorage_.push_back(tile);
      }
      break;
    case TileMap::twoBytesPerTile:
      {
      // 2bpt: standard read
      TileMap tile(rom.directRead(info.address),
                   info.format,
                   info.w,
                   info.h);
      primaryStorage_.push_back(tile);
      }
      break;
    default:
      continue;
      break;
    }
    
    // Add index->address mapping
    indexToAddress_[i] = info.address;
  }
}

int EditableTileMaps::size() const {
  return primaryStorage_.size();
}

TileMap& EditableTileMaps::tileMap(int index) {
  if (index >= primaryStorage_.size()) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "EditableTileMaps::tileMap(int)",
                                   index);
  }

  return primaryStorage_[index];
}

const TileMap& EditableTileMaps::tileMap(int index) const {
  if (index >= primaryStorage_.size()) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "EditableTileMaps::tileMap(int)",
                                   index);
  }

  return primaryStorage_[index];
}

void EditableTileMaps::save(std::string& data) {
  Tbyte buffer[ByteSizes::uint32Size];
  
  SaveHelper saver(data,
                   DataChunkIDs::tileMaps,
                   versionNum_);
  
  // Number of tilemaps
  ByteConversion::toBytes(primaryStorage_.size(),
                          buffer,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint32Size);
  
  // Tilemap data
  for (int i = 0; i < primaryStorage_.size(); i++) {
    primaryStorage_[i].save(data);
  }
  
  // Index->address mapping
  indexToAddress_.save(data);
  
  saver.finalize();
}

int EditableTileMaps::load(const Tbyte* data) {
  int byteCount = 0;
  LoadHelper loader(data,
                    byteCount);
                    
  // Clear existing data
  primaryStorage_.clear();
  indexToAddress_.clear();
  
  // Get number of tilemaps
  int numTileMaps
    = ByteConversion::fromBytes(data + byteCount,
                                ByteSizes::uint32Size,
                                EndiannessTypes::little,
                                SignednessTypes::nosign);
  byteCount += ByteSizes::uint32Size;
  
  // Get tilemap data
  for (int i = 0; i < numTileMaps; i++) {
    TileMap tilemap;
    byteCount += tilemap.load(data + byteCount);
    primaryStorage_.push_back(tilemap);
  }
  
  // Get index->address mapping
  byteCount += indexToAddress_.load(data + byteCount);
  
  return byteCount;
}

void EditableTileMaps::exportToROM(WritableROM& rom) {
  // Write tilemaps to ROM
  for (int i = 0; i < primaryStorage_.size(); i++) {
    primaryStorage_[i].writeToData(rom.directWrite(indexToAddress_[i]));
  }
}


};
