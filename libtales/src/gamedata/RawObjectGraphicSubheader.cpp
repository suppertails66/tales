#include "gamedata/RawObjectGraphicSubheader.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"

using namespace Luncheon;

namespace Tales {


RawObjectGraphicSubheader::RawObjectGraphicSubheader()
  : vdpWriteAddress_(0),
    objectGraphicAddress_(0),
    substitutionEnabled_(false) { };

RawObjectGraphicSubheader::RawObjectGraphicSubheader(
                       LoadedROM& rom,
                       Taddress address)
  : vdpWriteAddress_(0),
    objectGraphicAddress_(0),
    substitutionEnabled_(false) {
  // Get settings byte
  Tbyte settingsByte = *(rom.directRead(address + 0));
  
  // Get substitution setting
  if (settingsByte & substitutionMask) {
    substitutionEnabled_ = true;
  }
  
  // Get bank number of object graphic banked address
  int bankNum = (int)(settingsByte & bankNumMask);
  
  // Get VDP write address (direct)
  vdpWriteAddress_ = ByteConversion::fromBytes(
                              rom.directRead(address + 1),
                              ByteSizes::uint16Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign);
                              
  // Get object graphic address (banked)
  int bankedObjectGraphicAddress = ByteConversion::fromBytes(
                              rom.directRead(address + 3),
                              ByteSizes::uint16Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign);
  
  // Convert banked object graphic address to unbanked
  objectGraphicAddress_ = LoadedROM::getDirectAddress(
                                      bankNum,
                                      bankedObjectGraphicAddress);
}

Taddress RawObjectGraphicSubheader::vdpWriteAddress() const {
  return vdpWriteAddress_;
}

Taddress RawObjectGraphicSubheader::objectGraphicAddress() const {
  return objectGraphicAddress_;
}

bool RawObjectGraphicSubheader::substitutionEnabled() const {
  return substitutionEnabled_;
}


}
