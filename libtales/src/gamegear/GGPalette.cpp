#include "gamegear/GGPalette.h"
#include "exception/ColorOutOfRangeException.h"

namespace Tales {


GGPalette::GGPalette() { };

GGPalette::GGPalette(const GGPalette& palette) {
  // Copy color data
  for (int i = 0; i < numColorsInPalette; i++) {
    colors_[i] = palette.colors_[i];
  }
}

GGPalette& GGPalette::operator=(const GGPalette& palette) {
  // Copy color data
  for (int i = 0; i < numColorsInPalette; i++) {
    colors_[i] = palette.colors_[i];
  }
  
  return *this;
}

GGColor& GGPalette::operator[](unsigned int index) {
  // Throw if index out of range
  if (index >= numColorsInPalette) {
    throw ColorOutOfRangeException(TALES_SRCANDLINE,
                                   "GGPalette::operator[](unsigned int)",
                                   index);
  }
  
  // Return the requested color
  return colors_[index];
}

const GGColor& GGPalette::operator[](unsigned int index) const {
  // Throw if index out of range
  if (index >= numColorsInPalette) {
    throw ColorOutOfRangeException(TALES_SRCANDLINE,
                                   "GGPalette::operator[](unsigned int) const",
                                   index);
  }
  
  // Return the requested color
  return colors_[index];
}

unsigned int GGPalette::getTransColorIndex() const {
  return transColorIndex;
}


};
