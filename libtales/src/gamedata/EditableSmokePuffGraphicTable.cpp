#include "gamedata/EditableSmokePuffGraphicTable.h"

namespace Tales {


EditableSmokePuffGraphicTable::EditableSmokePuffGraphicTable()
  : BaseEditableFixedGraphicTable() { };

EditableSmokePuffGraphicTable::EditableSmokePuffGraphicTable(
                                LoadedROM& rom,
                                Taddress tableStart__,
                                const int subKeyTable[],
                                int numPrimaryKeys)
  : BaseEditableFixedGraphicTable(rom,
                                  tableStart__,
                                  subKeyTable,
                                  numPrimaryKeys) { };

DataChunkIDs::DataChunkID EditableSmokePuffGraphicTable::dataChunkID() {
  return DataChunkIDs::smokePuffGraphicTable;
}

int EditableSmokePuffGraphicTable::version() {
  return 0;
}

int EditableSmokePuffGraphicTable::maxVersion() {
  return 0;
}


};
