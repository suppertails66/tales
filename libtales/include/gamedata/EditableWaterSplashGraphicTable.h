#ifndef EDITABLEWATERSPLASHGRAPHICTABLE_H
#define EDITABLEWATERSPLASHGRAPHICTABLE_H


#include "gamedata/BaseEditableFixedGraphicTable.h"

namespace Tales {


class EditableWaterSplashGraphicTable
  : public BaseEditableFixedGraphicTable {
public:
  const static int numGraphicTiles = 14;
  
  /**
   * Default constructor.
   */
  EditableWaterSplashGraphicTable();
  
  /**
   * Constructor from ROM.
   * @param rom ROM to read from.
   */
  EditableWaterSplashGraphicTable(LoadedROM& rom,
                                  Taddress tableStart__,
                                  const int subKeyTable[],
                                  int numPrimaryKeys);
  
  /** 
   * Returns the DataChunkID of the object.
   */
  DataChunkIDs::DataChunkID dataChunkID();

  /** 
   * Returns the version number of the object.
   */
  int version();

  /** 
   * Returns the maximum loadable version number of the object.
   */
  int maxVersion();
protected:
  
};


};


#endif
