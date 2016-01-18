#ifndef LEVELOBJECTENTRY_H
#define LEVELOBJECTENTRY_H


#include "structs/Tbyte.h"
#include "structs/Taddress.h"
#include "gamedata/ObjectTypeID.h"
#include <string>

namespace Tales {


/**
 * An entry in a LevelObjectGroup.
 */
class LevelObjectEntry {
public:
  /**
   * Size in bytes of raw data representation.
   */
  const static int dataSize = 9;
  
  /**
   * Enum of x-direction flags (left/right facing).
   */
  enum XDirectionFlag {
    right,   /**< Object faces right. */
    left     /**< Object faces left. */
  };
  
  enum BlinkingFlag {
    notBlinking,   /**< Object blinks. */
    blinking       /**< Object does not blink. */
  };
  
  enum InvisibilityFlag {
    visible,   /**< Object is visible. */
    invisible  /**< Object is invisible. */
  };

  /**
   * Default constructor.
   */
  LevelObjectEntry();

  /**
   * Constructor from known values.
   */
  LevelObjectEntry(ObjectTypeIDs::ObjectTypeID objectTypeID__,
                   int xPos__,
                   int yPos__,
                   XDirectionFlag xDirectionFlag__,
                   BlinkingFlag blinkingFlag__,
                   InvisibilityFlag invisibilityFlag__,
                   Tbyte spawnParameter__,
                   int leftTileVRAMIndex__,
                   int rightTileVRAMIndex__);

  /**
   * Constructor from existing data.
   * @param data Byte array to read from.
   */
  LevelObjectEntry(const Tbyte* data);
  
  /**
   * Saves to a string.
   * @data String to save to.
   */
  void save(std::string& data);
  
  /**
   * Loads from a byte array.
   * @data Byte array to load from.
   * @return Number of bytes read.
   */
  int load(const Tbyte* data);
  
  /**
   * Writes to a byte array.
   * @data Byte array to save to.
   * @return Number of bytes written.
   */
  int writeToData(Tbyte* data);
  
  /**
   * Reads from a byte array.
   * @data Byte array to load from.
   * @return Number of bytes read.
   */
  int readFromData(const Tbyte* data);

  /**
   * Getter.
   */
  ObjectTypeIDs::ObjectTypeID objectTypeID() const;
  
  /**
   * Getter.
   */
  int xPos() const;
  
  /**
   * Getter.
   */
  int yPos() const;
  
  /**
   * Getter.
   */
  XDirectionFlag xDirectionFlag() const;
  
  /**
   * Getter.
   */
  BlinkingFlag blinkingFlag() const;
  
  /**
   * Getter.
   */
  InvisibilityFlag invisibilityFlag() const;
  
  /**
   * Getter.
   */
  Tbyte spawnParameter() const;
  
  /**
   * Getter.
   */
  int leftTileVRAMIndex() const;
  
  /**
   * Getter.
   */
  int rightTileVRAMIndex() const;
  
  /**
   * Setter.
   */
  void setObjectTypeID(ObjectTypeIDs::ObjectTypeID objectTypeID__);
  
  /**
   * Setter.
   */
  void setXPos(int xPos__);
  
  /**
   * Setter.
   */
  void setYPos(int yPos__);
  
  /**
   * Setter.
   */
  void setXDirectionFlag(XDirectionFlag xDirectionFlag__);
  
  /**
   * Setter.
   */
  void setBlinkingFlag(BlinkingFlag blinkingFlag__);
  
  /**
   * Setter.
   */
  void setInvisibilityFlag(InvisibilityFlag invisibilityFlag__);
  
  /**
   * Setter.
   */
  void setSpawnParameter(Tbyte spawnParameter__);
  
  /**
   * Setter.
   */
  void setLeftTileVRAMIndex(int leftTileVRAMIndex__);
  
  /**
   * Setter.
   */
  void setRightTileVRAMIndex(int rightTileVRAMIndex__);
  
protected:
  /**
   * Amount by which to adjust written x and y positions to get actual values.
   * For some reason, both coordinates are stored as 0x100 more than their
   * actual values.
   */
  const static int coordinateWriteAdjustment = 0x100;

  /**
   * Amount by which to adjust read x and y positions to get actual values.
   * For some reason, both coordinates are stored as 0x100 more than their
   * actual values.
   */
  const static int coordinateReadAdjustment = -coordinateWriteAdjustment;

  const static Tbyte unknownFlag0Mask = 0x01;
  const static Tbyte unknownFlag1Mask = 0x02;
  const static Tbyte unknownFlag2Mask = 0x04;
  const static Tbyte unknownFlag3Mask = 0x08;
  const static Tbyte unknownFlag6Mask = 0x40;
  
  /**
   * Mask to retrieve x direction flag from status byte.
   */
  const static Tbyte xDirectionMask = 0x10;
  
  /**
   * Mask to retrieve blinking flag from status byte.
   */
  const static Tbyte blinkingMask = 0x20;
  
  /**
   * Mask to retrieve invisibility flag from status byte.
   */
  const static Tbyte invisibilityMask = 0x80;
  
  /**
   * Sets the native bitflag representation from raw representation.
   * @param flags Byte containing raw bitflags.
   */
  void setFlags(Tbyte flags);
  
  /**
   * Converts the native bitflag representation to raw representation.
   * @return Raw representation of current native state.
   */
  Tbyte getRawFlags();

  /**
   * The object's internal type ID.
   */
  ObjectTypeIDs::ObjectTypeID objectTypeID_;
  
  /**
   * Object's starting x-position, in pixels.
   */
  int xPos_;
  
  /**
   * Object's starting y-position, in pixels.
   */
  int yPos_;
  
  // bit 0
  bool unknownFlag0_;
  
  // bit 1
  bool unknownFlag1_;
  
  // bit 2
  bool unknownFlag2_;
  
  // bit 3
  bool unknownFlag3_;
  
  // bit 4
  XDirectionFlag xDirectionFlag_;
  
  // bit 5
  BlinkingFlag blinkingFlag_;
  
  // bit 6
  bool unknownFlag6_;
  
  // bit 7
  InvisibilityFlag invisibilityFlag_;
  
  /**
   * The object's one-byte spawn parameter.
   * Usually this is the ID of the object's starting state, but its meaning
   * is object-dependent and is different for some types of objects
   * (e.g. warps).
   */
  Tbyte spawnParameter_;
  
  /**
   * Index, in tiles, of the object's leftward-facing graphics in VRAM.
   */
  int leftTileVRAMIndex_;
  
  /**
   * Index, in tiles, of the object's rightward-facing graphics in VRAM.
   */
  int rightTileVRAMIndex_;
};


};


#endif
