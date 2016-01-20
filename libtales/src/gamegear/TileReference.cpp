#include "gamegear/TileReference.h"
#include <iostream>

namespace Tales {


TileReference::TileReference()
  : tileNum_(0),
    horizontalMirroringOption_(noHorizontalMirror),
    verticalMirroringOption_(noVerticalMirror),
    paletteOption_(palette0),
    priorityOption_(priorityBG) { };
    
TileReference::TileReference(unsigned int identifier)
  : tileNum_(0),
    horizontalMirroringOption_(noHorizontalMirror),
    verticalMirroringOption_(noVerticalMirror),
    paletteOption_(palette0),
    priorityOption_(priorityBG) {
    
  // Retrieve each field from the raw identifier
  
  tileNum_ = (identifier & tileNumMask) >> tileNumShift;
  
  if (identifier & horizontalMirroringMask) {
    horizontalMirroringOption_ = horizontalMirror;
  }
  
  if (identifier & verticalMirroringMask) {
    verticalMirroringOption_ = verticalMirror;
  }
  
  if (identifier & paletteMask) {
    paletteOption_ = palette1;
  }
  
  if (identifier & priorityMask) {
    priorityOption_ = priorityFG;
  }
}

TileReference::TileReference(unsigned int tileNum__,
              HorizontalMirroringOption horizontalMirroringOption__,
              VerticalMirroringOption verticalMirroringOption__,
              PaletteOption paletteOption__,
              PriorityOption priorityOption__)
  : tileNum_(tileNum__),
    horizontalMirroringOption_(horizontalMirroringOption__),
    verticalMirroringOption_(verticalMirroringOption__),
    paletteOption_(paletteOption__),
    priorityOption_(priorityOption__) { };

unsigned int TileReference::toRawIdentifier() const {
  // Value of the identifier
  unsigned int value = 0;
  
  // OR with tile number
  value |= (tileNum_ >> tileNumShift);
  
  // Set flags
  
  if (horizontalMirroringOption_ == horizontalMirror) {
    value |= horizontalMirroringMask;
  }
  
  if (verticalMirroringOption_ == verticalMirror) {
    value |= verticalMirroringMask;
  }
  
  if (paletteOption_ == palette1) {
    value |= paletteMask;
  }
  
  if (priorityOption_ == priorityFG) {
    value |= priorityMask;
  }
  
  return value;
}

unsigned int TileReference::tileNum() const {
  return tileNum_;
}

TileReference::HorizontalMirroringOption
    TileReference::horizontalMirroringOption() const {
  return horizontalMirroringOption_;
}

TileReference::VerticalMirroringOption
    TileReference::verticalMirroringOption() const {
  return verticalMirroringOption_;
}

TileReference::PaletteOption
    TileReference::paletteOption() const {
  return paletteOption_;
}

TileReference::PriorityOption
    TileReference::priorityOption() const {
  return priorityOption_;
}

void TileReference::setTileNum(unsigned int tileNum__) {
  tileNum_ = tileNum__;
}

void TileReference::setHorizontalMirroringOption(
      TileReference::HorizontalMirroringOption horizontalMirroringOption__) {
  horizontalMirroringOption_ = horizontalMirroringOption__;
}

void TileReference::setVerticalMirroringOption(
      TileReference::VerticalMirroringOption verticalMirroringOption__) {
  verticalMirroringOption_ = verticalMirroringOption__;
}

void TileReference::setPaletteOption(
      TileReference::PaletteOption paletteOption__) {
  paletteOption_ = paletteOption__;
}

void TileReference::setPriorityOption(
      TileReference::PriorityOption priorityOption__) {
  priorityOption_ = priorityOption__;
}
    
    
};
