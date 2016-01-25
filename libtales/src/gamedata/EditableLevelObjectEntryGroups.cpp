#include "gamedata/EditableLevelObjectEntryGroups.h"
#include "exception/OutOfRangeIndexException.h"
#include "exception/TGenericException.h"
#include "exception/NotEnoughSpaceException.h"
#include "exception/UnrecognizedVersionException.h"
#include "gamegear/LoadedROM.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"
#include "util/StringConversion.h"
#include <cstring>
#include <iostream>

using namespace Luncheon;

namespace Tales {


EditableLevelObjectEntryGroups::EditableLevelObjectEntryGroups()
  : TwoKeyIndexedEditableMappedData<LevelObjectEntryGroup>(),
    movedToNewBank_(false),
    tableHeaderSize_(0),
    initialTableAddress_(0),
    initialTableContentSize_(0) { };

EditableLevelObjectEntryGroups::EditableLevelObjectEntryGroups(
                         LoadedROM& rom,
                         Taddress tableHeaderAddress,
                         Taddress tableContentAddress,
                         Taddress tableEndAddress,
                         int numEntries)
  : TwoKeyIndexedEditableMappedData<LevelObjectEntryGroup>(rom,
                                 tableHeaderAddress,
                                 tableContentAddress,
                                 tableEndAddress,
                                 numEntries,
                                 SubMaps::subMapLevelObjectTableCounts,
                                 primaryMapLimit),
    movedToNewBank_(false),
    tableHeaderSize_(tableContentAddress - tableHeaderAddress),
    initialTableAddress_(tableHeaderAddress),
    initialTableContentSize_(tableEndAddress - tableContentAddress) {
    
    // For seemingly no reason except to fuck us over, some of the
    // table entries are non-contiguous, so we can't use this
/*  readAllDataAndConstruct(rom,
                   tableHeaderAddress,
                   tableContentAddress,
                   tableEndAddress,
                   numEntries); */
                   
//  std::cout << "****** THIS ONE ********" << std::endl;
                   
  readAndConstruct(rom,
                   tableHeaderAddress,
                   tableEndAddress);
                   
//  std::cout << mapnumToAddress_.numPrimaryKeys() << std::endl;
  
  // Copy C1 and C3 code segments for exporting
  
  std::memcpy(codeSegmentC1,
              rom.directRead(addressOfC1Segment),
              lengthOfC1Segment);
              
  std::memcpy(codeSegmentC3,
              rom.directRead(addressOfC3Segment),
              lengthOfC3Segment);
  
}

int EditableLevelObjectEntryGroups::maxTotalEntries() {
  return maxTotalEntries_;
}

int EditableLevelObjectEntryGroups::totalEntries() {
  // Add up number of objects in each group
  int totalObjects = 0;
  for (BaseEditableMappedData<LevelObjectEntryGroup>::IndexDataMap::iterator
          it = primaryStorage_.begin();
       it != primaryStorage_.end();
       ++it) {
    totalObjects += it->size();
  }
  
  return totalObjects;
}

int EditableLevelObjectEntryGroups::groupSize(int groupIndex) {
  // Throw if index out of range
  if ((unsigned int)groupIndex >= primaryStorage_.size()) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "EditableLevelObjectEntryGroups"
                                   "::groupSize(int)",
                                   groupIndex);
  }
  
  // Return size of group
  return primaryStorage_[groupIndex].size();
}

void EditableLevelObjectEntryGroups::addEntry(int groupIndex,
              const LevelObjectEntry& entry) {
  // Throw if index out of range
  if ((unsigned int)groupIndex >= primaryStorage_.size()) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "EditableLevelObjectEntryGroups"
                                   "::addEntry(int, const LevelObjectEntry&)",
                                   groupIndex);
  }
  
  // Throw if max number of objects reached
  if (totalEntries() >= maxTotalEntries()) {
    throw TGenericException(TALES_SRCANDLINE,
                                   "EditableLevelObjectEntryGroups"
                                   "::addEntry(int, const LevelObjectEntry&)",
                                   "Max object limit exceeded");
  }

  primaryStorage_[groupIndex].addEntry(entry);
}

