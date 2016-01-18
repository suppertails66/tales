#include "gamedata/EditableWaterSplashGraphicTable.h"

namespace Tales {


EditableWaterSplashGraphicTable::EditableWaterSplashGraphicTable()
  : BaseEditableFixedGraphicTable() { };

EditableWaterSplashGraphicTable::EditableWaterSplashGraphicTable(
                                LoadedROM& rom,
                                Taddress tableStart__,
                                const int subKeyTable[],
                                int numPrimaryKeys)
  : BaseEditableFixedGraphicTable(rom,
                                  tableStart__,
                                  subKeyTable,
                                  numPrimaryKeys) { };

DataChunkIDs::DataChunkID EditableWaterSplashGraphicTable::dataChunkID() {
  return DataChunkIDs::waterSplashGraphicTable;
}

int EditableWaterSplashGraphicTable::version() {
  return 0;
}

int EditableWaterSplashGraphicTable::maxVersion() {
  return 0;
}


}; 
