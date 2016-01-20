#include "gamedata/LevelGraphicsHeader.h"
#include "gamegear/LoadedROM.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"

using namespace Luncheon;

namespace Tales {


LevelGraphicsHeader::LevelGraphicsHeader()
  : /*romExportAddress_(0),*/
    vdpWriteAddress_(0),
    mapGraphicIndex_(0),
    objectGraphicsHeaderIndex_(0) { };

LevelGraphicsHeader::LevelGraphicsHeader(
                    /*Taddress romExportAddress__,*/
                    Taddress vdpWriteAddress__,
                    int mapGraphicIndex__,
                    int objectGraphicsHeaderIndex__)
  : /*romExportAddress_(romExportAddress__),*/
    vdpWriteAddress_(vdpWriteAddress__),
    mapGraphicIndex_(mapGraphicIndex__),
    objectGraphicsHeaderIndex_(objectGraphicsHeaderIndex__) { };
    
void LevelGraphicsHeader::save(std::string& data) {
  // Write buffer
  Tbyte buffer[ByteSizes::uint32Size];
  
  // Write VDP write address
  ByteConversion::toBytes(vdpWriteAddress_,
                          buffer,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint16Size);
  
  // Write map graphic index
  ByteConversion::toBytes(mapGraphicIndex_,
                          buffer,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint16Size);
  
  // Write object graphics header index
  ByteConversion::toBytes(objectGraphicsHeaderIndex_,
                          buffer,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint16Size);
}

int LevelGraphicsHeader::load(const Tbyte* data) {
  // Count of read bytes
  int byteCount = 0;

  // Read VDP write address
  vdpWriteAddress_ = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint16Size;

  // Read map graphic index
  mapGraphicIndex_ = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint16Size;

  // Read object graphics header index
  objectGraphicsHeaderIndex_ = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint16Size;
  
  // Return count of bytes read
  return byteCount;
}

int LevelGraphicsHeader::exportToData(
                 Tbyte* data,
                 Taddress mapGraphicAddress,
                 Taddress objectGraphicsHeaderAddress) {
  // Convert direct address to banked
  int bankNum = LoadedROM::directToBankNum(mapGraphicAddress);
  int bankedMapGraphicAddress
    = LoadedROM::directToBankedAddress(mapGraphicAddress);
  
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
  
  // Write banked map graphic address
  ByteConversion::toBytes(bankedMapGraphicAddress,
                          data + 3,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  
  // Write object graphics header address (should be unbanked via
  // slot1/slot2)
  ByteConversion::toBytes(objectGraphicsHeaderAddress,
                          data + 5,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  
  // Return number of bytes written
  return dataSize;
}

//Taddress LevelGraphicsHeader::romExportAddress() const {
//  return romExportAddress_;
//}

Taddress LevelGraphicsHeader::vdpWriteAddress() const {
  return vdpWriteAddress_;
}

int LevelGraphicsHeader::mapGraphicIndex() const {
  return mapGraphicIndex_;
}

int LevelGraphicsHeader::objectGraphicsHeaderIndex() const {
  return objectGraphicsHeaderIndex_;
}

//void LevelGraphicsHeader
//    ::setRomExportAddress(Taddress romExportAddress__) {
//  romExportAddress_ = romExportAddress__;
//}

void LevelGraphicsHeader
    ::setVdpWriteAddress(Taddress vdpWriteAddress__) {
  vdpWriteAddress_ = vdpWriteAddress__;
}

void LevelGraphicsHeader
    ::setMapGraphicIndex(int mapGraphicIndex__) {
  mapGraphicIndex_ = mapGraphicIndex__;
}

void LevelGraphicsHeader
    ::setObjectGraphicsHeaderIndex(int objectGraphicsHeaderIndex__) {
  objectGraphicsHeaderIndex_ = objectGraphicsHeaderIndex__;
}


};
