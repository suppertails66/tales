#include "gamedata/PaletteCycleState.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"
#include <iostream>

using namespace Luncheon;

namespace Tales {


PaletteCycleState::PaletteCycleState() { };

void PaletteCycleState::save(std::string& data) {
  Tbyte buffer[ByteSizes::uint32Size];
  
  ByteConversion::toBytes(colors_.size(),
                          buffer,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint16Size);

  for (IndexToColorMap::iterator it = colors_.begin();
       it != colors_.end();
       it++) {
    ByteConversion::toBytes(it->first,
                            buffer,
                            ByteSizes::uint16Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    data += std::string((char*)buffer, ByteSizes::uint16Size);
    
    ByteConversion::toBytes(it->second.nativeColor(),
                            buffer,
                            ByteSizes::uint16Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    data += std::string((char*)buffer, ByteSizes::uint16Size);
  }
}
  
int PaletteCycleState::load(const Tbyte* data) {
  colors_.clear();
  int byteCount = 0;

  int numColors = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint16Size;
  
  for (int i = 0; i < numColors; i++) {
    int index = ByteConversion::fromBytes(
                            data + byteCount,
                            ByteSizes::uint16Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    byteCount += ByteSizes::uint16Size;
    
//    std::cout << index << std::endl;
    
    int nativeColor = ByteConversion::fromBytes(
                            data + byteCount,
                            ByteSizes::uint16Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    byteCount += ByteSizes::uint16Size;
    
    GGColor color;
    color.setNativeColor(nativeColor);
    
    colors_.insert(
      IndexToColorMap::PairType(
        index,
        color));
  }
//  std::cout << "\n\n" << std::endl;
  
  return byteCount;
}

int PaletteCycleState::standardWriteToData(Tbyte* data) {
  int byteCount = 0;

  for (IndexToColorMap::iterator it = colors_.begin();
       it != colors_.end();
       it++) {
    ByteConversion::toBytes(it->second.nativeColor(),
                            data + byteCount,
                            ByteSizes::uint16Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    byteCount += ByteSizes::uint16Size;
  }
  
  return byteCount;
}

int PaletteCycleState::standardReadFromData(
                         const Tbyte* data,
                         int startingColor,
                         int numColors) {
  colors_.clear();
  int byteCount = 0;
  
  int currentIndex = startingColor;
  for (int i = 0; i < numColors; i++) {
    int nativeColor = ByteConversion::fromBytes(
                            data + byteCount,
                            ByteSizes::uint16Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    byteCount += ByteSizes::uint16Size;
    
    GGColor color;
    color.setNativeColor(nativeColor);
    
    colors_.insert(
      IndexToColorMap::PairType(
        currentIndex,
        color));
    
    ++currentIndex;
  }
  
  return byteCount;
}
  
bool PaletteCycleState::hasColor(int index) {
  try {
    colors_.findOrThrow(index);
  }
  catch (TmapKeyNotFoundException& e) {
    return false;
  }
  
  return true;
}

GGColor PaletteCycleState::color(int index) {
  return colors_.findValueOrThrow(index);
}

void PaletteCycleState::modifyColor(
              int index,
              const GGColor& color) {
  colors_.findValueOrThrow(index) = color;
}
                
void PaletteCycleState::insertColor(
                 int index,
                 const GGColor& color) {
  colors_.insert(
    IndexToColorMap::PairType(index,
                              color));
}
                   
IndexToColorMap::const_iterator PaletteCycleState::cbegin() const {
  return colors_.cbegin();
}
                 
IndexToColorMap::const_iterator PaletteCycleState::cend() const {
  return colors_.cend();
}


};
