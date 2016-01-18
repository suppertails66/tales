#ifndef RAWOBJECTGRAPHICSUBHEADER_H
#define RAWOBJECTGRAPHICSUBHEADER_H


#include "structs/Tbyte.h"
#include "structs/Taddress.h"
#include "gamegear/LoadedROM.h"

namespace Tales {


/**
 * An object graphic header in a slightly modified "raw" format.
 * This can be read directly from ROM and stores addresses instead of
 * using indices like the non-raw version of the class. This is only
 * intended to be used temporarily, so that a regular ObjectGraphicHeader
 * can be constructed using indices once all the pointed-to data is loaded.
 * @see ObjectGraphicHeader
 */ 
class RawObjectGraphicSubheader {
public:
  /**
   * Size of raw data representation.
   * TODO: move to ObjectGraphicHeader
   */
  const static int dataSize = 5;

  /**
   * Default constructor.
   */
  RawObjectGraphicSubheader();
  
  /**
   * Constructor from ROM.
   * @param rom ROM to load from.
   * @param address Address in ROM to load from.
   */
  RawObjectGraphicSubheader(LoadedROM& rom,
                         Taddress address);
  
  /**
   * Getter.
   */
  Taddress vdpWriteAddress() const;
  
  /**
   * Getter.
   */
  Taddress objectGraphicAddress() const;
  
  /**
   * Getter.
   */
  bool substitutionEnabled() const;
  
protected:
  /**
   * Mask to retrieve substitution flag.
   */
  const static Tbyte substitutionMask = 0x80;
  
  /**
   * Mask to retrieve bank number.
   */
  const static Tbyte bankNumMask = 0x7F;

  /**
   * VDP write address.
   */
  Taddress vdpWriteAddress_;
  
  /**
   * Object graphic address.
   */
  Taddress objectGraphicAddress_;
  
  /**
   * Substitution flag.
   */
  bool substitutionEnabled_;
  
};


};


#endif
