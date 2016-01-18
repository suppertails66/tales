#ifndef EDITABLESMOKEPUFFGRAPHICTABLE_H
#define EDITABLESMOKEPUFFGRAPHICTABLE_H


#include "gamedata/BaseEditableFixedGraphicTable.h"

namespace Tales {


class EditableSmokePuffGraphicTable
  : public BaseEditableFixedGraphicTable {
public:
  const static int numGraphicTiles = 6;
  
  /**
   * Default constructor.
   */
  EditableSmokePuffGraphicTable();
  
  /**
   * Constructor from ROM.
   * @param rom ROM to read from.
   */
  EditableSmokePuffGraphicTable(LoadedROM& rom,
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
};


};


#endif