void EditableLevelObjectEntryGroups::eraseEntry(int groupIndex,
                const LevelObjectEntryCollection::iterator& entryIt) {
  // Throw if index out of range
  if ((unsigned int)groupIndex >= primaryStorage_.size()) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "EditableLevelObjectEntryGroups"
                                   "::eraseEntry(int, const"
                                   " LevelObjectEntryCollection::iterator&)",
                                   groupIndex);
  }

  primaryStorage_[groupIndex].eraseEntry(entryIt);
}
                  
LevelObjectEntryGroup& EditableLevelObjectEntryGroups::group(int groupIndex) {
  // Throw if index out of range
  if ((unsigned int)groupIndex >= primaryStorage_.size()) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "EditableLevelObjectEntryGroups"
                                   "::group(int)",
                                   groupIndex);
  }

  return primaryStorage_[groupIndex];
}
                  
const LevelObjectEntryGroup& EditableLevelObjectEntryGroups
    ::group(int groupIndex) const {
  // Throw if index out of range
  if ((unsigned int)groupIndex >= primaryStorage_.size()) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "EditableLevelObjectEntryGroups"
                                   "::group(int) const",
                                   groupIndex);
  }

  return primaryStorage_[groupIndex];
}

LevelObjectEntryCollection::iterator EditableLevelObjectEntryGroups
    ::groupBegin(int groupIndex) {
  // Throw if index out of range
  if ((unsigned int)groupIndex >= primaryStorage_.size()) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "EditableLevelObjectEntryGroups"
                                   "::groupBegin(int)",
                                   groupIndex);
  }

  return primaryStorage_[groupIndex].begin();
}

LevelObjectEntryCollection::iterator EditableLevelObjectEntryGroups
    ::groupEnd(int groupIndex) {
  // Throw if index out of range
  if ((unsigned int)groupIndex >= primaryStorage_.size()) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "EditableLevelObjectEntryGroups"
                                   "::groupEnd(int)",
                                   groupIndex);
  }

  return primaryStorage_[groupIndex].end();
}

LevelObjectEntryCollection::const_iterator EditableLevelObjectEntryGroups
    ::groupCbegin(int groupIndex) const {
  // Throw if index out of range
  if ((unsigned int)groupIndex >= primaryStorage_.size()) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "EditableLevelObjectEntryGroups"
                                   "::groupCbegin(int) const",
                                   groupIndex);
  }

  return primaryStorage_[groupIndex].cbegin();
}

LevelObjectEntryCollection::const_iterator EditableLevelObjectEntryGroups
    ::groupCend(int groupIndex) const {
  // Throw if index out of range
  if ((unsigned int)groupIndex >= primaryStorage_.size()) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "EditableLevelObjectEntryGroups"
                                   "::groupCend(int) const",
                                   groupIndex);
  }

  return primaryStorage_[groupIndex].cend();
}

void EditableLevelObjectEntryGroups::save(std::string& data) {
  Tbyte buffer[ByteSizes::uint32Size];
  SaveHelper saver(data,
                   DataChunkIDs::levelObjectEntryGroups,
                   0);
  
  ByteConversion::toBytes(static_cast<int>(movedToNewBank_),
                          buffer,
                          ByteSizes::uint8Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint8Size);
  
  ByteConversion::toBytes(tableHeaderSize_,
                          buffer,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint32Size);
  
  ByteConversion::toBytes(initialTableAddress_,
                          buffer,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint32Size);
  
  ByteConversion::toBytes(initialTableContentSize_,
                          buffer,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint32Size);
  
  // Save C1 and C3 code segments
  
  data += std::string((char*)codeSegmentC1, lengthOfC1Segment);
  
  data += std::string((char*)codeSegmentC3, lengthOfC3Segment);
  
//  BaseEditableMappedData<LevelObjectEntryGroup>::save(data);

  BaseEditableMappedData<LevelObjectEntryGroup>
      ::saveInternal(data);
  
  saver.finalize();
}

