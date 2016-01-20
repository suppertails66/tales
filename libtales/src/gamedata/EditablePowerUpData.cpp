#include "gamedata/EditablePowerUpData.h"
#include "exception/OutOfRangeIndexException.h"
#include "exception/UnrecognizedVersionException.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"
#include "util/MiscMath.h"
#include <iostream>

using namespace Luncheon;

namespace Tales {


int EditablePowerUpData::numPowerUps() {
  return numPowerUps_;
}

unsigned int EditablePowerUpData::maxHealthTotal() {
  return maxHealthTotal_;
}

unsigned int EditablePowerUpData::maxFlightTimeTotal() {
  return maxFlightTimeTotal_;
}

EditablePowerUpData::EditablePowerUpData()
  : powerUpTableAddress_(0) { };

EditablePowerUpData::EditablePowerUpData(LoadedROM& rom,
                                         Taddress powerUpTableAddress__)
  : powerUpTableAddress_(powerUpTableAddress__) {
  int byteCount = 0;
  
  for (int i = 0; i < numPowerUps_; i++) {
    // Get binary-coded decimal representation of max health
    int maxHealthBCD = ByteConversion::fromBytes(
                            rom.directRead(powerUpTableAddress_ + byteCount),
                            ByteSizes::uint8Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    byteCount += ByteSizes::uint8Size;
    
    // Convert to standard integer format
    int maxHealth = MiscMath::fromBCD(maxHealthBCD);
    
    // Store
    maxHealthPerPowerup_[i] = maxHealth;
    
    // Get flight time
    int flightTime = ByteConversion::fromBytes(
                            rom.directRead(powerUpTableAddress_ + byteCount),
                            ByteSizes::uint16Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    byteCount += ByteSizes::uint16Size;
    
    // Store
    flightTimePerPowerup_[i] = flightTime;
  }
}

void EditablePowerUpData::save(std::string& data) {
  Tbyte buffer[ByteSizes::uint32Size];
  SaveHelper saver(data,
                   DataChunkIDs::powerUpData,
                   0);
  
  ByteConversion::toBytes(powerUpTableAddress_,
                          buffer,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint32Size);
    
  for (int i = 0; i < numPowerUps_; i++) {
    ByteConversion::toBytes(maxHealthPerPowerup_[i],
                            buffer,
                            ByteSizes::uint8Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    data += std::string((char*)buffer, ByteSizes::uint8Size);
    
    ByteConversion::toBytes(flightTimePerPowerup_[i],
                            buffer,
                            ByteSizes::uint16Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    data += std::string((char*)buffer, ByteSizes::uint16Size);
  }
  
  saver.finalize();
}

int EditablePowerUpData::load(const Tbyte* data) {
  int byteCount = 0;
  LoadHelper loader(data,
                    byteCount);
                    
  if (loader.version() > 0) {
    throw UnrecognizedVersionException(TALES_SRCANDLINE,
                                       "EditablePowerUpData::load("
                                       "const Tbyte*)",
                                       DataChunkIDs::powerUpData,
                                       "EditablePowerUpData",
                                       loader.version(),
                                       0);
  }
  
  powerUpTableAddress_ = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint32Size;
    
  for (int i = 0; i < numPowerUps_; i++) {
    maxHealthPerPowerup_[i] = ByteConversion::fromBytes(
                            data + byteCount,
                            ByteSizes::uint8Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    byteCount += ByteSizes::uint8Size;
    
    // Get flight time
    flightTimePerPowerup_[i] = ByteConversion::fromBytes(
                            data + byteCount,
                            ByteSizes::uint16Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    byteCount += ByteSizes::uint16Size;
  }
  
  return byteCount;
}

void EditablePowerUpData::exportToROM(WritableROM& rom) {
  int byteCount = 0;

  for (int i = 0; i < numPowerUps_; i++) {
    ByteConversion::toBytes(MiscMath::toBCD(maxHealthPerPowerup_[i]),
                            rom.directWrite(powerUpTableAddress_
                                              + byteCount),
                            ByteSizes::uint8Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    byteCount += ByteSizes::uint8Size;
    
    ByteConversion::toBytes(flightTimePerPowerup_[i],
                            rom.directWrite(powerUpTableAddress_
                                              + byteCount),
                            ByteSizes::uint16Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    byteCount += ByteSizes::uint16Size;
  }
}

unsigned int& EditablePowerUpData::maxHealthPerPowerup(int powerups) {
  if (powerups >= numPowerUps_) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "EditablePowerUpData"
                                   "::maxHealthPerPowerup(int)",
                                   powerups);
  }
  
  return maxHealthPerPowerup_[powerups];
}

unsigned int& EditablePowerUpData::flightTimePerPowerup(int powerups) {
  if (powerups >= numPowerUps_) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "EditablePowerUpData"
                                   "::maxHealthPerPowerup(int)",
                                   powerups);
  }
  
  return flightTimePerPowerup_[powerups];
}


};
