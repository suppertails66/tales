#include "gamedata/EditableLevelEffectsHeaders.h"
#include "exception/UnrecognizedVersionException.h"
#include <iostream>

namespace Tales {


EditableLevelEffectsHeaders::EditableLevelEffectsHeaders()
  : TwoKeyIndexedEditableMappedData<LevelEffectsHeader>() { };

EditableLevelEffectsHeaders::EditableLevelEffectsHeaders(
                         LoadedROM& rom,
                         Taddress tableHeaderAddress,
                         Taddress tableContentAddress,
                         Taddress tableEndAddress,
                         int numEntries)
  : TwoKeyIndexedEditableMappedData<LevelEffectsHeader>(rom,
                                 tableHeaderAddress,
                                 tableContentAddress,
                                 tableEndAddress,
                                 numEntries,
                                 SubMaps::subMapCounts,
                                 primaryMapLimit) {
  readAllDataAndConstruct(rom,
                   tableHeaderAddress,
                   tableContentAddress,
                   tableEndAddress,
                   numEntries);
}

LevelEffectsHeader& EditableLevelEffectsHeaders::headersByMapnum(
                                    int primaryMapNum,
                                    int subMapNum) {
  return dataByMapnum(primaryMapNum,
                      subMapNum);
}

int EditableLevelEffectsHeaders::dataSizeOfOneElement() {
  return LevelEffectsHeader::dataSize;
}

int EditableLevelEffectsHeaders::readElements(LevelEffectsHeader& dst,
                         const Tbyte* data,
                         int numElements) {
  int byteCount = 0;
  
  for (int i = 0; i < numElements; i++) {
    // Read data
    byteCount += dst.readFromData(data + byteCount);
  }
  
  return byteCount;
}

void EditableLevelEffectsHeaders::saveElement(std::string& data,
                          LevelEffectsHeader& src) {
  src.save(data);
}

int EditableLevelEffectsHeaders::loadElement(LevelEffectsHeader& dst,
                        const Tbyte* data) {
  return dst.load(data);
}

void EditableLevelEffectsHeaders::exportElementToROM(WritableROM& rom,
                                Taddress address,
                                LevelEffectsHeader& src) {
  src.writeToData(rom.directWrite(address));
}
  
DataChunkIDs::DataChunkID EditableLevelEffectsHeaders::dataChunkID() {
  return DataChunkIDs::levelEffectsHeaders;
}

std::string EditableLevelEffectsHeaders::dataChunkName() {
  return "EditableLevelEffectsHeaders";
}

int EditableLevelEffectsHeaders::chunkVersionNumber() {
  return 0;
}

int EditableLevelEffectsHeaders::maxRecognizedVersionNumber() {
  return 0;
}

//void EditableLevelEffectsHeaders::prepareIndices() {
//  TwoKeyEditableMappedData<LevelEffectsHeader>::prepareIndices();
//}

/*void EditableLevelEffectsHeaders::readAllDataAndConstruct(
                      LoadedROM& rom,
                      Taddress tableHeaderAddress,
                      Taddress tableContentAddress,
                      Taddress tableEndAddress,
                      int numEntries) {
//    std::cout << "TABLE HEADER: " << tableHeaderAddress << std::endl;
//    std::cout << "TABLE END: " << tableEndAddress << std::endl;
                      
  // Read address table
  readAddressTable(rom,
                   tableHeaderAddress);
                   
//    std::cout << "header: " << tableHeaderAddress << std::endl;
//    std::cout << "end: " << tableEndAddress << std::endl;
  
//  prepareIndices();

  // Read all data
  Taddress dataReadAddress = tableContentAddress;
  for (int i = 0; i < numEntries; i++) {
    // Insert address to index mapping
    ParentType::addressToIndex_.insert(
      ParentType::AddressIndexPair(
        dataReadAddress,
        ParentType::primaryStorage_.size()));
        
    // Read header
    LevelEffectsHeader header;
    dataReadAddress += header.readFromData(rom.directRead(dataReadAddress));
    
    // Add to storage
    ParentType::primaryStorage_.push_back(header);
  }

  // Iterate over each read address
  
  // Read the entries
  readAndConstructReadStep(rom,
                           tableEndAddress);
  
//    std::cout << "\n\n\n***DONE***\n\n\n";
} */


};
