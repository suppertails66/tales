#ifndef METATILEBEHAVIOR_H
#define METATILEBEHAVIOR_H


#include "structs/Tbyte.h"
#include "gamedata/MetatileBehavior.h"
#include "gamedata/MetatileType.h"
#include "gamedata/MetatileSolidity.h"

namespace Tales {


/**
 * An entry in the metatile behavior table.
 */
class MetatileBehavior {
public:
//  const static int heightMapLength = 0x10;
//  const static int widthMapLength = 0x10;

  /**
   * Size of raw data in bytes.
   */
  const static int dataSize = 7;

  /**
   * Default constructor.
   * Initializes all fields to zero.
   */
  MetatileBehavior();
  
  /**
   * Constructor from raw data.
   * @param src Pointer to a raw metatile behavior table entry.
   */
  MetatileBehavior(const Tbyte* src);
  
  /**
   * Read from raw data in game format.
   * @param src Pointer to a raw metatile behavior table entry.
   */
  void readFromData(const Tbyte* src);
  
  /**
   * Write raw data in game format.
   * @param src Array of data to write to. Must be at least 7 bytes long.
   */
  void writeToData(Tbyte* src);
  
  /**
   * Gets solidity.
   */
  MetatileSolidities::MetatileSolidity solidity() const;
  
  /**
   * Getter.
   */
  bool fullySolid() const;
  
  /**
   * Getter.
   */
  bool solidOnTop() const;
  
  /**
   * Getter.
   */
  bool unknownSetting() const;
  
  /**
   * Getter.
   */
  MetatileTypes::MetatileType metatileType() const;
  
  /**
   * Getter.
   */
  int slopeSpeedIndex() const;
  
  /**
   * Getter.
   */
  int heightMapIndex() const;
  
  /**
   * Getter.
   */
  int widthMapIndex() const;
  
  /**
   * Getter.
   */
  Tbyte terminator() const;
  
  /**
   * Sets solidity.
   * @param solidity The target solidity type.
   */
  void setSolidity(MetatileSolidities::MetatileSolidity solidity);
  
  /**
   * Setter.
   */
  void setMetatileType(MetatileTypes::MetatileType metatileType__);
  
  /**
   * Setter.
   */
  void setSlopeSpeedIndex(int slopeSpeedIndex__);
  
  /**
   * Setter.
   */
  void setHeightMapIndex(int heightMapIndex__);
  
  /**
   * Setter.
   */
  void setWidthMapIndex(int widthMapIndex__);
  
  /**
   * Setter.
   */
  void setTerminator(Tbyte terminator__);
  
protected:
  
  /**
   * Setter.
   */
  void setFullySolid(bool fullySolid__);
  
  /**
   * Setter.
   */
  void setSolidOnTop(bool solidOnTop__);
  
  /**
   * Setter.
   */
  void setUnknownSetting(bool unknownSetting__);

  /**
   * Calculate and return the type byte.
   * @return The game-formatted type byte.
   */
  Tbyte getTypeByte() const;
  
  /**
   * fullySolid_ bitmask.
   */
  const static Tbyte fullySolidMask = 0x80;
  
  /**
   * solidOnTop_ bitmask.
   */
  const static Tbyte solidOnTopMask = 0x40;
  
  /**
   * unknownSetting_ bitmask.
   */
  const static Tbyte unknownSettingMask = 0x20;
  
  /**
   * metatileType_ bitmask.
   */
  const static Tbyte metatileTypeMask = 0x1F;

  /**
   * If true, metatile is solid on all sides.
   * Corresponds to bit 7 of behavior byte.
   */
  bool fullySolid_;

  /**
   * If true, and fullySolid_ is false, metatile is solid only on top side.
   * Corresponds to bit 6 of behavior byte.
   */
  bool solidOnTop_;
  
  /**
   * Unused setting, not set on any used metatile.
   * Corresponds to bit 5 of behavior byte.
   */
  bool unknownSetting_;
  
  /**
   * The type of metatile this is (behavior).
   * Corresponds to bits 0-4 of behavior byte.
   */
  MetatileTypes::MetatileType metatileType_;
  
  /**
   * The slope speed adjustment table index.
   */
  int slopeSpeedIndex_;
  
  /**
   * The index number of this tile's height map.
   */
  int heightMapIndex_;
  
  /**
   * The index number of this tile's width map.
   */
  int widthMapIndex_;
  
  /**
   * Entry terminator -- always 0xFF.
   */
  Tbyte terminator_;
  
};


};


#endif 
