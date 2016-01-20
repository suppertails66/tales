#ifndef RAWOBJECTGRAPHICSHEADER_H
#define RAWOBJECTGRAPHICSHEADER_H


#include "gamedata/RawObjectGraphicSubheader.h"
#include "structs/Tbyte.h"
#include "structs/Taddress.h"
#include "gamegear/LoadedROM.h"
#include <vector>

namespace Tales {


typedef std::vector<RawObjectGraphicSubheader>
    RawObjectGraphicSubheaderCollection;

/**
 * An object graphics header in a slightly modified "raw" format.
 * This can be read directly from ROM and stores addresses instead of
 * using indices like the non-raw version of the class. This is only
 * intended to be used temporarily, so that a regular ObjectGraphicsHeader
 * can be constructed using indices once all the pointed-to data is loaded.
 * @see ObjectGraphicsHeader
 */ 
class RawObjectGraphicsHeader {
public:
  /**
   * Default constructor.
   */
  RawObjectGraphicsHeader();
  
  /**
   * Constructor from ROM.
   * @param rom ROM to load from.
   * @param address Address in ROM to load from.
   */
  RawObjectGraphicsHeader(LoadedROM& rom,
                         Taddress address);
  
  /**
   * Returns number of subheaders.
   * @return Number of subheaders.
   */
  int size();
  
  /**
   * Subheader accessor.
   * @param index Index number of the subheader.
   * @return Reference to subheader of the given index.
   */
  RawObjectGraphicSubheader& subheader(int index);
  
  /**
   * Const subheader accessor.
   * @param index Index number of the subheader.
   * @return Const reference to subheader of the given index.
   */
  const RawObjectGraphicSubheader& subheader(int index) const;
protected:
  /**
   * End of header token.
   */
  const static Tbyte endOfHeaderToken = 0xFF;

  /**
   * Storage for raw graphics headers.
   */
  RawObjectGraphicSubheaderCollection rawObjectGraphicSubheaders_;
  
  
};


};


#endif
