#ifndef TILEMAP_H
#define TILEMAP_H


#include "structs/Tbyte.h"
#include "gamegear/TileReference.h"
#include <string>

namespace Tales {


/**
 * A rectangular area composed of tile identifiers.
 */
class TileMap {
public:
  /**
   * Enum of tilemap types.
   * 2-byte-per-tile format is a standard "full" tilemap with 16-bit
   * identifiers.
   * 1-byte-per-tile format specifies only the low byte of each identifier,
   * with some particular high byte for all values specified in the code.
   * The main difference is that 1-byte-per-tile format restricts tiles
   * to a specific range (0-255 or 256-511) and prevents them from being
   * mirrored, having palette flags set, etc.
   */
  enum TileMapFormat {
	oneBytePerTile,
	twoBytesPerTile
  };

  /**
   * Default constructor.
   */
  TileMap();
  
  /**
   * Constructor from raw data.
   * @param data Raw data source.
   * @param format__ Format of the source data.
   * @param w__ Width in tiles of the source data.
   * @param h__ Height in tiles of the source data.
   */
  TileMap(const Tbyte* data,
          TileMapFormat format__,
          int w__,
		  int h__);
  
  /**
   * Constructor from raw 1bpt data.
   * @param data Raw data source.
   * @param format__ Format of the source data.
   * @param w__ Width in tiles of the source data.
   * @param h__ Height in tiles of the source data.
   * @param upperByte__ Upper byte of each tile entry.
   */
  TileMap(const Tbyte* data,
          TileMapFormat format__,
          int w__,
		  int h__,
		  Tbyte upperByte__);
  
  /**
   * Destructor.
   */
  ~TileMap();
  
  /**
   * Reads a tilemap from raw data.
   * @param data Raw data source.
   * @param format__ Format of the source data.
   * @param w__ Width in tiles of the source data.
   * @param h__ Height in tiles of the source data.
   */
  int readFromData(const Tbyte* data,
                   TileMapFormat format__,
				   int w__,
				   int h__);
  
  /**
   * Reads a 1bpt tilemap from raw data.
   * @param data Raw data source.
   * @param format__ Format of the source data.
   * @param w__ Width in tiles of the source data.
   * @param h__ Height in tiles of the source data.
   */
  int readFromData(const Tbyte* data,
                   TileMapFormat format__,
				   int w__,
				   int h__,
				   Tbyte upperByte__);
  
  /**
   * Writes the tilemap to raw data.
   * @param data Raw data destination.
   */
  void writeToData(Tbyte* data) const;
  
  /**
   * Saves to a string.
   * @param data String to save to.
   */
  void save(std::string& data) const;
  
  /**
   * Loads from a byte array.
   * @param data Byte array to load from.
   */
  int load(const Tbyte* data);
  
  /**
   * Getter.
   */
  TileMapFormat format() const;
  
  /**
   * Getter.
   */
  int w() const;
  
  /**
   * Getter.
   */
  int h() const;
  
  /**
   * Getter.
   */
  int lowerLimit() const;
  
  /**
   * Getter.
   */
  int upperLimit() const;
  
  /**
   * Setter.
   */
  void setFormat(TileMapFormat format__);
  
  /**
   * Setter.
   */
  void setW(int w__);
  
  /**
   * Setter.
   */
  void setH(int h__);
  
  /**
   * Setter.
   */
  void setLowerLimit(int lowerLimit__);
  
  /**
   * Setter.
   */
  void setUpperLimit(int upperLimit__);
protected:
  /**
   * Default lower limit of tilemap range (0 = all tiles).
   */
  const static int defaultLowerLimit_ = 0;
  
  /**
   * Default upper limit of tilemap range (512 = all tiles).
   */
  const static int defaultUpperLimit_ = 512;
  
  /**
   * Deallocate the tile array.
   */
  void destroyTileData();
  
  /**
   * Initialize the tile array to the specified size.
   */
  void reinitializeTileData(int w__, int h__);
  
  /**
   * Array of tile data.
   */
  TileReference** tileData_;
  
  /**
   * Format of the source data.
   */
  TileMapFormat format_;
  
  /**
   * Width in tiles of the tilemap.
   */
  int w_;
  
  /**
   * Height in tiles of the tilemap.
   */
  int h_;
  
  /**
   * Lower limit of the tiles that can be specified in the tilemap.
   */
  int lowerLimit_;
  
  /**
   * Upper limit of the tiles that can be specified in the tilemap.
   */
  int upperLimit_;
};


};


#endif