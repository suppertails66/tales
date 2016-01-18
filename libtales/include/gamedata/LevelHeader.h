#ifndef LEVELHEADER_H
#define LEVELHEADER_H


#include "gamegear/LoadedROM.h"
#include "structs/Tbyte.h"
#include "structs/Taddress.h"
#include <string>

namespace Tales {


/**
 * A header containing basic level information.
 */
class LevelHeader {
public:
  
  /**
   * Size of raw header in bytes.
   */
  const static int dataSize = 22;
  
  /**
   * Height of nametable in metatiles.
   */
  const static int loadableAreaMultiplier = 14;

  /**
   * Default constructor.
   */
  LevelHeader();

  /**
   * Constructor from existing fields.
   * @param tileStructureID__ Tile structure ID.
   * @param mapLayoutID__ Map layout ID.
   * @param width__ Width in metatiles.
   * @param cameraLeftLimit__ Camera left limit.
   * @param cameraTopLimit__ Camera right limit.
   * @param cameraRightLimit__ Camera top limit.
   * @param cameraBottomLimit__ Camera bottom limit.
   * @param yTableID__ Y-table ID.
   */
  LevelHeader(int tileStructureID__,
              int mapLayoutID__,
              int width__,
              int cameraLeftLimit__,
              int cameraTopLimit__,
              int cameraRightLimit__,
              int cameraBottomLimit__,
              int yTableID__);
  
  int writeToData(Tbyte* data,
                  Taddress tileStructureAddress,
                  Taddress mapLayoutAddress,
                  Taddress yTableAddress) const;
              
  /**
   * Saves to a string.
   * @param data String to save to.
   */
  void save(std::string& data);
              
  /**
   * Loads from a byte array.
   * @param data Byte array to load from.
   * @return Number of bytes of data loaded.
   */
  int load(const Tbyte* data);

  /**
   * Getter.
   */
  int tileStructureID() const;
  
  /**
   * Getter.
   */
  int mapLayoutID() const;
  
  /**
   * Getter.
   */
  int width() const;
  
  /**
   * Getter.
   */
  int cameraLeftLimit() const;
  
  /**
   * Getter.
   */
  int cameraTopLimit() const;
  
  /**
   * Getter.
   */
  int cameraRightLimit() const;
  
  /**
   * Getter.
   */
  int cameraBottomLimit() const;
  
  /**
   * Getter.
   */
  int yTableID() const;
   
  /**
   * Setter.
   */
  void setTileStructureID(int tileStructureID__);
   
  /**
   * Setter.
   */
  void setMapLayoutID(int mapLayoutID__);
   
  /**
   * Setter.
   */
  void setWidth(int width__);
  
  /**
   * Setter.
   */
  void setCameraLeftLimit(int cameraLeftLimit__);
  
  /**
   * Setter.
   */
  void setCameraTopLimit(int cameraTopLimit__);
  
  /**
   * Setter.
   */
  void setCameraRightLimit(int cameraRightLimit__);
  
  /**
   * Setter.
   */
  void setCameraBottomLimit(int cameraBottomLimit__);
   
  /**
   * Setter.
   */
  void setYTableID(int yTableID__);
  
protected:
  
  /**
   * Associative index for EditableTileStructures.
   */
  int tileStructureID_;

  /**
   * Associative index for EditableMapLayouts.
   */
  int mapLayoutID_;

  /**
   * Width of the level in metatiles.
   */
  int width_;

  /**
   * Maximum leftward position of the camera (left side of screen).
   */
  int cameraLeftLimit_;
  
  /**
   * Maximum upward position of the camera (top side of screen).
   */
  int cameraTopLimit_;
  
  /**
   * Maximum rightward position of the camera (left side of screen).
   */
  int cameraRightLimit_;
  
  /**
   * Maximum downward position of the camera (top side of screen).
   */
  int cameraBottomLimit_;

  /**
   * Associative index for YTableAddresses.
   */
  int yTableID_;
  
};


};


#endif 
