#include "editors/HackSettings.h"
#include "structs/SaveHelper.h"
#include "structs/LoadHelper.h"
#include "gamedata/TailsAdvBank0Hacks.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"

using namespace Luncheon;

namespace Tales {


HackSettings::HackSettings()
  : doubleJumpFixOption_(doubleJumpFixOff),
    maxHeightFixOption_(maxHeightFixOff),
    bombJumpFixOption_(bombJumpFixOff),
    inventoryHackOption_(inventoryHackOff),
    flightHackOption_(flightHackOff) { };
  
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


};
