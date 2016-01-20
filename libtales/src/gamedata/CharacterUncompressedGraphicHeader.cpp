#include "gamedata/CharacterUncompressedGraphicHeader.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"

using namespace Luncheon;

namespace Tales {


CharacterUncompressedGraphicHeader
    ::CharacterUncompressedGraphicHeader()
  : graphicAddress_(0),
    numTiles_(0) { };

CharacterUncompressedGraphicHeader
    ::CharacterUncompressedGraphicHeader(const Tbyte* data)
  : graphicAddress_(0),
    numTiles_(0) {
  readFromData(data);
}

int CharacterUncompressedGraphicHeader::readFromData(const Tbyte* data) {
  int bankNum = ByteConversion::fromBytes(data + 0,
                                          ByteSizes::uint8Size,
                                          EndiannessTypes::little,
                                          SignednessTypes::nosign);
  
  // Ignore flip bit
//  bankNum &= 0x7F;
                                          
  int bankedGraphicAddress = ByteConversion::fromBytes(data + 1,
                                        ByteSizes::uint16Size,
                                        EndiannessTypes::little,
                                        SignednessTypes::nosign);
  
  graphicAddress_ = LoadedROM::getDirectAddress(bankNum,
                                                bankedGraphicAddress);
                                          
  numTiles_ = ByteConversion::fromBytes(data + 3,
                                        ByteSizes::uint8Size,
                                        EndiannessTypes::little,
                                        SignednessTypes::nosign);
                                 
  // The nominal tilesize is half of the actual size (due to use of VDP sprite
  // doubling mode)
  numTiles_ *= 2;
                                                
  return dataSize;
}

Taddress CharacterUncompressedGraphicHeader::graphicAddress() const {
  return graphicAddress_;
}

int CharacterUncompressedGraphicHeader::numTiles() const {
  return numTiles_;
}


}
