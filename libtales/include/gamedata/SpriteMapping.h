#ifndef SPRITEMAPPING_H
#define SPRITEMAPPING_H


#include "structs/Tbyte.h"
#include "structs/Taddress.h"
#include "structs/Tmap.h"
#include "gamegear/LoadedROM.h"

namespace Tales {


class SpriteMapping {
public:
  /**
   * Size in bytes of raw data representation.
   */
  const static int dataSize = 11;

  /**
   * Default constructor.
   */
  SpriteMapping();
  
  /**
   * Initializer from existing data.
   * @param numSprites__ Number of component sprites.
   * @param collisionXLength__ Extent of collision box in x-axis.
   * @param collisionYLength__ Extent of collision box in y-axis.
   * @param coordinateTableIndex__ Index number of coordinate lookup table.
   * @param offsetX__ Offset in x of sprites from nominal object position.
   * @param offsetY__ Offset in y of sprites from nominal object position.
   * @param tileIndexTableIndex__ Index number of tile index lookup table.
   */
  SpriteMapping(int numSprites__,
                int collisionXLength__,
                int collisionYLength__,
                int coordinateTableIndex__,
                int offsetY__,
                int offsetX__,
                int tileIndexTableIndex__);
  
  /**
   * Saves to a string.
   * @param data String to save to.
   */
  void save(std::string& data);
  
  /**
   * Loads from raw data.
   * @param data Raw byte array to read from.
   * @return Number of bytes read.
   */
  int load(const Tbyte* data);
  
  /**
   * Writes to data.
   * @param data Raw byte array to write to.
   * @param coordinateTableAddress Direct address of the coordinate table.
   * @param tileIndexTableAddress Direct address of the tile index table.
   * @return Number of bytes written.
   */
  int writeToData(Tbyte* data,
                  Taddress coordinateTableAddress,
                  Taddress tileIndexTableAddress);
  
  /**
   * Getter.
   */
  int numSprites() const;
  
  /**
   * Getter.
   */
  int collisionXLength() const;
  
  /**
   * Getter.
   */
  int collisionYLength() const;
  
  /**
   * Getter.
   */
  int coordinateTableIndex() const;
  
  /**
   * Getter.
   */
  int offsetY() const;
  
  /**
   * Getter.
   */
  int offsetX() const;
  
  /**
   * Getter.
   */
  int tileIndexTableIndex() const;
  
  /**
   * Setter.
   */
  void setNumSprites(int numSprites__);
  
  /**
   * Setter.
   */
  void setCollisionXLength(int collisionXLength__);
  
  /**
   * Setter.
   */
  void setCollisionYLength(int collisionYLength__);
  
  /**
   * Setter.
   */
  void setCoordinateTableIndex(int coordinateTableIndex__);
  
  /**
   * Setter.
   */
  void setOffsetY(int offsetY__);
  
  /**
   * Setter.
   */
  void setOffsetX(int offsetX__);
  
  /**
   * Setter.
   */
  void setTileIndexTableIndex(int tileIndexTableIndex__);
  
protected:
  
  int numSprites_;
  
  int collisionXLength_;
  
  int collisionYLength_;
  
  int coordinateTableIndex_;
  
  int offsetY_;
  
  int offsetX_;
  
  int tileIndexTableIndex_;
  
};


};


#endif
