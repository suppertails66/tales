#include "gamedata/StandardUncompressedGraphicHeader.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"

using namespace Luncheon;

namespace Tales {


StandardUncompressedGraphicHeader
    ::StandardUncompressedGraphicHeader()
  : graphicAddress_(0),
    numTiles_(0),
    vramWriteAddress_(0) { };

StandardUncompressedGraphicHeader
    ::StandardUncompressedGraphicHeader(const Tbyte* data)
  : graphicAddress_(0),
    numTiles_(0),
    vramWriteAddress_(0) {
  readFromData(data);
}

int StandardUncompressedGraphicHeader
    ::readFromData(const Tbyte* data) {
  int bankNum = ByteConversion::fromBytes(data + 0,
                                          ByteSizes::uint8Size,
                                          EndiannessTypes::little,
                                          SignednessTypes::nosign);
  
  // Ignore flip bit
  bankNum &= 0x7F;
                                          
  numTiles_ = ByteConversion::fromBytes(data + 1,
                                        ByteSizes::uint8Size,
                                        EndiannessTypes::little,
                                        SignednessTypes::nosign);
                                          
  vramWriteAddress_ = ByteConversion::fromBytes(data + 2,
                                        ByteSizes::uint16Size,
                                        EndiannessTypes::little,
                                        SignednessTypes::nosign);
                                          
  int bankedGraphicAddress = ByteConversion::fromBytes(data + 4,
                                        ByteSizes::uint16Size,
                                        EndiannessTypes::little,
                                        SignednessTypes::nosign);
  
  graphicAddress_ = LoadedROM::getDirectAddress(bankNum,
                                                bankedGraphicAddress);
                                                
  return dataSize;
}

Taddress StandardUncompressedGraphicHeader::graphicAddress() const {
  return graphicAddress_;
}

int StandardUncompressedGraphicHeader::numTiles() const {
  return numTiles_;
}

Taddress StandardUncompressedGraphicHeader::vramWriteAddress() const {
  return vramWriteAddress_;
}


};