int EditableLevelObjectEntryGroups::load(const Tbyte* data) {
  int byteCount = 0;
  LoadHelper loader(data,
                    byteCount);
                    
  if (loader.version() > 0) {
    throw UnrecognizedVersionException(TALES_SRCANDLINE,
                                       "EditableLevelObjectEntryGroups::load("
                                       "const Tbyte*)",
                                       DataChunkIDs::levelObjectEntryGroups,
                                       "EditableLevelObjectEntryGroups",
                                       loader.version(),
                                       0);
  }
  
  movedToNewBank_ = static_cast<bool>(
                      ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint8Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign));
  byteCount += ByteSizes::uint8Size;
  
  tableHeaderSize_ = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint32Size;
  
  initialTableAddress_ = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint32Size;
  
  initialTableContentSize_ = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint32Size;
  
  // Read C1 and C3 code segments
  
  std::memcpy(codeSegmentC1,
              data + byteCount,
              lengthOfC1Segment);
  byteCount += lengthOfC1Segment;
  
  std::memcpy(codeSegmentC3,
              data + byteCount,
              lengthOfC3Segment);
  byteCount += lengthOfC3Segment;
  
//  byteCount
//      += BaseEditableMappedData<LevelObjectEntryGroup>::load(data
//                                                             + byteCount);

  int mainLoadByteCount = 0;
  BaseEditableMappedData<LevelObjectEntryGroup>
            ::loadInternal(data + byteCount,
                           mainLoadByteCount);
  byteCount += mainLoadByteCount;
      
  return byteCount;
}

void EditableLevelObjectEntryGroups::exportToROM(WritableROM& rom) {
  
  Taddress exportAddress = initialTableAddress_;
  
  // Get total size of table content
  int exportSize = totalExportedSize();
  
  // If there's not enough space at the table's original location
  // to export it in-place, we have to find a new home for it
  if (exportSize > initialTableContentSize_) {
    // If we already moved banks, throw (we can't get any more room)
/*    if (movedToNewBank_) {
      throw TGenericException(TALES_SRCANDLINE,
                             "EditableLevelObjectEntryGroups::"
                             "exportToROM(WritableROM&)",
                             std::string("Need ")
                             + StringConversion::toString(
                                  exportSize)
                             + " bytes, but already"
                             "moved to new bank");
    } */
    
    // Move to new bank
    exportAddress = moveToNewBank(rom);
    
//    std::cout << exportAddress << std::endl;
  }
  
  exportTable(exportAddress,
              rom);
}

