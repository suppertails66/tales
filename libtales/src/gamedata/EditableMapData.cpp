#include "gamedata/EditableMapData.h"
#include "exception/UnrecognizedVersionException.h"

namespace Tales {


EditableMapData::EditableMapData() { };

EditableMapData::EditableMapData(
                LoadedROM& rom,
                Taddress levelHeaderTableAddress,
                Taddress levelHeaderTableContentAddress,
                int numLevelHeaderTableEntries)
  : rawLevelHeaders_(rom,
                     levelHeaderTableAddress,
                     levelHeaderTableContentAddress,
                     numLevelHeaderTableEntries),
    yTableAddresses_(rawLevelHeaders_),
    metatileStructures_(rom,
                        rawLevelHeaders_),
    mapLayouts_(rom,
                rawLevelHeaders_),
    levelHeaders_(rom,
                  levelHeaderTableAddress,
                  rawLevelHeaders_,
                  metatileStructures_,
                  mapLayouts_,
                  yTableAddresses_) { };
                  
void EditableMapData::save(std::string& data) {
  // rawLevelHeaders_ is used only for the initial load from ROM; we don't
  // need to save it
  SaveHelper saver(data,
                   DataChunkIDs::mapData,
                   0);
  
  yTableAddresses_.save(data);  
  
  metatileStructures_.save(data);
  mapLayouts_.save(data);
  levelHeaders_.save(data);
  
  saver.finalize();
}

int EditableMapData::load(const Tbyte* data) {
  int byteCount = 0;
  LoadHelper loader(data,
                    byteCount);
                    
  if (loader.version() > 0) {
    throw UnrecognizedVersionException(TALES_SRCANDLINE,
                                       "EditableMapData::load("
                                       "const Tbyte*)",
                                       DataChunkIDs::mapData,
                                       "EditableMapData",
                                       loader.version(),
                                       0);
  }

  byteCount += yTableAddresses_.load(data + byteCount);
  
  byteCount += metatileStructures_.load(data + byteCount);
  byteCount += mapLayouts_.load(data + byteCount);
  byteCount += levelHeaders_.load(data + byteCount);
  
  return byteCount;
}

void EditableMapData::exportToROM(WritableROM& rom) {

  metatileStructures_.exportToROM(rom);
  
  mapLayouts_.exportToROM(rom);
  
  levelHeaders_.exportToROM(rom,
                            metatileStructures_,
                            mapLayouts_,
                            yTableAddresses_);
}
  
MetatileStructures& EditableMapData::metatileStructures() {
  return metatileStructures_;
}

MapLayouts& EditableMapData::mapLayouts() {
  return mapLayouts_;
}

LevelHeaders& EditableMapData::levelHeaders() {
  return levelHeaders_;
}


};
