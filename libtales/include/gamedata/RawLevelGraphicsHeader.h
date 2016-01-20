#ifndef RAWLEVELGRAPHICSHEADER_H
#define RAWLEVELGRAPHICSHEADER_H


#include "structs/Tbyte.h"
#include "structs/Taddress.h"
#include "gamegear/LoadedROM.h"

namespace Tales {


/**
 * A level graphics header in a slightly modified "raw" format.
 * This can be read directly from ROM and stores addresses instead of
 * using indices like the non-raw version of the class. This is only
 * intended to be used temporarily, so that a regular LevelGraphicsHeader
 * can be constructed using indices once all the pointed-to data is loaded.
 * @see LevelGraphicsHeader
 */ 
class RawLevelGraphicsHeader {
public:
  /**
   * Size of raw data representation.
   * TODO: move to LevelGraphicsHeader
   */
  const static int dataSize = 7;

  /**
   * Default constructor.
   */
  RawLevelGraphicsHeader();
  
  /**
   * Constructor from ROM.
   * @param rom ROM to load from.
   * @param address Address in ROM to load from.
   */
  RawLevelGraphicsHeader(LoadedROM& rom,
                         Taddress address);
  
  /**
   * Getter.
   */
  Taddress vdpWriteAddress() const;
  
  /**
   * Getter.
   */
  Taddress mapGraphicAddress() const;
  
  /**
   * Getter.
   */
  Taddress objectGraphicsHeaderAddress() const;
  
protected:

  /**
   * VDP write address.
   */
  Taddress vdpWriteAddress_;
  
  /**
   * Map graphics address.
   */
  Taddress mapGraphicAddress_;
  
  /**
   * Object graphics header table address.
   */
  Taddress objectGraphicsHeaderAddress_;
  
};


};


#endif
