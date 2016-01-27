#ifndef GGTILE_H
#define GGTILE_H


#include "structs/Tbyte.h"
#include "structs/TwoDByteArray.h"
#include <string>

namespace Tales {

/**
 * Representation of a Game Gear VDP tile.
 * Uses raw unpalettized, deinterleaved, 1 byte per pixel format.
 */
class GGTile {
public:
  /**
   * Width of a tile in pixels.
   */
   const static int width = 8;
   
  /**
   * Height of a tile in pixels.
   */
   const static int height = 8;
   
  /**
   * Bytes per pixel in the data array.
   */
   const static int bytesPerPixel = 1;
   
  /**
   * Size of the pixel data array in bytes.
   */
   const static int dataSize = width * height * bytesPerPixel;
   
  /**
   * Bits per pixel in the data array.
   */
   const static int bitsPerPixel = 4;
   
  /**
   * Bytes per row in the data array.
   */
   const static int bytesPerRow = bytesPerPixel * width;
  
  /**
   * Size in bytes of raw data input.
   */
  const static int rawInputDataSize = dataSize/2;
   
  /**
   * Default constructor.
   * Initializes all pixels to zero.
   */
  GGTile();
   
  /**
   * Constructor from raw VRAM data for one tile.
   * @param vramData Raw VRAM data (4 bits per pixel format, interleaved).
   */
  GGTile(const Tbyte* vramData);
   
  /**
   * Copy constructor.
   */
  GGTile(const GGTile& tile);
   
  /**
   * Copy assignment.
   */
  GGTile& operator=(const GGTile& tile);
   
  /**
   * Fills pixel data from raw array of interleaved VRAM pixel data.
   * @param deinterleavedPixelData 4-bits-per-pixel array of pixel values.
   * Must have length greater than or equal to (dataSize / 2).
   */
  void assignFromInterleavedPixels(const Tbyte* interleavedPixelData);
   
  /**
   * Fills pixel data from raw array of deinterleaved VRAM pixel data.
   * @param deinterleavedPixelData 4-bits-per-pixel array of pixel values.
   * Must have length greater than or equal to (dataSize / 2).
   */
  void assignFromDeinterleavedPixels(const Tbyte* deinterleavedPixelData);
  
  void toInterleavedPixels(Tbyte* dst) const;
  
  /**
   * Retrieves the tile width.
   * Function-based alias to static width member, for consistency.
   * @return The tile's width.
   */
  static int w();
  
  /**
   * Retrieves the tile height.
   * Function-based alias to static height member, for consistency.
   * @return The tile's height.
   */
  static int h();
  
  /**
   * Retrieves the tile pixel array size, in bytes.
   * Function-based alias to static dataSize member, for consistency.
   * @return The tile pixel array size, in bytes.
   */
  static int size();
  
  /**
   * Returns non-const pointer to pixel data array.
   * @return Non-const pointer to pixel data array.
   */
  Tbyte* imgdat();
  
  /**
   * Returns const pointer to pixel data array.
   * @return Const pointer to pixel data array.
   */
  const Tbyte* const_imgdat() const;
  
  /**
   * Retrieves the color index number of the given pixel.
   * @param xpos The x-position of the pixel to look up.
   * @param ypos The y-position of the pixel to look up.
   * @return The integral color index number of the given pixel.
   */
  Tbyte getPixel(int xpos, int ypos) const;
  
  /**
   * Sets the color index number of the given pixel.
   * @param xpos The x-position of the pixel to modify.
   * @param ypos The y-position of the pixel to modify.
   * @param value The new value for the pixel's color index.
   */
  void setPixel(int xpos,
                int ypos,
                Tbyte value);
  
  /**
   * Flips the tile horizontally.
   */
  void flipHorizontal();
  
  /**
   * Flips the tile vertically.
   */
  void flipVertical();
  
  /**
   * Saves to a string.
   * @param data String to save to.
   */
  void save(std::string& data);
  
  /**
   * Loads from a byte array.
   * @param data Byte array to load from.
   * @return Number of bytes read.
   */
  int load(const Tbyte* data);
  
  void transferToByteArray(TwoDByteArray& dst,
                           int x, int y);
  
protected:
  
  /**
   * Size in bytes of the deinterleave buffer.
   */
  const static int deinterleaveBufferSize = 4;

  /**
   * Pixel data array.
   * Each byte represents one pixel. Ordering is left-to-right, top-to-bottom.
   */
  Tbyte imgdat_[dataSize];
  
};


};


#endif
