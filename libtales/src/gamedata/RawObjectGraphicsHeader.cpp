#include "gamedata/RawObjectGraphicsHeader.h"
#include "gamedata/RawObjectGraphicSubheader.h"
#include "exception/OutOfRangeIndexException.h"
#include <iostream>

namespace Tales {


RawObjectGraphicsHeader::RawObjectGraphicsHeader() { };

RawObjectGraphicsHeader::RawObjectGraphicsHeader(
                       LoadedROM& rom,
                       Taddress address) {
  Taddress readAddress = address;
  Tbyte endOfHeaderCheck = *(rom.directRead(readAddress));
  while (endOfHeaderCheck != endOfHeaderToken) {
    // Read subheader
    RawObjectGraphicSubheader subheader(rom,
                                        readAddress);
    
    // Add to storage
    rawObjectGraphicSubheaders_.push_back(subheader);
    
    // Move to next subheader address
    readAddress += RawObjectGraphicSubheader::dataSize;
    
    // Check for end of header
    endOfHeaderCheck = *(rom.directRead(readAddress));
  }
}

int RawObjectGraphicsHeader::size() {
  return rawObjectGraphicSubheaders_.size();
}

RawObjectGraphicSubheader& RawObjectGraphicsHeader::subheader(int index) {
  // Throw if index out of range
  if ((unsigned int)index >= rawObjectGraphicSubheaders_.size()) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "RawObjectGraphicsHeader::subheader(int)",
                                   index);
  }

  return rawObjectGraphicSubheaders_[index];
}

const RawObjectGraphicSubheader& RawObjectGraphicsHeader
    ::subheader(int index) const {
  // Throw if index out of range
  if ((unsigned int)index >= rawObjectGraphicSubheaders_.size()) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "RawObjectGraphicsHeader::subheader(int)"
                                   " const",
                                   index);
  }
  
  return rawObjectGraphicSubheaders_[index];
}


};
