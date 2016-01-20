#include "gamedata/ObjectGraphicSubheader.h"
#include "gamegear/LoadedROM.h"
#include "gamegear/GGTile.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"

using namespace Luncheon;

namespace Tales {


ObjectGraphicSubheader::ObjectGraphicSubheader()
  : /*romExportAddress_(0),*/
    vdpWriteAddress_(0),
    objectGraphicIndex_(0),
    substitutionOption_(SubstitutionOption::substitutionDisabled) { };

ObjectGraphicSubheader::ObjectGraphicSubheader(
                       /*Taddress romExportAddress__,*/
                       Taddress vdpWriteAddress__,
                       int objectGraphicIndex__,
                       SubstitutionOption substitutionOption__)
  : /*romExportAddress_(romExportAddress__),*/
    vdpWriteAddress_(vdpWriteAddress__),
    objectGraphicIndex_(objectGraphicIndex__),
    substitutionOption_(substitutionOption__) { };
    
void ObjectGraphicSubheader::save(std::string& data) {
  // Write buffer
  Tbyte buffer[ByteSizes::uint32Size];
  
  // Write VDP write address
  ByteConversion::toBytes(vdpWriteAddress_,
                          buffer,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint16Size);
  
  // Write object graphic index
  ByteConversion::toBytes(objectGraphicIndex_,
                          buffer,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint16Size);
  
  // Write substitution option
  ByteConversion::toBytes(static_cast<int>(substitutionOption_),
                          buffer,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint16Size);
  
}

int ObjectGraphicSubheader::load(const Tbyte* data) {
  // Count of read bytes
  int byteCount = 0;

  // Read VDP write address
  vdpWriteAddress_ = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint16Size;
  
  // Read object graphic index
  objectGraphicIndex_ = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint16Size;
  
  // Read substitution option
  substitutionOption_ = static_cast<SubstitutionOption>(
                            ByteConversion::fromBytes(
                                      data + byteCount,
                                      ByteSizes::uint16Size,
                                      EndiannessTypes::little,
                                      SignednessTypes::nosign));
  byteCount += ByteSizes::uint16Size;
  
  // Return count of bytes read
  return byteCount;
}

int ObjectGraphicSubheader::exportToData(
                  Tbyte* data,
                  Taddress objectGraphicAddress) {
  // Convert direct address to banked
  int bankNum = LoadedROM::directToBankNum(objectGraphicAddress);
  int bankedObjectGraphicAddress
    = LoadedROM::directToBankedAddress(objectGraphicAddress);
    
  // If substitution enabled, mask bankNum
  if (substitutionOption_ == substitutionEnabled) {
    bankNum |= substitutionMask;
  }
  
  // Write bank number
  ByteConversion::toBytes(bankNum,
                          data + 0,
                          ByteSizes::uint8Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  
  // Write VDP write address
  ByteConversion::toBytes(vdpWriteAddress_,
                          data + 1,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  
  // Write banked object graphic address
  ByteConversion::toBytes(bankedObjectGraphicAddress,
                          data + 3,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  
  // Return number of bytes written
  return dataSize;
}

//Taddress ObjectGraphicSubheader::romExportAddress() {
//  return romExportAddress_;
//}

Taddress ObjectGraphicSubheader::vdpWriteAddress() const {
  return vdpWriteAddress_;
}

int ObjectGraphicSubheader::objectGraphicIndex() const {
  return objectGraphicIndex_;
}

ObjectGraphicSubheader::SubstitutionOption ObjectGraphicSubheader
    ::substitutionOption() const {
  return substitutionOption_;
}

int ObjectGraphicSubheader
    ::tileWriteIndex() const {
  return (vdpWriteAddress_ / GGTile::rawInputDataSize);
}

void ObjectGraphicSubheader
    ::setTileWriteIndex(int tileWriteIndex) {
  vdpWriteAddress_ = tileWriteIndex * GGTile::rawInputDataSize;
}

//void ObjectGraphicSubheader::setRomExportAddress(
//    Taddress romExportAddress__) {
//  romExportAddress_ = romExportAddress__;
//}

void ObjectGraphicSubheader::setVdpWriteAddress(Taddress vdpWriteAddress__) {
  vdpWriteAddress_ = vdpWriteAddress__;
}

void ObjectGraphicSubheader::setObjectGraphicIndex(int objectGraphicIndex__) {
  objectGraphicIndex_ = objectGraphicIndex__;
}

void ObjectGraphicSubheader::setSubstitutionOption(
    SubstitutionOption substitutionOption__) {
  substitutionOption_ = substitutionOption__;
}


}
