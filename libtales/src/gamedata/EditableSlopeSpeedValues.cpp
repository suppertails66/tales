#include "gamedata/EditableSlopeSpeedValues.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"
#include "exception/OutOfRangeIndexException.h"
#include "exception/UnrecognizedVersionException.h"
#include <iostream>

using namespace Luncheon;

namespace Tales {


EditableSlopeSpeedValues::EditableSlopeSpeedValues()
  : baseAddress_(0) { };

EditableSlopeSpeedValues::EditableSlopeSpeedValues(LoadedROM& rom,
                         Taddress baseAddress__,
                         int numEntries)
  : baseAddress_(baseAddress__) {
  for (int i = 0; i < numEntries; i++) {
    int value = ByteConversion::fromBytes(
                            rom.directRead(baseAddress__
                              + (i * ByteSizes::int16Size)),
                            ByteSizes::int16Size,
                            EndiannessTypes::little,
                            SignednessTypes::sign);
    speedValues_.push_back(value);
  }
}

int EditableSlopeSpeedValues::size() const {
  return speedValues_.size();
}

SlopeSpeedValue& EditableSlopeSpeedValues::speedValue(int index) {
  // Throw if index out of range
  if ((unsigned int)index >= speedValues_.size()) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "EditableSlopeSpeedValues::speedValue(int)",
                                   index);
  }
  
  return speedValues_[index];
}

const SlopeSpeedValue& EditableSlopeSpeedValues::speedValue(int index) const {
  // Throw if index out of range
  if ((unsigned int)index >= speedValues_.size()) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "EditableSlopeSpeedValues::speedValue(int)"
                                   " const",
                                   index);
  }
  
  return speedValues_[index];
}

void EditableSlopeSpeedValues::save(std::string& data) {
  // Output buffer
  Tbyte buffer[ByteSizes::uint32Size];
  SaveHelper saver(data,
                   DataChunkIDs::slopeSpeedValues,
                   0);

  // Write base address
  ByteConversion::toBytes(baseAddress_,
                          buffer,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint32Size);

  // Write number of entries
  ByteConversion::toBytes(speedValues_.size(),
                          buffer,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint16Size);
  
  // Write each entry
  for (SlopeSpeedValueCollection::iterator it = speedValues_.begin();
       it != speedValues_.end();
       it++) {
    ByteConversion::toBytes(*it,
                            buffer,
                            ByteSizes::int16Size,
                            EndiannessTypes::little,
                            SignednessTypes::sign);
    data += std::string((char*)buffer, ByteSizes::int16Size);
  }
  
  saver.finalize();
}

int EditableSlopeSpeedValues::load(const Tbyte* data) {
  // Clear existing entries
  speedValues_.clear();
  
  // Count of bytes read
  int byteCount = 0;
  LoadHelper loader(data,
                    byteCount);
                    
  if (loader.version() > 0) {
    throw UnrecognizedVersionException(TALES_SRCANDLINE,
                                       "EditableSlopeSpeedValues::load("
                                       "const Tbyte*)",
                                       DataChunkIDs::slopeSpeedValues,
                                       "EditableSlopeSpeedValues",
                                       loader.version(),
                                       0);
  }
  
  // Get base address
  baseAddress_
    = ByteConversion::fromBytes(data + byteCount,
                                ByteSizes::uint32Size,
                                EndiannessTypes::little,
                                SignednessTypes::nosign);
  byteCount += ByteSizes::uint32Size;
  
  // Get number of entries
  int numEntries
    = ByteConversion::fromBytes(data + byteCount,
                                ByteSizes::uint16Size,
                                EndiannessTypes::little,
                                SignednessTypes::nosign);
  byteCount += ByteSizes::uint16Size;
  
  // Read each entry
  for (int i = 0; i < numEntries; i++) {
    int value
      = ByteConversion::fromBytes(data + byteCount,
                                  ByteSizes::int16Size,
                                  EndiannessTypes::little,
                                  SignednessTypes::sign);
    byteCount += ByteSizes::int16Size;
    
    // TODO: negative saved values are 1 less than they should be
    // probably a bug in toBytes
    if (value < -1) {
//      value += 1;
    }
    
    speedValues_.push_back(value);
  }
  
  return byteCount;
}

void EditableSlopeSpeedValues::exportToROM(WritableROM& rom) {
  // Write each value to ROM
  int writeAddress = baseAddress_;
  for (SlopeSpeedValueCollection::iterator it = speedValues_.begin();
       it != speedValues_.end();
       it++) {
    Tbyte buffer[ByteSizes::int16Size];
    ByteConversion::toBytes(*it,
                            buffer,
                            ByteSizes::int16Size,
                            EndiannessTypes::little,
                            SignednessTypes::sign);
    rom.directWrite(writeAddress,
                    buffer,
                    ByteSizes::int16Size);
    writeAddress += ByteSizes::int16Size;
  }
}


};
