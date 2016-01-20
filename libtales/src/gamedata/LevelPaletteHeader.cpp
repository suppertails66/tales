#include "gamedata/LevelPaletteHeader.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"
#include <iostream>

using namespace Luncheon;

namespace Tales {


LevelPaletteHeader::LevelPaletteHeader()
  : palette0Index_(0),
    palette1Index_(0) { };

LevelPaletteHeader::LevelPaletteHeader(
                   int palette0Index__,
                   int palette1Index__)
  : palette0Index_(palette0Index__),
    palette1Index_(palette1Index__) { };

LevelPaletteHeader::LevelPaletteHeader(const Tbyte* data) {
  readFromData(data);
}

int LevelPaletteHeader::readFromData(const Tbyte* data) {
  // Get indices
  palette0Index_ = ByteConversion::fromBytes(
                          data,
                          ByteSizes::uint8Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
                          
  palette1Index_ = ByteConversion::fromBytes(
                          data + ByteSizes::uint8Size,
                          ByteSizes::uint8Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  
  return dataSize;
}

int LevelPaletteHeader::writeToData(Tbyte* data) {
  // Write indices
  ByteConversion::toBytes(palette0Index_,
                          data + 0,
                          ByteSizes::uint8Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
                          
  ByteConversion::toBytes(palette1Index_,
                          data + 1,
                          ByteSizes::uint8Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  
  return dataSize;
}

void LevelPaletteHeader::save(std::string& data) {
  // Output buffer
  Tbyte buffer[dataSize];
  
  // Get raw data
  writeToData(buffer);
  
  // Add to string
  data += std::string((char*)buffer, dataSize);
}

int LevelPaletteHeader::load(const Tbyte* data) {
  return readFromData(data);
}

void LevelPaletteHeader::exportToROM(
                 WritableROM& rom,
                 Taddress address) {
  // Output buffer
  Tbyte buffer[dataSize];
  
  // Get raw data
  writeToData(buffer);
  
  // Copy to ROM
  rom.directWrite(address,
                  buffer,
                  dataSize);
}

int LevelPaletteHeader::palette0Index() {
  return palette0Index_;
}

int LevelPaletteHeader::palette1Index() {
  return palette1Index_;
}

void LevelPaletteHeader::setPalette0Index(int palette0Index__) {
  palette0Index_ = palette0Index__;
}

void LevelPaletteHeader::setPalette1Index(int palette1Index__) {
  palette1Index_ = palette1Index__;
}


};
