#include "gamedata/MetatileLengthMap.h"
#include "exception/OutOfRangeIndexException.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"
#include "util/StringConversion.h"

using namespace Luncheon;

namespace Tales {


MetatileLengthMap::MetatileLengthMap() { };

MetatileLengthMap::MetatileLengthMap(const Tbyte* data) {
  // Read each value
  for (int i = 0; i < numElements; i++) {
    // Place in array
    lengths_[i] = LengthMapValue(data[i]);
  }
}

LengthMapValue& MetatileLengthMap::lengthAt(int index) {
  // Throw if index out of range
  if ((unsigned int)index >= numElements) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "MetatileLengthMap::lengthAt(int)",
                                   index);
  }

  return lengths_[index];
}

void MetatileLengthMap::setLengthAt(int index, LengthMapValue value) {
  // Throw if index out of range
  if ((unsigned int)index >= numElements) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "MetatileLengthMap::setLengthAt(int,"
                                   "LengthMapValue)",
                                   index);
  }
  
  lengths_[index] = value;
}

LengthMapValue& MetatileLengthMap::lengths(int index) {
  // Throw if index out of range
  if ((unsigned int)index >= numElements) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "MetatileLengthMap::lengthAt(int)",
                                   index);
  }

  return lengths_[index];
}

const LengthMapValue& MetatileLengthMap::lengths(int index) const {
  // Throw if index out of range
  if ((unsigned int)index >= numElements) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "MetatileLengthMap::lengthAt(int)",
                                   index);
  }

  return lengths_[index];
}

void MetatileLengthMap::save(std::string& data) {
  // Output buffer
  Tbyte buffer[ByteSizes::uint16Size];

  // Write each element to string
  for (int i = 0; i < numElements; i++) {
    ByteConversion::toBytes(
                      lengths_[i].toByte(),
                      buffer,
                      ByteSizes::uint8Size,
                      EndiannessTypes::little,
                      SignednessTypes::nosign);
    data += std::string((char*)buffer, ByteSizes::uint8Size);
  }
}

int MetatileLengthMap::load(const Tbyte* data) {
  // Read each element from string
  for (int i = 0; i < numElements; i++) {
    lengths_[i] = LengthMapValue(data[i]);
  }
  
  // Return number of bytes read
  return dataSize;
}

void MetatileLengthMap::writeToData(Tbyte* data) {
  // Copy each element
  for (int i = 0; i < numElements; i++) {
    data[i] = lengths_[i].toByte();
  }
}


};
