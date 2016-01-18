#include "gamedata/EditableEmeraldHealthRefills.h"
#include "exception/OutOfRangeIndexException.h"
#include "exception/UnrecognizedVersionException.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"
#include "util/MiscMath.h"
#include <iostream>

using namespace Luncheon;

namespace Tales {


int EditableEmeraldHealthRefills::numEntries() {
  return numEntries_;
}

EditableEmeraldHealthRefills::EditableEmeraldHealthRefills() { };

EditableEmeraldHealthRefills::EditableEmeraldHealthRefills(
                                LoadedROM& rom,
                                Taddress emeraldHealthRefillTableAddress__)
  : emeraldHealthRefillTableAddress_(emeraldHealthRefillTableAddress__) {
  
  int byteCount = 0;
  
  for (int i = 0; i < numEntries_; i++) {
    // Get binary-coded decimal representation of health refill
    int maxHealthBCD = ByteConversion::fromBytes(
                            rom.directRead(emeraldHealthRefillTableAddress_
                                              + byteCount),
                            ByteSizes::uint8Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    byteCount += ByteSizes::uint8Size;
    
    // Convert to standard integer format
    int maxHealth = MiscMath::fromBCD(maxHealthBCD);
    
    // Store
    healthRefillPerEmerald_[i] = maxHealth;
  }
}

void EditableEmeraldHealthRefills::save(std::string& data) {
  Tbyte buffer[ByteSizes::uint32Size];
  
  SaveHelper saver(data,
                   DataChunkIDs::emeraldHealthRefills,
                   0);
  
  ByteConversion::toBytes(emeraldHealthRefillTableAddress_,
                          buffer,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint32Size);
    
  for (int i = 0; i < numEntries_; i++) {
    ByteConversion::toBytes(healthRefillPerEmerald_[i],
                            buffer,
                            ByteSizes::uint8Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    data += std::string((char*)buffer, ByteSizes::uint8Size);
  }
  
  saver.finalize();
}

int EditableEmeraldHealthRefills::load(const Tbyte* data) {
  int byteCount = 0;
  LoadHelper loader(data,
                    byteCount);
                    
  if (loader.version() > 0) {
    throw UnrecognizedVersionException(TALES_SRCANDLINE,
                                       "EditableEmeraldHealthRefills::load("
                                       "const Tbyte*)",
                                       DataChunkIDs::emeraldHealthRefills,
                                       "EditableEmeraldHealthRefills",
                                       loader.version(),
                                       0);
  }
  
  emeraldHealthRefillTableAddress_ = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint32Size;
    
  for (int i = 0; i < numEntries_; i++) {
    healthRefillPerEmerald_[i] = ByteConversion::fromBytes(
                            data + byteCount,
                            ByteSizes::uint8Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    byteCount += ByteSizes::uint8Size;
  }
  
  return byteCount;
}

void EditableEmeraldHealthRefills::exportToROM(WritableROM& rom) {
  int byteCount = 0;

  for (int i = 0; i < numEntries_; i++) {
    ByteConversion::toBytes(MiscMath::toBCD(healthRefillPerEmerald_[i]),
                            rom.directWrite(emeraldHealthRefillTableAddress_
                                              + byteCount),
                            ByteSizes::uint8Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    byteCount += ByteSizes::uint8Size;
  }
}

unsigned int& EditableEmeraldHealthRefills
    ::healthRefillPerEmerald(int powerups) {
  if (powerups >= numEntries_) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "EditableEmeraldHealthRefills"
                                   "::healthRefillPerEmerald(int)",
                                   powerups);
  }
  
  return healthRefillPerEmerald_[powerups];
}


};