Taddress EditableLevelObjectEntryGroups::moveToNewBank(WritableROM& rom) {

//  std::cout << "Preparing to move to new bank" << std::endl;
  
  // More for convenience than anything else, we grab a whole bank of data
  // for use by this table (and a few bits of associated code).
  // Note that this basically requires expanding the ROM to 1 MB
  FreeSpaceList::iterator spaceIt
      = rom.freeSpace().getFreeSpace(LoadedROM::bankSize);
  
  // Throw if a full bank isn't available
  if (spaceIt == rom.freeSpace().freeSpaceList().end()) {
    throw NotEnoughSpaceException(TALES_SRCANDLINE,
                                  "EditableLevelObjectEntryGroups::"
                                  "exportToROM(WritableROM&)",
                                  LoadedROM::bankSize);
  }
  
//  std::cout << spaceIt->address() << " " << spaceIt->length() << std::endl;
                             
  Taddress newBaseAddress = spaceIt->address();
  
  // Claim the bank
  rom.freeSpace().claimSpace(spaceIt,
                             LoadedROM::bankSize);
  
//  std::cout << "New base address: " << newBaseAddress << std::endl;
  
  // Copy code segments C1 and C3 to new bank.
  // C1 and C3 both contain code that references the object table,
  // so they must (to avoid more complicated hacking) be in the same bank.
  // After rearranging the code, the new bank will contain C1, C3, and
  // the object table, in that order, starting from the beginning of the
  // bank
  
  // Copy C1 to start of bank
  Taddress newC1Address = newBaseAddress;
  std::memcpy(rom.directWrite(newC1Address),
              codeSegmentC1,
              lengthOfC1Segment);
              
  // Copy C3 to directly after C1
  Taddress newC3Address = newC1Address
                            + lengthOfC1Segment;
  std::memcpy(rom.directWrite(newC3Address),
              codeSegmentC3,
              lengthOfC3Segment);
  
  // Set new export address for table (directly after C3)
  int exportAddress = newBaseAddress
                    + lengthOfC1Segment
                    + lengthOfC3Segment;
                    
//  std::cout << "New C1 address: " << newC1Address << std::endl;
//  std::cout << "New C3 address: " << newC3Address << std::endl;
//  std::cout << "Export address: " << exportAddress << std::endl;
  
  // Update all the code that references the old locations of C1 and C3
  
  // Get the banked address for the new direct address of C1
  int newC1BankNum = LoadedROM::directToBankNum(newC1Address);
  int newC1BankedAddress = LoadedROM::directToBankedAddress(newC1Address);
  
  // Get the banked address for the new direct address of C3
  int newC3BankNum = LoadedROM::directToBankNum(newC3Address);
  int newC3BankedAddress = LoadedROM::directToBankedAddress(newC3Address);
  
  // Update bank number in code that calls C1
  ByteConversion::toBytes(newC1BankNum,
                          rom.directWrite(callReferenceToC1Bank),
                          ByteSizes::uint8Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  
  // C1's banked address is the same (0000), so we don't need to update it
  // ... but do anyway for consistency
  ByteConversion::toBytes(newC1BankedAddress,
                          rom.directWrite(callReferenceToC1Address),
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  
  // Update banked address in code that calls C3
  ByteConversion::toBytes(newC3BankNum,
                          rom.directWrite(callReferenceToC3Bank),
                          ByteSizes::uint8Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  
  // Update bank number in code that calls C3.
  ByteConversion::toBytes(newC3BankedAddress,
                          rom.directWrite(callReferenceToC3Address),
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  
  // C3 contains a hardcoded JP instruction into itself. Since we moved
  // C3, we have to update the JP to correspond to the new location.
  
  // Get new address of the JP instruction's address parameter
  Taddress addressOfNewJpParameter = newC3Address
                                      + offsetOfJpInC3;
  
  // Get new address of the JP instruction's jump point base
  Taddress addressOfNewJpBase = newC3Address
                                      + baseOffsetOfJpInC3;
  
  // Compute the new target address
  Taddress newJpTargetAddress = addressOfNewJpBase
                                  - absoluteLengthOfJpInC3;
                                  
//  std::cout << "New JP target: " << newJpTargetAddress << std::endl;
                                  
  // Convert to banked form
  Taddress newJpTargetBankedAddress
      = LoadedROM::directToBankedAddress(newJpTargetAddress);
  
  // Write the new target address to the JP parameter
  ByteConversion::toBytes(newJpTargetBankedAddress,
                          rom.directWrite(addressOfNewJpParameter),
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  
  // Get the banked address for the new direct address of the object table
//    int newTableBankNum
//        = LoadedROM::directToBankNum(exportAddress);
  int newTableBankedAddress
      = LoadedROM::directToBankedAddress(exportAddress);
  
  // Update C1 to refer to the new location of the object table
  ByteConversion::toBytes(newTableBankedAddress,
                          rom.directWrite(newC1Address
                                          + offsetOfTableReferenceInC1),
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  
  // Update C3 to refer to the new location of the object table
  ByteConversion::toBytes(newTableBankedAddress,
                          rom.directWrite(newC3Address
                                          + offsetOfTableReferenceInC3),
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  
  // Update table information
//    initialTableAddress_ = exportAddress;

//  initialTableContentSize_ = spaceIt->length()
//                              - exportAddress
//                              - tableHeaderSize_;

//  initialTableContentSize_ = exportAddress - spaceIt->address()
//                              - tableHeaderSize_;

//  initialTableContentSize_ = LoadedROM::bankSize;
                              
//  std::cout << initialTableContentSize_ << std::endl;
  
  // Mark that we've moved to a new bank
  movedToNewBank_ = true;
  
  return exportAddress;
}
  
void EditableLevelObjectEntryGroups::exportTable(
                 Taddress exportAddress,
                 WritableROM& rom) {
  
//  std::cout << "Exporting to: " << exportAddress << std::endl;
  
  // Subkey address write location
  Taddress subkeyWriteAddress = exportAddress
                                 + (primaryMapLimit
                                    * ByteSizes::uint16Size);
                                    
//  std::cout << std::hex << subkeyWriteAddress << std::endl;
  
  // Determine total number of maps to output
  int numSubkeyEntries = 0;
  for (int i = 0; i < mapnumToAddress_.numPrimaryKeys(); i++) {
    // If at least one entry for this primary key, use first entry
    if (mapnumToAddress_.subKeyTable()[i] > 0) {
      numSubkeyEntries += mapnumToAddress_.subKeyTable()[i];
    }
  }
  
  // Compute base address for entries
  Taddress entryWriteAddress = subkeyWriteAddress
                                 + (numSubkeyEntries
                                    * ByteSizes::uint16Size);
                                 
  // Temporarily convert address table to index table
  for (int i = 0; i < mapnumToAddress_.numPrimaryKeys(); i++) {
    for (int j = 0; j < mapnumToAddress_.subKeyTable()[i]; j++) {
    
      Taddress& addr = mapnumToAddress_.refDataByKeys(
                            i + TwoKeyedAddress::primaryKeyBase,
                            j + TwoKeyedAddress::subKeyBase);
      
      int ind = addressToIndex_.findValueOrThrow(addr);
      
      addr = ind;
    }
  }
  
  // Clear address to index map
  addressToIndex_.clear();
  
  // Create temporary mapping of indices to address
  Tmap<int, Taddress> indToAddr;
                                 
  for (int i = 0; i < primaryStorage_.size(); i++) {
    
    // Add new (temporary) index->address mapping
    indToAddr.insert(Tmap<int, Taddress>::PairType(
                      i, entryWriteAddress));
                      
    // Write entry to ROM
    int writeLength = primaryStorage_[i].writeToData(
                        rom.directWrite(entryWriteAddress));
    
    // Add new address->index mapping
    addressToIndex_.insert(
      BaseEditableMappedData<LevelObjectEntryGroup>
          ::AddressIndexPair(
              entryWriteAddress,
              i));
                      
    // Write subkey address
/*    Taddress bankedAddress = LoadedROM::directToBankedAddress(
                                entryWriteAddress);
    ByteConversion::toBytes(bankedAddress,
                            rom.directWrite(subkeyWriteAddress),
                            ByteSizes::uint16Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
                            
//    std::cout << std::hex << "value: " << bankedAddress << std::endl;
//    std::cout << std::hex << "addr: " << subkeyWriteAddress << std::endl;
    
    // Move to next address
    subkeyWriteAddress += ByteSizes::uint16Size; */
    entryWriteAddress += writeLength;
  }
  
  // Write the address table to the export location
  Taddress primaryWriteAddress = exportAddress;
  int totalMaps = 0;
  for (int i = 0; i < mapnumToAddress_.numPrimaryKeys(); i++) {
    
    Taddress bankedAddress = exportAddress
                           + (primaryMapLimit
                               * ByteSizes::uint16Size);
    
    // If at least one entry for this primary key, use first entry
    if (mapnumToAddress_.subKeyTable()[i] > 0) {
      bankedAddress += (totalMaps * ByteSizes::uint16Size);
      totalMaps += mapnumToAddress_.subKeyTable()[i];
/*      bankedAddress
        = indToAddr.findValueOrThrow(
                        mapnumToAddress_.refDataByKeys(
                            i + TwoKeyedAddress::primaryKeyBase,
                            TwoKeyedAddress::subKeyBase)); */
    }
    
    bankedAddress = LoadedROM::directToBankedAddress(bankedAddress);
    
    // Write primary address
    ByteConversion::toBytes(bankedAddress,
                            rom.directWrite(primaryWriteAddress),
                            ByteSizes::uint16Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    primaryWriteAddress += ByteSizes::uint16Size;
  
    // Convert indices back to addresses
    for (int j = 0; j < mapnumToAddress_.subKeyTable()[i]; j++) {
      Taddress& ind = mapnumToAddress_.refDataByKeys(
                            i + TwoKeyedAddress::primaryKeyBase,
                            j + TwoKeyedAddress::subKeyBase);
                            
//      std::cout << ind << std::endl;
      
      // Get address corresponding to this index
      Taddress address = indToAddr.findValueOrThrow(ind);
      
//      std::cout << address << std::endl;
      
      // Write subkey address
      Taddress bankedSubAddress = LoadedROM::directToBankedAddress(
                                  address);
      ByteConversion::toBytes(bankedSubAddress,
                              rom.directWrite(subkeyWriteAddress),
                              ByteSizes::uint16Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign);
      
      // Move to next address
      subkeyWriteAddress += ByteSizes::uint16Size;
                            
      // Convert indexed address table back to address table
      ind = address;
    }
  }

  // Export each data element to ROM
/*  for (typename AddressIndexMap::iterator it = addressToIndex_.begin();
       it != addressToIndex_.end();
       it++) {
    // Address to write to
    Taddress address = it->first;
    
    // Write data
    exportElementToROM(rom,
                       address,
                       primaryStorage_[it->second]);
  } */
}

void EditableLevelObjectEntryGroups::readAndConstructReadStep(
                                      LoadedROM& rom,
                                      Taddress tableEndAddress) {
  // Iterate over primary storage addresses and read corresponding data
  for (AddressIndexMap::iterator it = addressToIndex_.begin();
       it != addressToIndex_.end();
       ++it) {
//      std::cout << "start: " << it->first << std::endl;
    
    Taddress startAddress = it->first;
    
    // Read elements in array
    LevelObjectEntryGroup dst;
    readElements(dst,
                 rom.directRead(startAddress),
                 1);
    
    // Add read elements to primary storage
    primaryStorage_[it->second] = LevelObjectEntryGroup(dst);
  }
}

int EditableLevelObjectEntryGroups::totalExportedSize() {
  int total = 0;
  
  // Add up raw size of each contained entry group
  for (BaseEditableMappedData<LevelObjectEntryGroup>::IndexDataMap::iterator
          it = primaryStorage_.begin();
       it != primaryStorage_.end();
       it++) {
    total += it->rawSize();
  }
  
  return total;
}

int EditableLevelObjectEntryGroups::dataSizeOfOneElement() {
  // this doesn't make sense here
//  std::cout << "here" << std::endl;
  return 0;
}

int EditableLevelObjectEntryGroups::readElements(LevelObjectEntryGroup& dst,
                         const Tbyte* data,
                         int numElements) {
  int byteCount = 0;
  
  for (int i = 0; i < numElements; i++) {
    // Read data
    byteCount += dst.readFromData(data + byteCount);
  }
  
  return byteCount;
}

void EditableLevelObjectEntryGroups::saveElement(std::string& data,
                          LevelObjectEntryGroup& src) {
  src.save(data);
}

int EditableLevelObjectEntryGroups::loadElement(LevelObjectEntryGroup& dst,
                        const Tbyte* data) {
  return dst.load(data);
}

void EditableLevelObjectEntryGroups::exportElementToROM(WritableROM& rom,
                                Taddress address,
                                LevelObjectEntryGroup& src) {
  src.writeToData(rom.directWrite(address));
}
  
DataChunkIDs::DataChunkID EditableLevelObjectEntryGroups::dataChunkID() {
  return DataChunkIDs::levelObjectEntryGroups;
}

std::string EditableLevelObjectEntryGroups::dataChunkName() {
  return "EditableLevelObjectEntryGroups";
}

int EditableLevelObjectEntryGroups::chunkVersionNumber() {
  return 0;
}

int EditableLevelObjectEntryGroups::maxRecognizedVersionNumber() {
  return 0;
}


};
