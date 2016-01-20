#include "gamedata/EditableLeafGraphicsTable.h"
#include "exception/OutOfRangeIndexException.h"
#include "structs/SaveHelper.h"
#include "structs/LoadHelper.h"
#include "structs/DataChunkID.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"
#include <iostream>

using namespace Luncheon;

namespace Tales {


EditableLeafGraphicsTable::EditableLeafGraphicsTable()
  : address_(0) { };

EditableLeafGraphicsTable::EditableLeafGraphicsTable(
                          LoadedROM& rom,
                          Taddress address__)
  : address_(address__) {
  readFromData(rom.directRead(address__));
}
                          
int& EditableLeafGraphicsTable::entry(int index) {
  // Table is 1-based -- only indices 1 through [datasize] are valid
  --index;

  // Throw if out of range
  if ((unsigned int)index >= dataSize) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "EditableLeafGraphicsTable::entry(int)",
                                   index);
  }

  return tableEntries[index];
}
                          
void EditableLeafGraphicsTable::save(std::string& data) {
  SaveHelper saver(data,
                   DataChunkIDs::leafGraphicsTable,
                   0);
                   
  Tbyte buffer[ByteSizes::uint32Size];
  ByteConversion::toBytes(address_,
                          buffer,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint32Size);

  Tbyte buffer2[dataSize];
  writeToData(buffer2);
  data += std::string((char*)buffer2, dataSize);
  
  saver.finalize();
}

int EditableLeafGraphicsTable::load(const Tbyte* data) {
  int byteCount = 0;

  LoadHelper loader(data + byteCount,
                    byteCount);
  
  address_ = ByteConversion::fromBytes(data + byteCount,
                                       ByteSizes::uint32Size,
                                       EndiannessTypes::little,
                                       SignednessTypes::nosign);
  byteCount += ByteSizes::uint32Size;

  byteCount += readFromData(data + byteCount);
  
  return byteCount;
}

void EditableLeafGraphicsTable::exportToROM(WritableROM& rom) {
  writeToData(rom.directWrite(address_));
}
  
int EditableLeafGraphicsTable::writeToData(Tbyte* data) {
  int byteCount = 0;
  
  for (int i = 0; i < dataSize; i++) {
    ByteConversion::toBytes(tableEntries[i],
                            data + byteCount,
                            ByteSizes::uint8Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    byteCount += ByteSizes::uint8Size;
  }
  
  return byteCount;
}
  
int EditableLeafGraphicsTable::readFromData(const Tbyte* data) {
  int byteCount = 0;

  for (int i = 0; i < dataSize; i++) {
    int value = ByteConversion::fromBytes(data + byteCount,
                                          ByteSizes::uint8Size,
                                          EndiannessTypes::little,
                                          SignednessTypes::nosign);
    byteCount += ByteSizes::uint8Size;
    
    tableEntries[i] = value;
  }
  
  return byteCount;
}


};
