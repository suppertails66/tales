#include "gamedata/TailsAdvData.h"
#include "gamedata/TailsAdvAddresses.h"
#include "gamedata/PrimaryMaps.h"
#include "gamedata/SubMaps.h"
#include "gamedata/TailsAdvFreeSpace.h"
#include "exception/InvalidLoadDataException.h"
#include "gamedata/TailsAdvBank0Hacks.h"
#include <iostream>

namespace Tales {


const Tbyte TailsAdvData::andMaskExpandAdjustValue[1] = { 0x3F };

TailsAdvData::TailsAdvData(LoadedROM& rom)
  : TailsAdvEditable(),
    romExpanded_(false),
  /* A VERY LONG SEQUENCE OF IMPORTS GOES HERE */
    standardPalettes_(rom,
                      TailsAdvAddresses::PaletteTable,
                      TailsAdvAddresses::NumPaletteTableEntries),
    paletteCycles_(rom),
    levelEffectsHeaders_(rom,
                         TailsAdvAddresses::MapEffectsTable,
                         TailsAdvAddresses::MapEffectsTableContent,
                         TailsAdvAddresses::MapEffectsTableEnd,
                         TailsAdvAddresses::NumMapEffectsTableEntries),
    levelPaletteHeaders_(rom,
                         TailsAdvAddresses::MapPaletteNumTable,
                         TailsAdvAddresses::MapPaletteNumTableContent,
                         TailsAdvAddresses::NumMapPaletteNumTableEntries,
                         SubMaps::subMapCounts,
                         PrimaryMaps::primaryMapTableSize),
    levelGraphicsData_(rom,
                      TailsAdvAddresses::MapGraphicsHeaderTable,
                      TailsAdvAddresses::MapGraphicsHeaderTableContent,
                      TailsAdvAddresses::NumMapGraphicsHeaderTableEntries,
                      TailsAdvAddresses::UncompressedGraphicsHeaders,
                      TailsAdvAddresses::NumUncompressedGraphicsHeaders,
                      TailsAdvAddresses::TailsGraphicHeaders,
                      TailsAdvAddresses::NumTailsGraphicHeaders,
                      TailsAdvAddresses::RemoteRobotGraphicHeaders,
                      TailsAdvAddresses::NumRemoteRobotGraphicHeaders),
    leafGraphicsTable_(rom,
                       TailsAdvAddresses::LeafGraphicsTable),
    waterSplashGraphicTable_(rom,
                             TailsAdvAddresses::WaterSplashGraphicTable,
                             SubMaps::subMapFixedGraphicTableCounts,
                             SubMaps::subMapFixedGraphicTableCountsSize),
    smokePuffGraphicTable_(rom,
                             TailsAdvAddresses::SmokePuffGraphicTable,
                             SubMaps::subMapFixedGraphicTableCounts,
                             SubMaps::subMapFixedGraphicTableCountsSize),
    spriteMappings_(rom,
                    TailsAdvAddresses::SpriteMappingsTable,
                    TailsAdvAddresses::NumSpriteMappingsTableObjects),
    musicAssignments_(rom,
                      TailsAdvAddresses::LevelMusicTable),
    radioMusic_(rom,
                TailsAdvAddresses::RadioMusicTable,
                TailsAdvAddresses::NumRadioMusicTableEntries),
    emeraldHealthRefills_(rom,
                          TailsAdvAddresses::EmeraldHealthRefillTable),
    powerUpData_(rom,
                 TailsAdvAddresses::PowerUpTable),
    metatileWidthMaps_(rom,
               TailsAdvAddresses::WidthMapTable,
               TailsAdvAddresses::NumWidthMaps),
    metatileHeightMaps_(rom,
               TailsAdvAddresses::HeightMapTable,
               TailsAdvAddresses::NumHeightMaps),
    slopeSpeedValues_(rom,
                      TailsAdvAddresses::SlopeSpeedTable,
                      TailsAdvAddresses::NumSlopeSpeedTableEntries),
    metatileBehaviors_(rom, TailsAdvAddresses::MetatileBehaviorTableContent),
    spawnPoints_(rom,
                 TailsAdvAddresses::TailsSpawnTable,
                 TailsAdvAddresses::TailsSpawnTableEnd),
    warpDestinations_(rom,
                 TailsAdvAddresses::WarpDestinationTable,
                 TailsAdvAddresses::WarpDestinationTableEnd),
    levelObjectEntryGroups_(rom,
                         TailsAdvAddresses::ObjectLayoutTable,
                         TailsAdvAddresses::ObjectLayoutTableContent,
                         TailsAdvAddresses::ObjectLayoutTableEnd,
                         TailsAdvAddresses::NumObjectLayoutTableEntries),
    mapData_(rom,
             TailsAdvAddresses::LevelHeaderTable,
             TailsAdvAddresses::LevelHeaderTableContent,
             TailsAdvAddresses::LevelHeaderTableContentEntries) { };
  
void TailsAdvData::save(std::string& data) {
  
  /* A VERY LONG SEQUENCE OF SAVES GOES HERE */
  
  SaveHelper saver(data,
                   DataChunkIDs::fileStart,
                   0);
  
  standardPalettes_.save(data);
  paletteCycles_.save(data);
  levelEffectsHeaders_.save(data);
  levelPaletteHeaders_.save(data);
  levelGraphicsData_.save(data);
  leafGraphicsTable_.save(data);
  waterSplashGraphicTable_.save(data);
  smokePuffGraphicTable_.save(data);
  spriteMappings_.save(data);
  musicAssignments_.save(data);
  radioMusic_.save(data);
  powerUpData_.save(data);
  emeraldHealthRefills_.save(data);
  metatileWidthMaps_.save(data);
  metatileHeightMaps_.save(data);
  slopeSpeedValues_.save(data);
  metatileBehaviors_.save(data);
  spawnPoints_.save(data);
  warpDestinations_.save(data);
  levelObjectEntryGroups_.save(data);
  mapData_.save(data);
  
  SaveHelper saver2(data,
                   DataChunkIDs::fileEnd,
                   0);
  
  saver2.finalize();
  
  saver.finalize();
}

int TailsAdvData::load(const Tbyte* data) {
  
  /* A VERY LONG SEQUENCE OF LOADS GOES HERE */
  
  int dataAddr = 0;
  
  LoadHelper loader(data,
                    dataAddr);
                    
  // Throw if load data is invalid
  if ((loader.id() != DataChunkIDs::fileStart)
      || (loader.version() != 0)) {
    throw InvalidLoadDataException(TALES_SRCANDLINE,
                                   "TailsAdvData::load(const Tbyte*)");
  }
  
  loader.readHeader(data + dataAddr);
  while (loader.id() != DataChunkIDs::fileEnd) {
    // Load appropriate data
    switch (loader.id()) {
    case DataChunkIDs::standardPalettes:
      dataAddr += standardPalettes_.load(data + dataAddr);
      break;
    case DataChunkIDs::paletteCycles:
      dataAddr += paletteCycles_.load(data + dataAddr);
      break;
    case DataChunkIDs::levelEffectsHeaders:
      dataAddr += levelEffectsHeaders_.load(data + dataAddr);
      break;
    case DataChunkIDs::levelPaletteHeaders:
      dataAddr += levelPaletteHeaders_.load(data + dataAddr);
      break;
    case DataChunkIDs::levelGraphicsData:
      dataAddr += levelGraphicsData_.load(data + dataAddr);
      break;
    case DataChunkIDs::leafGraphicsTable:
      dataAddr += leafGraphicsTable_.load(data + dataAddr);
      break;
    case DataChunkIDs::waterSplashGraphicTable:
      dataAddr += waterSplashGraphicTable_.load(data + dataAddr);
      break;
    case DataChunkIDs::smokePuffGraphicTable:
      dataAddr += smokePuffGraphicTable_.load(data + dataAddr);
      break;
    case DataChunkIDs::spriteMappings:
      dataAddr += spriteMappings_.load(data + dataAddr);
      break;
    case DataChunkIDs::musicAssignments:
      dataAddr += musicAssignments_.load(data + dataAddr);
      break;
    case DataChunkIDs::radioMusic:
      dataAddr += radioMusic_.load(data + dataAddr);
      break;
    case DataChunkIDs::powerUpData:
      dataAddr += powerUpData_.load(data + dataAddr);
      break;
    case DataChunkIDs::emeraldHealthRefills:
      dataAddr += emeraldHealthRefills_.load(data + dataAddr);
      break;
    case DataChunkIDs::metatileWidthMaps:
      dataAddr += metatileWidthMaps_.load(data + dataAddr);
      break;
    case DataChunkIDs::metatileHeightMaps:
      dataAddr += metatileHeightMaps_.load(data + dataAddr);
      break;
    case DataChunkIDs::slopeSpeedValues:
      dataAddr += slopeSpeedValues_.load(data + dataAddr);
      break;
    case DataChunkIDs::metatileBehaviors:
      dataAddr += metatileBehaviors_.load(data + dataAddr);
      break;
    case DataChunkIDs::spawnPoints:
      dataAddr += spawnPoints_.load(data + dataAddr);
      break;
    case DataChunkIDs::warpDestinations:
      dataAddr += warpDestinations_.load(data + dataAddr);
      break;
    case DataChunkIDs::levelObjectEntryGroups:
      dataAddr += levelObjectEntryGroups_.load(data + dataAddr);
      break;
    case DataChunkIDs::mapData:
      dataAddr += mapData_.load(data + dataAddr);
      break;
    default:
      std::cerr << "ERROR: unrecognized chunk type "
        << loader.id() << ": skipping" << std::endl;
      loader.readHeader(data,
                        dataAddr);
      dataAddr += loader.size();
      break;
    }
    
//    std::cout << std::hex << dataAddr << std::endl;
    
    // Read header (but do not advance getpos; we want the chunk we load
    // to be able to reread it)
    loader.readHeader(data + dataAddr);
  }
  
  // Skip fileEnd marker
  loader.readHeader(data,
                    dataAddr);
//  dataAddr += loader.size();
  
/*  dataAddr += standardPalettes_.load(data + dataAddr);
  dataAddr += paletteCycles_.load(data + dataAddr);
  dataAddr += levelEffectsHeaders_.load(data + dataAddr);
  dataAddr += levelPaletteHeaders_.load(data + dataAddr);
  dataAddr += levelGraphicsData_.load(data + dataAddr);
  dataAddr += spriteMappings_.load(data + dataAddr);
  dataAddr += musicAssignments_.load(data + dataAddr);
  dataAddr += radioMusic_.load(data + dataAddr);
  dataAddr += powerUpData_.load(data + dataAddr);
  dataAddr += emeraldHealthRefills_.load(data + dataAddr);
  dataAddr += metatileWidthMaps_.load(data + dataAddr);
  dataAddr += metatileHeightMaps_.load(data + dataAddr);
  dataAddr += slopeSpeedValues_.load(data + dataAddr);
  dataAddr += metatileBehaviors_.load(data + dataAddr);
  dataAddr += spawnPoints_.load(data + dataAddr);
  dataAddr += warpDestinations_.load(data + dataAddr);
  dataAddr += levelObjectEntryGroups_.load(data + dataAddr);
  dataAddr += mapData_.load(data + dataAddr); */
  
  return dataAddr;
}

void TailsAdvData::exportToROM(WritableROM& rom) {
  
  /* A VERY LONG SEQUENCE OF EXPORTS GOES HERE */
  
  standardPalettes_.exportToROM(rom);
  paletteCycles_.exportToROM(rom);
  levelEffectsHeaders_.exportToROM(rom);
  levelPaletteHeaders_.exportToROM(rom);
  levelGraphicsData_.exportToROM(rom);
  leafGraphicsTable_.exportToROM(rom);
  waterSplashGraphicTable_.exportToROM(rom);
  smokePuffGraphicTable_.exportToROM(rom);
  spriteMappings_.exportToROM(rom);
  musicAssignments_.exportToROM(rom);
  radioMusic_.exportToROM(rom);
  powerUpData_.exportToROM(rom);
  emeraldHealthRefills_.exportToROM(rom);
  metatileWidthMaps_.exportToROM(rom);
  metatileHeightMaps_.exportToROM(rom);
  slopeSpeedValues_.exportToROM(rom);
  metatileBehaviors_.exportToROM(rom);
  spawnPoints_.exportToROM(rom);
  warpDestinations_.exportToROM(rom);
  levelObjectEntryGroups_.exportToROM(rom);
  mapData_.exportToROM(rom);
  
  // If the ROM has been expanded, there are now 0x40 rather than 0x20
  // valid banks. However, there are a handful of pieces of code that
  // mask a value by 0x1F to obtain a bank number. We need to adjust these
  // to 0x3F or the program will be unable to access the new banks.
  rom.directWrite(andMaskExpandAdjustAddress1,
                  andMaskExpandAdjustValue,
                  1);
  rom.directWrite(andMaskExpandAdjustAddress2,
                  andMaskExpandAdjustValue,
                  1);

  
}

void TailsAdvData::exportToFile(LoadedROM& rom,
                                const std::string& filename) {
  // Create writable ROM to export data to
  WritableROM writerom(rom,
                       FreeSpaceListing(
                        TailsAdvFreeSpace::freeSpace,
                        TailsAdvFreeSpace::numFreeSpacePairs));
  
  // If ROM expansion enabled, double size
  if (romExpanded_) {
    writerom.doubleROMSize();
  }
  
  // Write data to ROM
  exportToROM(writerom);
  
  // Write ROM to file
  writerom.writeToFile(filename);
}

bool TailsAdvData::romExpanded() const {
  return romExpanded_;
}

void TailsAdvData::setRomExpanded(bool romExpanded__) {
  romExpanded_ = romExpanded__;
}

EditableStandardPalettes& TailsAdvData::standardPalettes() {
  return standardPalettes_;
}

EditablePaletteCycles& TailsAdvData::paletteCycles() {
  return paletteCycles_;
}

EditableLevelEffectsHeaders& TailsAdvData::levelEffectsHeaders() {
  return levelEffectsHeaders_;
}

EditableLevelPaletteHeaders& TailsAdvData::levelPaletteHeaders() {
  return levelPaletteHeaders_;
}

EditableLevelGraphicsData& TailsAdvData::levelGraphicsData() {
  return levelGraphicsData_;
}

EditableLeafGraphicsTable& TailsAdvData::leafGraphicsTable() {
  return leafGraphicsTable_;
}

EditableWaterSplashGraphicTable& TailsAdvData::waterSplashGraphicTable() {
  return waterSplashGraphicTable_;
}

EditableSmokePuffGraphicTable& TailsAdvData::smokePuffGraphicTable() {
  return smokePuffGraphicTable_;
}

EditableSpriteMappings& TailsAdvData::spriteMappings() {
  return spriteMappings_;
}

EditableMusicAssignments& TailsAdvData::musicAssignments() {
  return musicAssignments_;
}

EditableRadioMusic& TailsAdvData::radioMusic() {
  return radioMusic_;
}

EditablePowerUpData& TailsAdvData::powerUpData() {
  return powerUpData_;
}

EditableEmeraldHealthRefills& TailsAdvData::emeraldHealthRefills() {
  return emeraldHealthRefills_;
}

EditableMetatileWidthMaps& TailsAdvData::metatileWidthMaps() {
  return metatileWidthMaps_;
}

EditableMetatileHeightMaps& TailsAdvData::metatileHeightMaps() {
  return metatileHeightMaps_;
}

EditableSlopeSpeedValues& TailsAdvData::slopeSpeedValues() {
  return slopeSpeedValues_;
}

EditableMetatileBehaviors& TailsAdvData::metatileBehaviors() {
  return metatileBehaviors_;
}

EditableSpawnPoints& TailsAdvData::spawnPoints() {
  return spawnPoints_;
}

EditableWarpDestinations& TailsAdvData::warpDestinations() {
  return warpDestinations_;
}

EditableLevelObjectEntryGroups& TailsAdvData::levelObjectEntryGroups() {
  return levelObjectEntryGroups_;
}

EditableMapData& TailsAdvData::mapData() {
  return mapData_;
}


};
