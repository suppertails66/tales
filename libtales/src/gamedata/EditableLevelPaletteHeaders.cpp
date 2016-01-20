#include "gamedata/EditableLevelPaletteHeaders.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"
#include "exception/OutOfRangeIndexException.h"
#include "exception/UnrecognizedVersionException.h"
#include <iostream>

namespace Tales {


EditableLevelPaletteHeaders::EditableLevelPaletteHeaders()
  : tableHeaderAddress_(0),
    tableContentAddress_(0) { };

EditableLevelPaletteHeaders::EditableLevelPaletteHeaders(
                            LoadedROM& rom,
                            Taddress tableHeaderAddress__,
                            Taddress tableContentAddress__,
                            int numContentEntries,
                            const int subKeyTable[],
                            int numPrimaryKeys)
  : mapnumToIndex_(subKeyTable,
                   numPrimaryKeys),
    tableHeaderAddress_(tableHeaderAddress__),
    tableContentAddress_(tableContentAddress__) {
  // Read the key index table
  
  int tableHeaderReadAddress = tableHeaderAddress_;
  for (int i = 0; i < mapnumToIndex_.numPrimaryKeys(); i++) {
    // Only set index if there is at least one submap
    if (mapnumToIndex_.subKeyTable()[i] > 0) {
      // Get banked address of data
      Taddress address
        = ByteConversion::fromBytes(
                            rom.directRead(tableHeaderReadAddress),
                            ByteSizes::uint16Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
      
      int index = LoadedROM::toIndex(
                             tableContentAddress_,
                             address,
                             LevelPaletteHeader::dataSize);
//      std::cout << "address: " << address << std::endl;
//      std::cout << "index: " << index << std::endl;
//      std::cout << "aewtnio: " << i << std::endl;
      
      // Convert address to index and store
      mapnumToIndex_.refDataByKeys(i, TwoKeyedAddress::subKeyBase)
        = index;
    }
    
    tableHeaderReadAddress += ByteSizes::uint16Size;
    
//    for (int j = 0; j < mapnumToIndex_.subKeyTable()[i]; j++) {
//    }
  }
  
  // This particular header table has a different format from most others:
  // there is a single table of primary map numbers to addresses, and
  // the game simply adds the appropriate amount for the submap to that
  // address
  // We simulate this by setting higher indices correspondingly
  for (int i = 0; i < mapnumToIndex_.numPrimaryKeys(); i++) {
    int nextIndex = 0;
    
    // Only get index if there is at least one submap
    if (mapnumToIndex_.subKeyTable()[i] > 0) {
      // Get the index for the first submap of the current primary map
      nextIndex = mapnumToIndex_.refDataByKeys(i,
                                               TwoKeyedAddress::subKeyBase);
      // Advance to next position;
      ++nextIndex;
      
    }
    for (int j = 1; j < mapnumToIndex_.subKeyTable()[i]; j++) {
      // Set each submap to the previous map plus one
      mapnumToIndex_.refDataByKeys(i, j + TwoKeyedAddress::subKeyBase)
        = nextIndex;
      ++nextIndex;
    }
  }
  
  // Read actual header entries
  int tableContentReadAddress = tableContentAddress_;
  for (int i = 0; i < numContentEntries; i++) {
    LevelPaletteHeader header;
    
    tableContentReadAddress
      += header.readFromData(rom.directRead(tableContentReadAddress));
      
    primaryStorage_.push_back(header);
  }
}

void EditableLevelPaletteHeaders::save(std::string& data) {
  // Output buffer
  Tbyte buffer[ByteSizes::uint32Size];
  SaveHelper saver(data,
                   DataChunkIDs::levelPaletteHeaders,
                   0);
  
//  std::cout << "size1: " << data.size() << std::endl;

  // Write header address
  ByteConversion::toBytes(tableHeaderAddress_,
                          buffer,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint32Size);

  // Write content address
  ByteConversion::toBytes(tableContentAddress_,
                          buffer,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint32Size);
                          
  // Write number of headers
  ByteConversion::toBytes(primaryStorage_.size(),
                          buffer,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint16Size);
  
  // Write headers
  for (LevelPaletteHeaderCollection::iterator it = primaryStorage_.begin();
       it != primaryStorage_.end();
       ++it) {
    it->save(data);
  }
  
//  std::cout << "size2: " << data.size() << std::endl;
  
  // Write map key table
  mapnumToIndex_.writeToData(data);
  
  saver.finalize();
}

int EditableLevelPaletteHeaders::load(const Tbyte* data) {
  // Clear existing storage
  primaryStorage_.clear();

  // Count of bytes read
  int byteCount = 0;
  LoadHelper loader(data,
                    byteCount);
                    
  if (loader.version() > 0) {
    throw UnrecognizedVersionException(TALES_SRCANDLINE,
                                       "EditableLevelPaletteHeaders::load("
                                       "const Tbyte*)",
                                       DataChunkIDs::levelPaletteHeaders,
                                       "EditableLevelPaletteHeaders",
                                       loader.version(),
                                       0);
  }
  
  // Get header address
  tableHeaderAddress_ = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint32Size;
  
  // Get content address
  tableContentAddress_ = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint32Size;
  
  // Get number of entries
  int numEntries = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint16Size;
  
  // Read each entry
  for (int i = 0; i < numEntries; i++) {
    LevelPaletteHeader header;
    
    byteCount += header.load(data + byteCount);
    
    primaryStorage_.push_back(header);
  }
  
//  std::cout << "bytecount: " << byteCount << std::endl;
  
  // Read map key table
  byteCount += mapnumToIndex_.readFromData(data + byteCount);
  
  // Return number of bytes read
  return byteCount;
}

void EditableLevelPaletteHeaders::exportToROM(WritableROM& rom) {
  // Write palette headers
  int contentWriteAddress = tableContentAddress_;
  for (LevelPaletteHeaderCollection::iterator it = primaryStorage_.begin();
       it != primaryStorage_.end();
       ++it) {
    it->exportToROM(rom,
                    contentWriteAddress);
    contentWriteAddress += LevelPaletteHeader::dataSize;
  }
  
  // Write table header
  int headerWriteAddress = tableHeaderAddress_;
//  std::cout << "start: " << std::hex << headerWriteAddress << std::endl;
  for (int i = 0; i < mapnumToIndex_.numPrimaryKeys(); i++) {
//    std::cout << "at: " << std::hex << headerWriteAddress << std::endl;
    // Only write used keys
    if (mapnumToIndex_.subKeyTable()[i] > 0) {
//      std::cout << '\t' << "writing " << std::hex << i << std::endl;
      int index = mapnumToIndex_.refDataByKeys(
                                         i,
                                         TwoKeyedAddress::subKeyBase);
//      std::cout << '\t' << "index: " << index << std::endl;
      // Get banked address of content
      Taddress address
        = LoadedROM::indexToBankedAddr(tableContentAddress_,
                                       index,
                                       LevelPaletteHeader::dataSize);
      
      Tbyte buffer[ByteSizes::uint16Size];
      ByteConversion::toBytes(address,
                              buffer,
                              ByteSizes::uint16Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign);
      
//      std::cout << "number: " << std::hex << i << std::endl;
//      std::cout << "write address: " << std::hex << headerWriteAddress << std::endl;
      
      // Write address to ROM
      rom.directWrite(headerWriteAddress,
                      buffer,
                      ByteSizes::uint16Size);
    }
    
    // Go to next address
    headerWriteAddress += ByteSizes::uint16Size;
  }
  
}

int EditableLevelPaletteHeaders::size() {
  return primaryStorage_.size();
}

int EditableLevelPaletteHeaders::indexOfMapNum(
                                   int primaryNum,
                                   int subNum) {
  // Throw if primary key out of range
  if (primaryNum >= mapnumToIndex_.numPrimaryKeys()) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "EditableLevelPaletteHeaders::"
                                   "indexOfMapNum(int,int) [PRIMARY]",
                                   primaryNum);
  }
  
