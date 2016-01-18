#include "editors/EditorMetadata.h"
#include "gamedata/PrimaryMaps.h"
#include "gamedata/SubMaps.h"
#include "editors/GraphicToInfo.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"
#include <iostream>

using namespace Luncheon;

namespace Tales {


EditorMetadata::EditorMetadata()
  : levelMetadata_(SubMaps::subMapCounts,
                   SubMaps::subMapCountsSize) {
  initializeDefaults();
}

void EditorMetadata::save(std::string& data) {
  SaveHelper saver(data,
                   DataChunkIDs::editorMetadata,
                   versionNum_);
                   
  Tbyte buffer[ByteSizes::uint32Size];
  
  // Number of area metadata entries
  ByteConversion::toBytes(areaMetadata_.size(),
                          buffer,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint32Size);
                   
  // Area metadata
  for (int i = 0; i < areaMetadata_.size(); i++) {
    areaMetadata_[i].save(data);
  }
  
  // Number of metatile structure defaults
  ByteConversion::toBytes(metatileStructureDefaults_.size(),
                          buffer,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint32Size);
  
  // Metatile structure defaults
  for (MetatileStructureDefaultMap::iterator it
          = metatileStructureDefaults_.begin();
       it != metatileStructureDefaults_.end();
       it++) {
    // Key
    ByteConversion::toBytes(it->first,
                            buffer,
                            ByteSizes::uint32Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    data += std::string((char*)buffer, ByteSizes::uint32Size);
    
    // Graphic
    ByteConversion::toBytes(it->second.graphicIndex_,
                            buffer,
                            ByteSizes::uint32Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    data += std::string((char*)buffer, ByteSizes::uint32Size);
    
    // Palette
    ByteConversion::toBytes(it->second.paletteIndex_,
                            buffer,
                            ByteSizes::uint32Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    data += std::string((char*)buffer, ByteSizes::uint32Size);
    
    if (versionNum_ >= 1) {
      // Palette1
      ByteConversion::toBytes(it->second.palette1Index_,
                              buffer,
                              ByteSizes::uint32Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign);
      data += std::string((char*)buffer, ByteSizes::uint32Size);
    }
  }
  
  saveGraphicPaletteDefaultMap(data,
                               compressedGraphicPaletteDefaults_);
  
  saveGraphicPaletteDefaultMap(data,
                               uncompressedGraphicPaletteDefaults_);
                               
  // Hack settings
  hackSettings_.save(data);
  
  // Export file location
  SaveHelper::saveString(data,
                         exportFileLocation_);
                   
  saver.finalize();
}
  
int EditorMetadata::load(const Tbyte* data) {
  int byteCount = 0;
  
  LoadHelper loader(data + byteCount,
                    byteCount);
  
  // Area metadata
  
  int numAreaMetadataEntries = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint32Size;
  
  for (int i = 0; i < numAreaMetadataEntries; i++) {
    AreaMetadataEntry entry;
    byteCount += entry.load(data + byteCount);
  }
  
  // Number of metatile structure defaults
  int numMetatileStructureDefaults = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint32Size;
  
  // Metatile structure defaults
  for (int i = 0; i < numMetatileStructureDefaults; i++) {
    // Key
    int defaultKey = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
    byteCount += ByteSizes::uint32Size;
    
    // Graphic
    int graphic = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
    byteCount += ByteSizes::uint32Size;
    
    // Palette
    int palette = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
    byteCount += ByteSizes::uint32Size;
    
    int palette1 = 0;
    if (loader.version() >= 1) {
      // Palette1
      palette1 = ByteConversion::fromBytes(
                            data + byteCount,
                            ByteSizes::uint32Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
      byteCount += ByteSizes::uint32Size;
    }
      
    metatileStructureDefaults_[defaultKey]
      = MetatileStructureDefault(graphic, palette, palette1);
  }
  
  byteCount += loadGraphicPaletteDefaultMap(
                               compressedGraphicPaletteDefaults_,
                               data + byteCount);
  
  byteCount += loadGraphicPaletteDefaultMap(
                               uncompressedGraphicPaletteDefaults_,
                               data + byteCount);
                               
  // Hack settings
  byteCount += hackSettings_.load(data + byteCount);
  
  // Export file location
  byteCount += LoadHelper::loadString(data + byteCount,
                                      exportFileLocation_);
  
  return byteCount;
}
  
std::string EditorMetadata::exportFileLocation() {
  return exportFileLocation_;
}

void EditorMetadata
    ::setExportFileLocation(const std::string& exportFileLocation__) {
  exportFileLocation_ = exportFileLocation__;
}
  
MetatileStructureDefaultMap& EditorMetadata
    ::metatileStructureDefaults() {
  return metatileStructureDefaults_;
}
  
AreaMetadataEntry& EditorMetadata::areaMetadata(int areaNum) {
  return areaMetadata_[areaNum];
}

AreaMetadataMap& EditorMetadata::areaMetadataMap() {
  return areaMetadata_;
}

void EditorMetadata::initializeDefaults() {
  initializeAreaDefaults();
  initializeLevelDefaults();
  initializeMetatileStructureDefaults();
  initializeGraphicPaletteDefaults();
}

void EditorMetadata::initializeAreaDefaults() {
  // Area 0x00: invalid
  areaMetadata_.push_back(AreaMetadataEntry());
  // Area 0x01: Poloy Forest
  areaMetadata_.push_back(AreaMetadataEntry("Poloy Forest"));
  areaMetadata_.push_back(AreaMetadataEntry("Caron Forest"));
  areaMetadata_.push_back(AreaMetadataEntry("Volcanic Tunnel"));
  areaMetadata_.push_back(AreaMetadataEntry("Polly Mt. 1"));
  areaMetadata_.push_back(AreaMetadataEntry("Polly Mt. 2"));
  areaMetadata_.push_back(AreaMetadataEntry("Lake Rocky"));
  areaMetadata_.push_back(AreaMetadataEntry("Lake Crystal"));
  areaMetadata_.push_back(AreaMetadataEntry("Green Island"));
  areaMetadata_.push_back(AreaMetadataEntry("Cavern Island"));
  areaMetadata_.push_back(AreaMetadataEntry("Coco Island"));
  areaMetadata_.push_back(AreaMetadataEntry("Battle Fortress 1"));
  areaMetadata_.push_back(AreaMetadataEntry("Battle Fortress 2"));
  areaMetadata_.push_back(AreaMetadataEntry());
  areaMetadata_.push_back(AreaMetadataEntry());
  areaMetadata_.push_back(AreaMetadataEntry());
  areaMetadata_.push_back(AreaMetadataEntry("World map"));
  areaMetadata_.push_back(AreaMetadataEntry("Tails' House"));
  areaMetadata_.push_back(AreaMetadataEntry());
  areaMetadata_.push_back(AreaMetadataEntry("Intro"));
  areaMetadata_.push_back(AreaMetadataEntry("Leave dock cutscene"));
  areaMetadata_.push_back(AreaMetadataEntry("Return to dock cutscene"));
}

void EditorMetadata::initializeLevelDefaults() {
  
}
  
void EditorMetadata::initializeMetatileStructureDefaults() {
  metatileStructureDefaults_[0]
	= MetatileStructureDefault(65, 7, 4);  // Poloy/Caron
  metatileStructureDefaults_[1]
	= MetatileStructureDefault(70, 9, 4 );  // Volcanic Tunnel
  metatileStructureDefaults_[2]
	= MetatileStructureDefault(66, 10, 4 ); // Polly Mt. 1
  metatileStructureDefaults_[3]
	= MetatileStructureDefault(70, 12, 4 ); // Polly Mt. 2
  metatileStructureDefaults_[4]
	= MetatileStructureDefault(72, 13, 4 ); // Lake Rocky
  metatileStructureDefaults_[5]
	= MetatileStructureDefault(79, 15, 4 ); // Lake Rocky boss
  metatileStructureDefaults_[6]
	= MetatileStructureDefault(72, 17, 4 ); // Lake Crystal
  metatileStructureDefaults_[7]
	= MetatileStructureDefault(65, 20, 4 ); // Green Island
  metatileStructureDefaults_[8]
	= MetatileStructureDefault(70, 21, 4 ); // Cavern Island
  metatileStructureDefaults_[9]
	= MetatileStructureDefault(70, 22, 39 ); // Cavern Island boss
  metatileStructureDefaults_[10]
	= MetatileStructureDefault(76, 23, 4 );// Coco Island
  metatileStructureDefaults_[11]
	= MetatileStructureDefault(77, 24, 4 );// Battle Fortress 1
  metatileStructureDefaults_[12]
	= MetatileStructureDefault(76, 25, 4 );// Battle Fortress 2
  metatileStructureDefaults_[13]
	= MetatileStructureDefault(68, 28, 29 );// program-generated
                                          // set for world map
}
  
void EditorMetadata::initializeGraphicPaletteDefaults() {
  for (int i = 0; i < GraphicToInfo::numCompressedGraphicInfos; i++) {
    switch (i) {
    case 34:  // world map objects
      compressedGraphicPaletteDefaults_[i]
        = GraphicPaletteDefaultEntry(29);
      break;
    case 43:  // coco island boss
      compressedGraphicPaletteDefaults_[i]
        = GraphicPaletteDefaultEntry(40);
      break;
    case 51:  // cavern island boss
    case 52:
      compressedGraphicPaletteDefaults_[i]
        = GraphicPaletteDefaultEntry(39);
      break;
    case 63:  // sega logo
      compressedGraphicPaletteDefaults_[i]
        = GraphicPaletteDefaultEntry(1);
      break;
    case 64:  // level select font
      compressedGraphicPaletteDefaults_[i]
        = GraphicPaletteDefaultEntry(2);
      break;
    case 65:  // forest
      compressedGraphicPaletteDefaults_[i]
        = GraphicPaletteDefaultEntry(7);
      break;
    case 66:  // mountain
      compressedGraphicPaletteDefaults_[i]
        = GraphicPaletteDefaultEntry(10);
      break;
    case 67:  // title screen
      compressedGraphicPaletteDefaults_[i]
        = GraphicPaletteDefaultEntry(26);
      break;
    case 68:  // world map tilemap
      compressedGraphicPaletteDefaults_[i]
        = GraphicPaletteDefaultEntry(28);
      break;
    case 69:  // tails house
      compressedGraphicPaletteDefaults_[i]
        = GraphicPaletteDefaultEntry(35);
      break;
    case 70:  // tunnel
      compressedGraphicPaletteDefaults_[i]
        = GraphicPaletteDefaultEntry(9);
      break;
    case 71:  // cavern island boss tilemap
      compressedGraphicPaletteDefaults_[i]
        = GraphicPaletteDefaultEntry(22);
      break;
    case 72:  // water
      compressedGraphicPaletteDefaults_[i]
        = GraphicPaletteDefaultEntry(13);
      break;
    case 73:  // password
      compressedGraphicPaletteDefaults_[i]
        = GraphicPaletteDefaultEntry(35);
      break;
    case 75:  // game over
      compressedGraphicPaletteDefaults_[i]
        = GraphicPaletteDefaultEntry(38);
      break;
    case 76:  // fortress
      compressedGraphicPaletteDefaults_[i]
        = GraphicPaletteDefaultEntry(23);
      break;
    case 77:  // flight
      compressedGraphicPaletteDefaults_[i]
        = GraphicPaletteDefaultEntry(24);
      break;
    case 78:  // credits
      compressedGraphicPaletteDefaults_[i]
        = GraphicPaletteDefaultEntry(37);
      break;
    case 79:  // lake rocky boss
      compressedGraphicPaletteDefaults_[i]
        = GraphicPaletteDefaultEntry(15);
      break;
    case 80:  // tails house EN
      compressedGraphicPaletteDefaults_[i]
        = GraphicPaletteDefaultEntry(35);
      break;
    default:
      compressedGraphicPaletteDefaults_[i]
        = GraphicPaletteDefaultEntry(4);
      break;
    }
  }
  
  for (int i = 0; i < GraphicToInfo::numUncompressedGraphicInfos; i++) {
    // JP title cards
    if ((i >= 204) && (i < 217)) {
      uncompressedGraphicPaletteDefaults_[i]
        = GraphicPaletteDefaultEntry(29);
    }
    // Water cycle
    else if ((i >= 226) && (i < 230)) {
      uncompressedGraphicPaletteDefaults_[i]
        = GraphicPaletteDefaultEntry(17);
    }
    // Lake Crystal water cycle
    else if ((i >= 226) && (i < 230)) {
      uncompressedGraphicPaletteDefaults_[i]
        = GraphicPaletteDefaultEntry(17);
    }
    // Conveyor cycle
    else if ((i >= 230) && (i < 232)) {
      uncompressedGraphicPaletteDefaults_[i]
        = GraphicPaletteDefaultEntry(23);
    }
    // EN title cards
    else if ((i >= 258) && (i < 271)) {
      uncompressedGraphicPaletteDefaults_[i]
        = GraphicPaletteDefaultEntry(29);
    }
    // Cavern Island boss dupe?
    else if ((i >= 271) && (i < 272)) {
      uncompressedGraphicPaletteDefaults_[i]
        = GraphicPaletteDefaultEntry(21);
    }
    else {
      uncompressedGraphicPaletteDefaults_[i]
        = GraphicPaletteDefaultEntry(4);
    }
  }
}

bool EditorMetadata::areaNumIsValid(int areaNum) {
  if ((areaNum < areaNumBase)
      || (areaNum >= areaNumLimit)
      || (areaNum == 0x0D)
      || (areaNum == 0x0E)
      || (areaNum == 0x0F)
      || (areaNum == 0x12)) {
    return false;
  }
  
  return true;
}

bool EditorMetadata::areaNumHasEditableLevels(int areaNum) {
  if (!areaNumIsValid(areaNum)) {
    return false;
  }
  
  // Don't allow world map or Tails' house
  if ((areaNum == 0x10)
      || (areaNum == 0x11)) {
    return false;
  }
  
  return true;
}

bool EditorMetadata::areaNumHasVRAMIndices(int areaNum) {
  if ((!areaNumIsValid(areaNum))
      || (!areaNumHasEditableLevels(areaNum))) {
    return false;
  }
  
  if ((areaNum >= 0x0D)) {
    return false;
  }
  
  return true;
}
  
void EditorMetadata::saveGraphicPaletteDefaultMap(
                  std::string& data,
                  GraphicPaletteDefaultMap& src) {
  Tbyte buffer[ByteSizes::uint32Size];
  
  // Number of entries
  ByteConversion::toBytes(src.size(),
                          buffer,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint32Size);
  
  for (GraphicPaletteDefaultMap::iterator it = src.begin();
       it != src.end();
       it++) {
    // Key
    ByteConversion::toBytes(it->first,
                            buffer,
                            ByteSizes::uint32Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    data += std::string((char*)buffer, ByteSizes::uint32Size);
    
    // Palette
    ByteConversion::toBytes(it->second.paletteNum(),
                            buffer,
                            ByteSizes::uint32Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    data += std::string((char*)buffer, ByteSizes::uint32Size);
  }
}

int EditorMetadata::loadGraphicPaletteDefaultMap(
                  GraphicPaletteDefaultMap& dst,
                  const Tbyte* data) {
  int byteCount = 0;
                  
  // Number of defaults
  int numDefaults = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint32Size;
  
  // Defaults
  for (int i = 0; i < numDefaults; i++) {
    // Key
    int defaultKey = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
    byteCount += ByteSizes::uint32Size;
    
    // Palette
    int paletteNum = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
    byteCount += ByteSizes::uint32Size;
    
    dst[defaultKey]
      = GraphicPaletteDefaultEntry(paletteNum);
  }
  
  return byteCount;
}
  
GraphicPaletteDefaultMap& EditorMetadata
    ::compressedGraphicPaletteDefaults() {
  return compressedGraphicPaletteDefaults_;
}

GraphicPaletteDefaultMap& EditorMetadata
    ::uncompressedGraphicPaletteDefaults() {
  return uncompressedGraphicPaletteDefaults_;
}
  
HackSettings& EditorMetadata::hackSettings() {
  return hackSettings_;
}


};
