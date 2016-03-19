#include "editors/HackSettings.h"
#include "structs/SaveHelper.h"
#include "structs/LoadHelper.h"
#include "gamedata/TailsAdvBank0Hacks.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"
#include <iostream>

using namespace Luncheon;

namespace Tales {


HackSettings::HackSettings()
  : doubleJumpFixOption_(doubleJumpFixOff),
    maxHeightFixOption_(maxHeightFixOff),
    bombJumpFixOption_(bombJumpFixOff),
    inventoryHackOption_(inventoryHackOff),
    flightHackOption_(flightHackOff),
    noGameOverHackOption_(noGameOverHackOff),
    saveHackOption_(saveHackOff),
    startOnLevelHackOption_(startOnLevelHackOff),
    startOnLevelHackArea_(1),
    startOnLevelHackMap_(1),
    startOnLevelHackSpawn_(0),
    startingItemHackOption_(startingItemHackOff),
    startingItemHackID_(0x01),
    startingItemHackSFID_(0x13) { };
  
void HackSettings::save(std::string& data) {
  SaveHelper saver(data,
                   DataChunkIDs::hackSettings,
                   versionNum_);
                   
  Tbyte buffer[ByteSizes::uint32Size];
  
  ByteConversion::toBytes(doubleJumpFixOption_,
                          buffer,
                          ByteSizes::uint8Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)(buffer), ByteSizes::uint8Size);
  
