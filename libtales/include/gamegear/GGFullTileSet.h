#ifndef GGFULLTILESET_H
#define GGFULLTILESET_H


#include "gamegear/GGTile.h"
#include "gamegear/VirtualVDP.h"

namespace Tales {


/**
 * Container for and access on a set of Game Gear tiles.
 * This models VRAM at the pattern level; i.e. it contains
 * exactly 512 tiles and allows read/write access to each one.
 */
class GGFullTileSet {
public:
  /**
   * The number of tiles contained in the set.
   * Following the specifications of the Game Gear VDP, this is a constant 512.
   */
  const static unsigned int numTilesInSet = 512;

  /**
   * Default constructor.
   * Initializes all tile pixel data to default (every color index zero).
   */
  GGFullTileSet();
  
  /**
   * Copy constructor.
   * @param ggTileSet GGFullTileSet from which to copy data.
   */
  GGFullTileSet(const GGFullTileSet& ggTileSet);
  
  /**
   * Copy assignment.
   * @param ggTileSet GGFullTileSet from which to copy data.
   */
  GGFullTileSet& operator=(const GGFullTileSet& ggTileSet);
  
  /**
   * Constructor from VRAM.
   * Deinterleaves and reformats VRAM into GGTiles and stores them for access.
   * @param vdp VirtualVDP from which to create GGTiles.
   */
  GGFullTileSet(const VirtualVDP& vdp);
  
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
protected:

  /**
   * Size of the temporary buffer used to deinterleave data.
   */
  const static int deinterleaveBufferSize = 4;
  
  /**
   * Tile data array.
   */
  GGTile tileSet_[numTilesInSet];
  
};


};


#endif 