  // Throw if subkey out of range
  if ((subNum - TwoKeyedAddress::subKeyBase)
        >= mapnumToIndex_.subKeyTable()[primaryNum]) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "EditableLevelPaletteHeaders::"
                                   "indexOfMapNum(int,int) [SUB]",
                                   subNum);
  }
  
  // Return index
  return mapnumToIndex_.refDataByKeys(primaryNum,
                                      subNum);
}

void EditableLevelPaletteHeaders::setIndexOfMapNum(
                      int primaryNum,
                      int subNum,
                      int index) {
  // Throw if primary key out of range
  if (primaryNum >= mapnumToIndex_.numPrimaryKeys()) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "EditableLevelPaletteHeaders::"
                                   "setIndexOfMapNum(int,int,int) [PRIMARY]",
                                   primaryNum);
  }
  
  // Throw if subkey out of range
  if (subNum >= mapnumToIndex_.subKeyTable()[primaryNum]) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "EditableLevelPaletteHeaders::"
                                   "setIndexOfMapNum(int,int,int) [SUB]",
                                   subNum);
  }
  
  // Set index
  mapnumToIndex_.refDataByKeys(primaryNum,
                               subNum)
    = index;
}

LevelPaletteHeader& EditableLevelPaletteHeaders::headerByIndex(
                                   int index) {
  // Throw if index out of range
  if ((unsigned int)index >= primaryStorage_.size()) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "EditableLevelPaletteHeaders::"
                                   "headerByIndex(int)",
                                   index);
  }
  
  // Return corresponding header
  return primaryStorage_[index];
}


};
