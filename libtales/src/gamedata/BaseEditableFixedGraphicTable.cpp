#include "gamedata/BaseEditableFixedGraphicTable.h"
#include "util/ByteSizes.h"
#include <iostream>

using namespace Luncheon;

namespace Tales {


BaseEditableFixedGraphicTable::BaseEditableFixedGraphicTable() { };

BaseEditableFixedGraphicTable::BaseEditableFixedGraphicTable(
                                 LoadedROM& rom,
                                 Taddress tableStart__,
                                 const int subKeyTable[],
                                 int numPrimaryKeys)
  : mapnumToAddress_(subKeyTable,
                     numPrimaryKeys),
    mapnumToData_(subKeyTable,
                  numPrimaryKeys) {
  // Read address table
  KeyedTableBuilder::buildKeyedPrimaryOnlyTable(rom,
                                            tableStart__
                                            // HACK: entries are 1-based
                                            // -- add fake 0 entry by
                                            // offsetting table start
                                              - ByteSizes::uint16Size,
                                            FixedGraphicTableEntry::dataSize,
                                            mapnumToAddress_);
//  std::cout << std::hex << tableStart__ << std::endl;
  
  // Read data
  for (int i = 0; i < mapnumToAddress_.numPrimaryKeys(); i++) {
    
    if (mapnumToAddress_.subKeyTable()[i] <= 0) {
      continue;
    }
    
    for (int j = 0; j < mapnumToAddress_.subKeyTable()[i]; j++) {
      Taddress address = mapnumToAddress_.refDataByKeys(
                            i + TwoKeyedAddress::primaryKeyBase,
                            j + TwoKeyedAddress::subKeyBase);
                            
//      std::cout << std::hex << address << std::endl;
      
      FixedGraphicTableEntry entry(rom.directRead(address));
      
      mapnumToData_.refDataByKeys(
                            i + TwoKeyedAddress::primaryKeyBase,
                            j + TwoKeyedAddress::subKeyBase)
        = entry;
    }
    
  }
}

void BaseEditableFixedGraphicTable::save(std::string& data) {
  SaveHelper saver(data,
                   dataChunkID(),
                   version());

  mapnumToAddress_.writeToData(data);
  
  // Save graphics data
  for (int i = 0; i < mapnumToData_.numPrimaryKeys(); i++) {
    for (int j = 0; j < mapnumToData_.subKeyTable()[i]; j++) {
      mapnumToData_.refDataByKeys(
                            i + TwoKeyedAddress::primaryKeyBase,
                            j + TwoKeyedAddress::subKeyBase)
        .save(data);
    }
  }
  
  saver.finalize();
}
  
int BaseEditableFixedGraphicTable::load(const Tbyte* data) {
  int byteCount = 0;

  LoadHelper loader(data,
                    byteCount);

  byteCount += mapnumToAddress_.readFromData(data + byteCount);
  
  // Resize mapnumToData_
  mapnumToData_ = FixedGraphicTableKeyMap(mapnumToAddress_.subKeyTable(),
                                          mapnumToAddress_.numPrimaryKeys());
  
  // Load graphics data
  for (int i = 0; i < mapnumToData_.numPrimaryKeys(); i++) {
    for (int j = 0; j < mapnumToData_.subKeyTable()[i]; j++) {
      byteCount += mapnumToData_.refDataByKeys(
                            i + TwoKeyedAddress::primaryKeyBase,
                            j + TwoKeyedAddress::subKeyBase)
                      .load(data + byteCount);
    }
  }
  
  return byteCount;
}
  
void BaseEditableFixedGraphicTable::exportToROM(WritableROM& rom) {
  for (int i = 0; i < mapnumToData_.numPrimaryKeys(); i++) {
    for (int j = 0; j < mapnumToData_.subKeyTable()[i]; j++) {
      Taddress address = mapnumToAddress_.refDataByKeys(
                            i + TwoKeyedAddress::primaryKeyBase,
                            j + TwoKeyedAddress::subKeyBase);
    
      mapnumToData_.refDataByKeys(
                            i + TwoKeyedAddress::primaryKeyBase,
                            j + TwoKeyedAddress::subKeyBase)
                      .writeToData(rom.directWrite(address));
    }
  }
}
  
FixedGraphicTableEntry& BaseEditableFixedGraphicTable::entry(int areaNum,
                                                            int mapNum) {
  return mapnumToData_.refDataByKeys(areaNum,
                                     mapNum);
}


};
