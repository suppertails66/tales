#ifndef GGPALETTE_H
#define GGPALETTE_H


#include "structs/Tbyte.h"
#include "gamegear/GGColor.h"

namespace Tales {


/**
 * A set of GGColors representing a 16-color Game Gear palette.
 */
class GGPalette {
public:
  /**
   * The number of colors in a palette.
   */
  const static unsigned int numColorsInPalette = 16;
  
  /**
   * The palette index treated as transparent under certain conditions.
   */
  const static unsigned int transColorIndex = 0;

  /**
   * Constructor.
   * Initializes all palette entries to default GGColor value (pure black).
   */
  GGPalette();
  
  /**
   * Copy constructor.
   * @param palette GGPalette from which to copy data.
   */
  GGPalette(const GGPalette& palette);
  
  /**
   * Copy assignment.
   * @param palette GGPalette from which to copy data.
   */
  GGPalette& operator=(const GGPalette& palette);
  
  /**
   * Subscript operator.
   * Returns a reference to the color at the given index.
   * @param index The index of the color to retrieve.
   * @throws ColorOutOfRangeException
   */
  GGColor& operator[](unsigned int index);
  
  /**
   * Const subscript operator.
   * Returns a reference to the color at the given index.
   * @param index The index of the color to retrieve.
   * @throws ColorOutOfRangeException
   */
  const GGColor& operator[](unsigned int index) const;
  
  /**
   * Returns the transparency color index.
   * @return The transparency color index.
   */
  unsigned int getTransColorIndex() const;
protected:
  
  /**
   * Array containing the palette entries.
   */
  GGColor colors_[numColorsInPalette];
  
};


};


#endif 
