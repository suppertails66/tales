#include "gamedata/EditableRadioMusic.h"
#include "exception/OutOfRangeIndexException.h"
#include "exception/UnrecognizedVersionException.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"
#include <iostream>

namespace Tales {


EditableRadioMusic::EditableRadioMusic()
  : address_(0) { };

EditableRadioMusic::EditableRadioMusic(
                   LoadedROM& rom,
                   Taddress address__,
                   int numEntries)
  : address_(address__) {
  
  Taddress readAddress = address__;
  for (int i = 0; i < numEntries; i++) {
    int musicValue = ByteConversion::fromBytes(
                            rom.directRead(readAddress),
                            ByteSizes::uint8Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    readAddress += ByteSizes::uint8Size;
    
    musicEntries_.push_back(musicValue);
  }
}
                   
int EditableRadioMusic::numMusicEntries() const {
  return musicEntries_.size();
}
                   
int& EditableRadioMusic::musicEntry(int index) {
  if (index >= musicEntries_.size()) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "EditableRadioMusic::musicEntry(int)",
                                   index);
  }

  return musicEntries_[index];
}

void EditableRadioMusic::save(std::string& data) {
  Tbyte buffer[ByteSizes::uint32Size];
  SaveHelper saver(data,
                   DataChunkIDs::radioMusic,
                   0);

  ByteConversion::toBytes(address_,
                          buffer,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint32Size);

  ByteConversion::toBytes(musicEntries_.size(),
                          buffer,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint32Size);
  
  for (int i = 0; i < musicEntries_.size(); i++) {
    ByteConversion::toBytes(musicEntries_[i],
                            buffer,
                            ByteSizes::uint8Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    data += std::string((char*)buffer, ByteSizes::uint8Size);
  }
  
  saver.finalize();
}

int EditableRadioMusic::load(const Tbyte* data) {
  musicEntries_.clear();
  int byteCount = 0;
  LoadHelper loader(data,
                    byteCount);
                    
  if (loader.version() > 0) {
    throw UnrecognizedVersionException(TALES_SRCANDLINE,
                                       "EditableRadioMusic::load("
                                       "const Tbyte*)",
                                       DataChunkIDs::radioMusic,
                                       "EditableRadioMusic",
                                       loader.version(),
                                       0);
  }
  
  address_ = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint32Size;
  
  int numMusicEntries = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint32Size;
  
  for (int i = 0; i < numMusicEntries; i++) {
    int entry = ByteConversion::fromBytes(
                            data + byteCount,
                            ByteSizes::uint8Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    byteCount += ByteSizes::uint8Size;
    
    musicEntries_.push_back(entry);
  }
  
  return byteCount;
}

void EditableRadioMusic::exportToROM(WritableROM& rom) {
  Taddress writeAddress = address_;
  
  for (int i = 0; i < musicEntries_.size(); i++) {
    ByteConversion::toBytes(musicEntries_[i],
                            rom.directWrite(writeAddress),
                            ByteSizes::uint8Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    writeAddress += ByteSizes::uint8Size;
  }
}


};
