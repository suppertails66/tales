#ifndef GGTILESET_H
#define GGTILESET_H


#include "gamegear/GGTile.h"
#include "gamegear/VirtualVDP.h"
#include "structs/Tbyte.h"
#include "structs/Graphic.h"
#include <string>

namespace Tales {


class GGTileSet {
public:
  /**
   * Default constructor.
   */
  GGTileSet();
  
  /**
   * Destructor.
   */
  virtual ~GGTileSet();
  
  /**
   * Copy constructor.
   * @param ggTileSet GGTileSet from which to copy data.
   */
  GGTileSet(const GGTileSet& ggTileSet);
  
  /**
   * Copy assignment.
   * @param ggTileSet GGTileSet from which to copy data.
   */
  GGTileSet& operator=(const GGTileSet& ggTileSet);
  
  /**
   * Constructor.
   * @param numTiles__ Number of tiles in the set.
   */
  GGTileSet(int numTiles__);
  
  /**
   * Constructor from existing graphics.
   * @param vdp VirtualVDP containing graphics.
   * @param startingTileNum Index of the first tile to load.
   * @param numTiles__ Number of tiles to load.
   */
  GGTileSet(VirtualVDP& vdp,
            int startingTileNum,
            int numTiles__);
  
  /**
   * Returns number of tiles in the set.
   * @return Number of tiles in the set.
   */
  int numTiles() const;
  
  /**
   * Resize to a new number of tiles.
   * Truncates tiles at end if new size is smaller, and appends default-
   * inialized tiles if new size is larger.
   * @param newSize New number of tiles in set.
   */
  void resize(int newSize);
  
  /**
   * Subscript operator access.
   * @param tileNum Index of the tile to retrieve.
   */
  GGTile& operator[](unsigned int tileNum);
  
  /**
   * Const subscript operator access.
   * @param tileNum Index of the tile to retrieve.
   */
  const GGTile& operator[](unsigned int tileNum) const;
  
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
  
  /**
   * Writes to native uncompressed format (4 bits per pixel, interleaved).
   * @param Tbyte* data Raw byte array to write to.
   * @return Number of bytes written.
   */
  int writeNativeUncompressed(Tbyte* data);
  
  /**
   * Returns tiles as a grayscale Graphic.
   * Mostly meant for testing.
   * @param width Width of the output image. Tiles will be wrapped at edges
   * to accomodate dimensions.
   * @param invert If true, output will be reversed (0 = FF, etc.).
   */
  Graphic toGrayscaleGraphic(int width,
                             Color backgroundColor
                               = Color(255, 255, 255, 255),
                             bool invert = false);
                             
  Graphic toPalettizedGraphic(int width,
                              const GGPalette& palette,
                              Color backgroundColor
                               = Color(255, 255, 255, 255),
                              Graphic::TileTransferTransOption transOption
                               = Graphic::tileTrans);
                               
  void drawPalettizedGraphic(Graphic& output,
                              int width,
                              const GGPalette& palette,
                              Color backgroundColor
                               = Color(255, 255, 255, 255),
                              Graphic::TileTransferTransOption transOption
                               = Graphic::tileTrans);
protected:
  /**
   * Tile data pointer.
   */
  GGTile* tileSet_;
  
  /**
   * Number of tiles in set.
   */
  int numTiles_;
  
};


};


#endif
