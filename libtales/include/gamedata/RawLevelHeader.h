#ifndef RAWLEVELHEADER_H
#define RAWLEVELHEADER_H


#include "structs/Tbyte.h"
#include "gamegear/LoadedROM.h"
#include "structs/Taddress.h"

namespace Tales {


/**
 * A raw level header.
 * This includes all level header data (including data pointers), and is
 * used as temporary storage for those values while initializing related
 * Editable classes.
 * @see EditableLevelHeader
 * @see EditableMetatileStructure
 * @see EditableMapLayout
 */
class RawLevelHeader {
public:
  
  /**
   * Size of raw header in bytes.
   */
  const static int dataSize = 22;

  /**
   * Default constructor.
   */
  RawLevelHeader();

  /**
   * Constructor from raw data.
   * @param rom ROM to load from.
   * @param address Address of the data to load.
   */
  RawLevelHeader(LoadedROM& rom,
                 Taddress address__);
  
  /**
   * Reads header from data.
   * @param rom ROM to read from.
   * @param address__ Address of data.
   */
  void readFromData(LoadedROM& rom,
                    Taddress address__);
  
  /**
   * Writes header to data.
   * @param data Tbyte array to hold header data. Must be at least (dataSize)
   * bytes long.
   */
//  int writeToData(Tbyte* data) const;

  /**
   * Returns the address of this header.
   * @return The address of this header.
   */
  Taddress address();

  /**
   * Getter.
   */
  Taddress metatileStructureAddress() const;
  
  /**
   * Getter.
   */
  Taddress mapLayoutAddress() const;
  
  /**
   * Getter.
   */
  int visualWidth() const;
  
  /**
   * Getter.
   */
  int negativeRowLength() const;
  
  /**
   * Getter.
   */
  int loadableMetatileArea() const;
  
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
  Taddress yTableAddress() const;
  
//  void setMetatileStructureAddress(Taddress metatileStructureAddress__);
  
//  void setMapLayoutAddress(Taddress mapLayoutAddress__);
  
protected:

  /**
   * Address of this header.
   */
  Taddress address_;
  
  /**
   * Address of metatile structure table.
   */
  Taddress metatileStructureAddress_;

  /**
   * Address of map layout data.
   */
  Taddress mapLayoutAddress_;

  /**
   * The visual width of the level, in metatiles.
   */
  int visualWidth_;

  /**
   * Offset to add to metatile index to find metatile one row above another.
   * This is used by the game to optimize vertical ejection and should always
   * equal (-visualWidth_).
   */
  int negativeRowLength_;

  /**
   * "Height" of the loadable area, in terms of metatiles and width.
   * This is a rather confusing field that indicates the number of bytes
   * needed to jump from the upper-left metatile of the loadable game area
   * (i.e. the nametable) to the position one beyond the lower-right.
   * This is an optimization used for loading graphics while
   * scrolling downward -- ultimately, the value is just
   * (levelWidthInMetatiles * nametableHeightInMetatiles).
   */
  int loadableMetatileArea_;

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
   * Address of the y-coordinate lookup table for this level.
   * The game optimizes tile collision checking using precomputed tables
   * of level array indices for each possible y-coordinate in each
   * possible level width. This field points to the table to be used for
   * this level. */
  Taddress yTableAddress_;
   
protected:
  /**
   * An invalid address used in the headers for the world map and Tails' House.
   */
  const static Taddress invalidTableAddress = 0x53630;
  
  /**
   * Replacement address for invalidTableAddress.
   * We need to move the table back in order to fit in the added
   * metatile definitions.
   */
  const static Taddress invalidTableRepairAddress = 0x53600;
};


};


#endif 
