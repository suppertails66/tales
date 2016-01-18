#include "editors/TailsAdvEditor.h"
#include "exception/InvalidLoadDataException.h"
#include "gamedata/TailsAdvBank0Hacks.h"
#include "gamedata/TailsAdvFreeSpace.h"
#include "util/IniFile.h"
#include <exception>
#include <fstream>
#include <iostream>

using namespace Luncheon;

namespace Tales {


TailsAdvEditor::TailsAdvEditor(const std::string& romFileName)
  : rom_(romFileName),
    data_(rom_),
    levelEditor_(data_.levelEffectsHeaders(),
                 data_.levelGraphicsData(),
                 data_.levelObjectEntryGroups(),
                 data_.levelPaletteHeaders(),
                 data_.mapData(),
                 data_.metatileBehaviors(),
                 data_.metatileHeightMaps(),
                 data_.metatileWidthMaps(),
                 data_.spawnPoints(),
                 data_.spriteMappings(),
                 data_.standardPalettes(),
                 data_.warpDestinations(),
                 metadata_),
    vramEditor_(data_.levelGraphicsData(),
                data_.levelPaletteHeaders(),
                data_.standardPalettes(),
                data_.leafGraphicsTable(),
                data_.smokePuffGraphicTable(),
                data_.waterSplashGraphicTable(),
                metadata_),
    metatileBehaviorEditor_(data_.metatileBehaviors(),
                            data_.metatileWidthMaps(),
                            data_.metatileHeightMaps(),
                            data_.slopeSpeedValues()),
    lengthMapEditor_(data_.metatileWidthMaps(),
                     data_.metatileHeightMaps(),
                     data_.slopeSpeedValues()),
    paletteEditor_(data_.standardPalettes()),
    metatileStructureEditor_(
                            metadata_.metatileStructureDefaults(),
                            data_.mapData().metatileStructures(),
                            data_.levelGraphicsData(),
                            data_.standardPalettes()),
    graphicsEditor_(data_.levelGraphicsData(),
                    data_.standardPalettes(),
                    data_.spriteMappings(),
                    metadata_),
    powerUpEditor_(data_.powerUpData(),
                   data_.emeraldHealthRefills()),
    musicEditor_(data_.musicAssignments(),
                 data_.radioMusic()),
    paletteCycleEditor_(data_.paletteCycles()),
    enhancementsEditor_(metadata_) {
  
  /* Expand the ROM regardless of anything else.
     This is theoretically temporary until some inconsistencies
     in the way the game compresses some of its data are resolved,
     but don't hold your breath. */
  data_.setRomExpanded(true);
  
//  for (int i = 0; i < 0x0F; i++) {
//    std::cout << std::hex << i << ": " << std::endl;
//    std::cout << '\t' << data_.leafGraphicsTable().entry(i) << std::endl;
//  }
}
  
void TailsAdvEditor::save(std::string& data) {
  SaveHelper saver(data,
                   DataChunkIDs::tailsAdvEditorStart,
                   versionNum_);
  
  metadata_.save(data);
  data_.save(data);
  
  SaveHelper saver2(data,
                   DataChunkIDs::tailsAdvEditorEnd,
                   versionNum_);
  saver2.finalize();
  
  saver.finalize();
  
//  IniFile test;
//  test.setValue("Global", "SourceRomPath", "./tailsadv.gg");
//  test.setValue("Global", "NNNN", "waetawetn e we ret ewat ");
//  test.setValue("Section2", "test", "nAAAAAAAAAAA");
//  test.writeFile("test.ini");
}

int TailsAdvEditor::load(const Tbyte* data) {
  int byteCount = 0;
  
  LoadHelper loader(data,
                    byteCount);
                    
  // Throw if load data is invalid
  if ((loader.id() != DataChunkIDs::tailsAdvEditorStart)
      || (loader.version() > versionNum_)) {
    throw InvalidLoadDataException(TALES_SRCANDLINE,
                                   "TailsAdvEditor::load(const Tbyte*)");
  }
  
  loader.readHeader(data + byteCount);
  while (loader.id() != DataChunkIDs::tailsAdvEditorEnd) {
    // Load appropriate data
    switch (loader.id()) {
    case DataChunkIDs::editorMetadata:
      byteCount += metadata_.load(data + byteCount);
      break;
    case DataChunkIDs::fileStart:
      byteCount += data_.load(data + byteCount);
      break;
    default:
      std::cerr << "ERROR: unrecognized chunk type "
        << loader.id() << ": skipping" << std::endl;
      loader.readHeader(data,
                        byteCount);
      byteCount += loader.size();
      break;
    }
    
//    std::cout << std::hex << dataAddr << std::endl;
    
    // Read header (but do not advance getpos; we want the chunk we load
    // to be able to reread it)
    loader.readHeader(data + byteCount);
  }
  
//  IniFile test("test.ini");
//  std::cout << test.hasKey("Global", "SourceRomPath") << std::endl;
//  std::cout << test.valueOfKey("Global", "SourceRomPath") << std::endl;
//  std::cout << test.valueOfKey("Global", "NNNN") << std::endl;
//  std::cout << test.valueOfKey("Section2", "test") << std::endl;
                    
  return byteCount;
}
  
void TailsAdvEditor::saveToFile(const std::string& filename) {
  std::string saveData;
  save(saveData);
  
  std::ofstream ofs(filename.c_str(),
                    std::ios_base::binary
                      | std::ios_base::trunc);
  ofs.write(saveData.c_str(), saveData.size());
}
  
void TailsAdvEditor::loadFromFile(const std::string& filename) {
  std::ifstream ifs(filename.c_str(),
                    std::ios_base::binary);
  ifs.seekg(0, std::ios_base::end);
  int fileSize = ifs.tellg();
  ifs.seekg(0, std::ios_base::beg);
                    
  Tbyte* data = new Tbyte[fileSize];
  ifs.read((char*)data, fileSize);
  
  try {
  
  load(data);
  
  }
  catch (std::exception& e) {
    delete data;
    throw e;
  }
  
  delete data;
}
  
void TailsAdvEditor::exportToFile(const std::string& filename) {
//  data_.exportToFile(rom_,
//                     filename);

  // Create writable ROM to export data to
  WritableROM writerom(rom_,
                       FreeSpaceListing(
                        TailsAdvFreeSpace::freeSpace,
                        TailsAdvFreeSpace::numFreeSpacePairs));
  
  // If ROM expansion enabled, double size
  if (data_.romExpanded()) {
    writerom.doubleROMSize();
  }
  
  // Write data to ROM
  data_.exportToROM(writerom);
  
  // Write enhancements to ROM
  metadata_.hackSettings().exportToROM(writerom);
  
  // Write ROM to file
  writerom.writeToFile(filename);
}
  
int TailsAdvEditor::versionNum() {
  return versionNum_;
}
  
EditorMetadata& TailsAdvEditor::metadata() {
  return metadata_;
}
  
LevelEditor& TailsAdvEditor::levelEditor() {
  return levelEditor_;
}
  
LevelVRAMEditor& TailsAdvEditor::vramEditor() {
  return vramEditor_;
}
  
MetatileBehaviorEditor& TailsAdvEditor::metatileBehaviorEditor() {
  return metatileBehaviorEditor_;
}
  
LengthMapEditor& TailsAdvEditor::lengthMapEditor() {
  return lengthMapEditor_;
}
  
PaletteEditor& TailsAdvEditor::paletteEditor() {
  return paletteEditor_;
}
  
MetatileStructureEditor& TailsAdvEditor::metatileStructureEditor() {
  return metatileStructureEditor_;
}
  
GraphicsEditor& TailsAdvEditor::graphicsEditor() {
  return graphicsEditor_;
}
  
PowerUpEditor& TailsAdvEditor::powerUpEditor() {
  return powerUpEditor_;
}
  
MusicEditor& TailsAdvEditor::musicEditor() {
  return musicEditor_;
}
  
PaletteCycleEditor& TailsAdvEditor::paletteCycleEditor() {
  return paletteCycleEditor_;
}
  
EnhancementsEditor& TailsAdvEditor::enhancementsEditor() {
  return enhancementsEditor_;
}


};
