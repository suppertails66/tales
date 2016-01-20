#include "gamedata/SpriteMappingCoordinateTableEntry.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"

using namespace Luncheon;

namespace Tales {


SpriteMappingCoordinateTableEntry
    ::SpriteMappingCoordinateTableEntry()
  : offsetY_(0),
    offsetX_(0) { };

SpriteMappingCoordinateTableEntry
    ::SpriteMappingCoordinateTableEntry(const Tbyte* data)
  : offsetY_(0),
    offsetX_(0) {
  readFromData(data);
}
  
/**
 * Saves to a string.
 * @param data String to save to.
 */
void SpriteMappingCoordinateTableEntry::save(std::string& data) {
  Tbyte buffer[ByteSizes::uint16Size];
  
  ByteConversion::toBytes(offsetY_,
                          buffer,
                          ByteSizes::int16Size,
                          EndiannessTypes::little,
                          SignednessTypes::sign);
  data += std::string((char*)buffer, ByteSizes::int16Size);
  
  ByteConversion::toBytes(offsetX_,
                          buffer,
                          ByteSizes::int16Size,
                          EndiannessTypes::little,
                          SignednessTypes::sign);
  data += std::string((char*)buffer, ByteSizes::int16Size);
}

/**
 * Loads from raw data.
 * @param data Raw byte array to read from.
 * @return Number of bytes read.
 */
int SpriteMappingCoordinateTableEntry::load(const Tbyte* data) {
  return readFromData(data);
}

/**
 * Reads from raw data.
 * @param data Raw byte array to read from.
 * @return Number of bytes read.
 */
int SpriteMappingCoordinateTableEntry::readFromData(const Tbyte* data) {
  offsetY_ = ByteConversion::fromBytes(
                          data + 0,
                          ByteSizes::int16Size,
                          EndiannessTypes::little,
                          SignednessTypes::sign);
  
  offsetX_ = ByteConversion::fromBytes(
                          data + 2,
                          ByteSizes::int16Size,
                          EndiannessTypes::little,
                          SignednessTypes::sign);
  
  return dataSize;
}

/**
 * Writes to data.
 * @param data Raw byte array to write to.
 * @return Number of bytes written.
 */
int SpriteMappingCoordinateTableEntry::writeToData(Tbyte* data) {
  ByteConversion::toBytes(offsetY_,
                          data + 0,
                          ByteSizes::int16Size,
                          EndiannessTypes::little,
                          SignednessTypes::sign);
  
  ByteConversion::toBytes(offsetX_,
                          data + 2,
                          ByteSizes::int16Size,
                          EndiannessTypes::little,
                          SignednessTypes::sign);
  
  return dataSize;
}

int SpriteMappingCoordinateTableEntry::offsetY() const {
  return offsetY_;
}

int SpriteMappingCoordinateTableEntry::offsetX() const {
  return offsetX_;
}

void SpriteMappingCoordinateTableEntry::setOffsetY(int offsetY__) {
  offsetY_ = offsetY__;
}

void SpriteMappingCoordinateTableEntry::setOffsetX(int offsetX__) {
  offsetX_ = offsetX__;
}


};