  ByteConversion::toBytes(maxHeightFixOption_,
                          buffer,
                          ByteSizes::uint8Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)(buffer), ByteSizes::uint8Size);
  
  ByteConversion::toBytes(bombJumpFixOption_,
                          buffer,
                          ByteSizes::uint8Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)(buffer), ByteSizes::uint8Size);
  
  ByteConversion::toBytes(inventoryHackOption_,
                          buffer,
                          ByteSizes::uint8Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)(buffer), ByteSizes::uint8Size);
  
  ByteConversion::toBytes(flightHackOption_,
                          buffer,
                          ByteSizes::uint8Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)(buffer), ByteSizes::uint8Size);
  
  if (versionNum_ >= 1) {
    ByteConversion::toBytes(noGameOverHackOption_,
                            buffer,
                            ByteSizes::uint8Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    data += std::string((char*)(buffer), ByteSizes::uint8Size);
  }
  
  if (versionNum_ >= 2) {
    ByteConversion::toBytes(saveHackOption_,
                            buffer,
                            ByteSizes::uint8Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    data += std::string((char*)(buffer), ByteSizes::uint8Size);
  }
  
  if (versionNum_ >= 3) {
    ByteConversion::toBytes(startOnLevelHackOption_,
                            buffer,
                            ByteSizes::uint8Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    data += std::string((char*)(buffer), ByteSizes::uint8Size);
    
    ByteConversion::toBytes(startOnLevelHackArea_,
                            buffer,
                            ByteSizes::uint8Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    data += std::string((char*)(buffer), ByteSizes::uint8Size);
    
    ByteConversion::toBytes(startOnLevelHackMap_,
                            buffer,
                            ByteSizes::uint8Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    data += std::string((char*)(buffer), ByteSizes::uint8Size);
    
    ByteConversion::toBytes(startOnLevelHackSpawn_,
                            buffer,
                            ByteSizes::uint8Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    data += std::string((char*)(buffer), ByteSizes::uint8Size);
  }
  
  if (versionNum_ >= 4) {
    ByteConversion::toBytes(startingItemHackOption_,
                            buffer,
                            ByteSizes::uint8Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    data += std::string((char*)(buffer), ByteSizes::uint8Size);
    
    ByteConversion::toBytes(startingItemHackID_,
                            buffer,
                            ByteSizes::uint8Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    data += std::string((char*)(buffer), ByteSizes::uint8Size);
    
    ByteConversion::toBytes(startingItemHackSFID_,
                            buffer,
                            ByteSizes::uint8Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    data += std::string((char*)(buffer), ByteSizes::uint8Size);
  }
  
  saver.finalize();
}

int HackSettings::load(const Tbyte* data) {
  int byteCount = 0;
  
  LoadHelper loader(data + byteCount,
                    byteCount);
  
  doubleJumpFixOption_ = static_cast<DoubleJumpFixOption>(
    ByteConversion::fromBytes(data + byteCount,
                              ByteSizes::uint8Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign)
  );
  byteCount += ByteSizes::uint8Size;
  
  maxHeightFixOption_ = static_cast<MaxHeightFixOption>(
    ByteConversion::fromBytes(data + byteCount,
                              ByteSizes::uint8Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign)
  );
  byteCount += ByteSizes::uint8Size;
  
  bombJumpFixOption_ = static_cast<BombJumpFixOption>(
    ByteConversion::fromBytes(data + byteCount,
                              ByteSizes::uint8Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign)
  );
  byteCount += ByteSizes::uint8Size;
  
  inventoryHackOption_ = static_cast<InventoryHackOption>(
    ByteConversion::fromBytes(data + byteCount,
                              ByteSizes::uint8Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign)
  );
  byteCount += ByteSizes::uint8Size;
  
  flightHackOption_ = static_cast<FlightHackOption>(
    ByteConversion::fromBytes(data + byteCount,
                              ByteSizes::uint8Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign)
  );
  byteCount += ByteSizes::uint8Size;
  
  if (loader.version() >= 1) {
    noGameOverHackOption_ = static_cast<NoGameOverHackOption>(
      ByteConversion::fromBytes(data + byteCount,
                                ByteSizes::uint8Size,
                                EndiannessTypes::little,
                                SignednessTypes::nosign)
    );
    byteCount += ByteSizes::uint8Size;
  }
  
  if (loader.version() >= 2) {
    saveHackOption_ = static_cast<SaveHackOption>(
      ByteConversion::fromBytes(data + byteCount,
                                ByteSizes::uint8Size,
                                EndiannessTypes::little,
                                SignednessTypes::nosign)
    );
    byteCount += ByteSizes::uint8Size;
  }
  
  if (loader.version() >= 3) {
    startOnLevelHackOption_ = static_cast<StartOnLevelHackOption>(
      ByteConversion::fromBytes(data + byteCount,
                                ByteSizes::uint8Size,
                                EndiannessTypes::little,
                                SignednessTypes::nosign)
    );
    byteCount += ByteSizes::uint8Size;
    
    startOnLevelHackArea_ = ByteConversion::fromBytes(data + byteCount,
                                ByteSizes::uint8Size,
                                EndiannessTypes::little,
                                SignednessTypes::nosign);
    byteCount += ByteSizes::uint8Size;
    
    startOnLevelHackMap_ = ByteConversion::fromBytes(data + byteCount,
                                ByteSizes::uint8Size,
                                EndiannessTypes::little,
                                SignednessTypes::nosign);
    byteCount += ByteSizes::uint8Size;
    
    startOnLevelHackSpawn_ = ByteConversion::fromBytes(data + byteCount,
                                ByteSizes::uint8Size,
                                EndiannessTypes::little,
                                SignednessTypes::nosign);
    byteCount += ByteSizes::uint8Size;
  }
  
  if (loader.version() >= 4) {
    startingItemHackOption_ = static_cast<StartingItemHackOption>(
      ByteConversion::fromBytes(data + byteCount,
                                ByteSizes::uint8Size,
                                EndiannessTypes::little,
                                SignednessTypes::nosign)
    );
    byteCount += ByteSizes::uint8Size;
    
    startingItemHackID_ = ByteConversion::fromBytes(data + byteCount,
                                ByteSizes::uint8Size,
                                EndiannessTypes::little,
                                SignednessTypes::nosign);
    byteCount += ByteSizes::uint8Size;
    
    startingItemHackSFID_ = ByteConversion::fromBytes(data + byteCount,
                                ByteSizes::uint8Size,
                                EndiannessTypes::little,
                                SignednessTypes::nosign);
    byteCount += ByteSizes::uint8Size;
  }
  
  return byteCount;
}
  
void HackSettings::exportToROM(WritableROM& rom) {
  switch (doubleJumpFixOption_) {
  case doubleJumpFixOn:
    TailsAdvBank0Hacks::addDoubleJumpFixHack(rom);
    break;
  default:
    break;
  }
  
  switch (maxHeightFixOption_) {
  case maxHeightFixOn:
    TailsAdvBank0Hacks::addButton1MaxHeightFixHack(rom);
    break;
  default:
    break;
  }
  
  switch (bombJumpFixOption_) {
  case bombJumpFixOn:
    TailsAdvBank0Hacks::addBombWhileJumpingGraphicFixHack(rom);
    break;
  default:
    break;
  }
  
  switch (inventoryHackOption_) {
  case inventoryHackOnBasic:
    TailsAdvBank0Hacks::addUseAllInventoryHack(rom);
    break;
  case inventoryHackOnFull:
    TailsAdvBank0Hacks::addFullInventoryHotswapHack(rom);
    break;
  case inventoryHackOnHotswapOnly:
    TailsAdvBank0Hacks::addRegularInventoryHotswapHack(rom);
    break;
  default:
    break;
  }
  
  switch (flightHackOption_) {
  case flightHackOnLimited:
    TailsAdvBank0Hacks::addFlightLimiterHack(rom);
    break;
  case flightHackOnDisabled:
    TailsAdvBank0Hacks::addFlightDisableHack(rom);
    break;
  default:
    break;
  }
  
  switch (noGameOverHackOption_) {
  case noGameOverHackOn:
    TailsAdvBank0Hacks::addNoGameOverHack(rom);
    break;
  default:
    break;
  }
  
  switch (saveHackOption_) {
  case manualSaveHackOn:
    TailsAdvBank0Hacks::addManualSaveHack(rom);
    break;
  case autoSaveHackOn:
    TailsAdvBank0Hacks::addAutoSaveHack(rom);
    break;
  default:
    break;
  }
  
  switch (startOnLevelHackOption_) {
  case startOnLevelHackOn:
    TailsAdvBank0Hacks::addStartOnLevelHack(rom,
                                            startOnLevelHackArea_,
                                            startOnLevelHackMap_,
                                            startOnLevelHackSpawn_);
    break;
  default:
    break;
  }
}
  
HackSettings::DoubleJumpFixOption HackSettings::doubleJumpFixOption() {
  return doubleJumpFixOption_;
}

void HackSettings::setDoubleJumpFixOption(
    DoubleJumpFixOption doubleJumpFixOption__) {
  doubleJumpFixOption_ = doubleJumpFixOption__;
}

HackSettings::MaxHeightFixOption HackSettings::maxHeightFixOption() {
  return maxHeightFixOption_;
}

void HackSettings::setMaxHeightFixOption(
    MaxHeightFixOption maxHeightFixOption__) {
  maxHeightFixOption_ = maxHeightFixOption__;
}

HackSettings::BombJumpFixOption HackSettings::bombJumpFixOption() {
  return bombJumpFixOption_;
}

void HackSettings::setBombJumpFixOption(
    BombJumpFixOption bombJumpFixOption__) {
  bombJumpFixOption_ = bombJumpFixOption__;
}

HackSettings::InventoryHackOption HackSettings::inventoryHackOption() {
  return inventoryHackOption_;
}

void HackSettings::setInventoryHackOption(
    InventoryHackOption inventoryHackOption__) {
  inventoryHackOption_ = inventoryHackOption__;
}

HackSettings::FlightHackOption HackSettings::flightHackOption() {
  return flightHackOption_;
}

void HackSettings::setFlightHackOption(
    FlightHackOption flightHackOption__) {
  flightHackOption_ = flightHackOption__;
}
  
HackSettings::NoGameOverHackOption HackSettings::noGameOverHackOption() {
  return noGameOverHackOption_;
}

void HackSettings::setNoGameOverHackOption(
    NoGameOverHackOption noGameOverHackOption__) {
  noGameOverHackOption_ = noGameOverHackOption__;
}
  
HackSettings::SaveHackOption HackSettings::saveHackOption() {
  return saveHackOption_;
}

void HackSettings::setSaveHackOption(
    SaveHackOption saveHackOption__) {
  saveHackOption_ = saveHackOption__;
}
  
HackSettings::StartOnLevelHackOption HackSettings::startOnLevelHackOption() {
  return startOnLevelHackOption_;
}

void HackSettings::setStartOnLevelHackOption(
    StartOnLevelHackOption startOnLevelHackOption__) {
  startOnLevelHackOption_ = startOnLevelHackOption__;
}
  
int HackSettings::startOnLevelHackArea() {
  return startOnLevelHackArea_;
}

void HackSettings::setStartOnLevelHackArea(int startOnLevelHackArea__) {
  startOnLevelHackArea_ = startOnLevelHackArea__;
}

int HackSettings::startOnLevelHackMap() {
  return startOnLevelHackMap_;
}

void HackSettings::setStartOnLevelHackMap(int startOnLevelHackMap__) {
  startOnLevelHackMap_ = startOnLevelHackMap__;
}

int HackSettings::startOnLevelHackSpawn() {
  return startOnLevelHackSpawn_;
}

void HackSettings::setStartOnLevelHackSpawn(int startOnLevelHackSpawn__) {
  startOnLevelHackSpawn_ = startOnLevelHackSpawn__;
}
  
HackSettings::StartingItemHackOption HackSettings::startingItemHackOption() {
  return startingItemHackOption_;
}

void HackSettings::setStartingItemHackOption(
    StartingItemHackOption startingItemHackOption__) {
  startingItemHackOption_ = startingItemHackOption__;
}

int HackSettings::startingItemHackID() {
  return startingItemHackID_;
}

void HackSettings::setStartingItemHackID(int startingItemHackID__) {
  startingItemHackID_ = startingItemHackID__;
}

int HackSettings::startingItemHackSFID() {
  return startingItemHackSFID_;
}

void HackSettings::setStartingItemHackSFID(int startingItemHackSFID__) {
  startingItemHackSFID_ = startingItemHackSFID__;
}


};
