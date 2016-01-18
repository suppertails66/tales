#include "gamedata/RawLevelGraphicsHeader.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"

using namespace Luncheon;

namespace Tales {


RawLevelGraphicsHeader::RawLevelGraphicsHeader()
  : vdpWriteAddress_(0),
    mapGraphicAddress_(0),
    objectGraphicsHeaderAddress_(0) { };

RawLevelGraphicsHeader::RawLevelGraphicsHeader(
                       LoadedROM& rom,
                       Taddress address)
  : vdpWriteAddress_(0),
    mapGraphicAddress_(0),
    objectGraphicsHeaderAddress_(0) {
  
  // Get bank number of map graphic banked address
  int bankNum = ByteConversion::fromBytes(
                              rom.directRead(address + 0),
                              ByteSizes::uint8Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign);
  
  // Get VDP write address (direct)
  vdpWriteAddress_ = ByteConversion::fromBytes(
                              rom.directRead(address + 1),
                              ByteSizes::uint16Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign);
                              
  // Get map graphic address (banked)
  int bankedMapGraphicAddress = ByteConversion::fromBytes(
                              rom.directRead(address + 3),
                              ByteSizes::uint16Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign);
  
  // Get object graphics header table address (direct -- must be 0x0-0x7FFF)
  objectGraphicsHeaderAddress_ = ByteConversion::fromBytes(
                              rom.directRead(address + 5),
                              ByteSizes::uint16Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign);
  
  // Convert banked map graphic address to unbanked
  mapGraphicAddress_ = LoadedROM::getDirectAddress(
                                      bankNum,
                                      bankedMapGraphicAddress);
  
}

Taddress RawLevelGraphicsHeader::vdpWriteAddress() const {
  return vdpWriteAddress_;
}

Taddress RawLevelGraphicsHeader::mapGraphicAddress() const {
  return mapGraphicAddress_;
}

Taddress RawLevelGraphicsHeader::objectGraphicsHeaderAddress() const {
  return objectGraphicsHeaderAddress_;
}


};
