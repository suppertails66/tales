#include "gamedata/EditableStandardPalettes.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"
#include "exception/OutOfRangeIndexException.h"
#include <iostream>

using namespace Luncheon;

namespace Tales {


EditableStandardPalettes::EditableStandardPalettes()
  : baseAddress_(0) { };

EditableStandardPalettes::EditableStandardPalettes(
                         LoadedROM& rom,
                         Taddress baseAddress__,
                         int numEntries)
  : baseAddress_(baseAddress__) {
  // Read palettes
  readPalettesFromData(rom.directRead(baseAddress__),
                       numEntries);
}

int EditableStandardPalettes::size() const {
  return primaryStorage_.size();
}

GGPalette& EditableStandardPalettes::palette(int index) {
  // Throw if index out of range
  if ((unsigned int)index >= primaryStorage_.size()) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "EditableStandardPalettes::palette(int)",
                                   index);
  }
  
  return primaryStorage_[index];
}

const GGPalette& EditableStandardPalettes::palette(int index) const {
  // Throw if index out of range
  if ((unsigned int)index >= primaryStorage_.size()) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "EditableStandardPalettes::palette(int)"
                                   " const",
                                   index);
  }
  
  return primaryStorage_[index];
}

void EditableStandardPalettes::save(std::string& data) {
  // Write buffer
  Tbyte buffer[ByteSizes::uint32Size];
  
  SaveHelper saver(data,
                   DataChunkIDs::standardPalettes,
                   0);
  
  // Write base address
  ByteConversion::toBytes(baseAddress_,
                          buffer,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint32Size);
  
  // Write number of palettes
  ByteConversion::toBytes(primaryStorage_.size(),
                          buffer,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint16Size);
  
  // Write each palette
  for (StandardPaletteCollection::size_type
        i = 0; i < primaryStorage_.size(); i++) {
    
    // Write each color in palette
    for (int j = 0; j < GGPalette::numColorsInPalette; j++) {
      ByteConversion::toBytes(primaryStorage_[i][j].nativeColor(),
                              buffer,
                              ByteSizes::uint16Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign);
      data += std::string((char*)buffer, ByteSizes::uint16Size);
    }
    
  }
  
  saver.finalize();
}

int EditableStandardPalettes::load(const Tbyte* data) {

  // Clear existing entries
  primaryStorage_.clear();

  // Count of loaded bytes
  int byteCount = 0;
  LoadHelper loader(data,
                    byteCount);
  
  // Get base address
  baseAddress_
    = ByteConversion::fromBytes(data + byteCount,
                                ByteSizes::uint32Size,
                                EndiannessTypes::little,
                                SignednessTypes::nosign);
  byteCount += ByteSizes::uint32Size;
  
  // Get number of palettes
  int numPalettes
    = ByteConversion::fromBytes(data + byteCount,
                                ByteSizes::uint16Size,
                                EndiannessTypes::little,
                                SignednessTypes::nosign);
  byteCount += ByteSizes::uint16Size;
  
  // Read palettes
  byteCount += readPalettesFromData(data + byteCount,
                                    numPalettes);
  
  return byteCount;
}

void EditableStandardPalettes::exportToROM(WritableROM& rom) {
  // Write each palette
  int address = baseAddress_;
  for (StandardPaletteCollection::size_type
        i = 0; i < primaryStorage_.size(); i++) {
    // Write each color
    for (int j = 0; j < GGPalette::numColorsInPalette; j++) {
      Tbyte buffer[ByteSizes::uint16Size];
      ByteConversion::toBytes(primaryStorage_[i][j].nativeColor(),
                              buffer,
                              ByteSizes::uint16Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign);
      
      // Copy to ROM
      rom.directWrite(address,
                      buffer,
                      ByteSizes::uint16Size);
      address += ByteSizes::uint16Size;
    }
  }
}

int EditableStandardPalettes::readPalettesFromData(
                         const Tbyte* data,
                         int numPalettes) {
  // Count of bytes read
  int byteCount = 0;
  
  // Read each palette
  for (StandardPaletteCollection::size_type
        i = 0; i < numPalettes; i++) {
    GGPalette palette;
    
    // Read each color
    for (int j = 0; j < GGPalette::numColorsInPalette; j++) {
      int nativeColor
        = ByteConversion::fromBytes(data + byteCount,
                                    ByteSizes::uint16Size,
                                    EndiannessTypes::little,
                                    SignednessTypes::nosign);
      byteCount += ByteSizes::uint16Size;
      
      GGColor color;
      color.setNativeColor(nativeColor);
      palette[j] = color;
    }
    
    // Add palette to storage
    primaryStorage_.push_back(palette);
  }
  
  return byteCount;
}


}; 
