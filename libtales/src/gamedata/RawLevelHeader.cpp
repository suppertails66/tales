#include "gamedata/RawLevelHeader.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"

using namespace Luncheon;

namespace Tales {


RawLevelHeader::RawLevelHeader()
  : address_(0),
    metatileStructureAddress_(0),
    mapLayoutAddress_(0),
    visualWidth_(0),
    negativeRowLength_(0),
    loadableMetatileArea_(0),
    cameraLeftLimit_(0),
    cameraTopLimit_(0),
    cameraRightLimit_(0),
    cameraBottomLimit_(0),
    yTableAddress_(0) { };

RawLevelHeader::RawLevelHeader(LoadedROM& rom,
                    Taddress address__/*,
                    const EditableMapLayouts& mapLayouts*/)
  : address_(0),
    metatileStructureAddress_(0),
    mapLayoutAddress_(0),
    visualWidth_(0),
    negativeRowLength_(0),
    loadableMetatileArea_(0),
    cameraLeftLimit_(0),
    cameraTopLimit_(0),
    cameraRightLimit_(0),
    cameraBottomLimit_(0),
    yTableAddress_(0)
/*    cameraLeftLimit_(ByteConversion::fromBytes(
                        rom.directRead(address + 12),
                        ByteSizes::uint16Size,
                        EndiannessTypes::little,
                        SignednessTypes::nosign)),
    cameraTopLimit_(ByteConversion::fromBytes(
                        rom.directRead(address + 14),
                        ByteSizes::uint16Size,
                        EndiannessTypes::little,
                        SignednessTypes::nosign)),
    cameraRightLimit_(ByteConversion::fromBytes(
                        rom.directRead(address + 16),
                        ByteSizes::uint16Size,
                        EndiannessTypes::little,
                        SignednessTypes::nosign)),
    cameraBottomLimit_(ByteConversion::fromBytes(
                        rom.directRead(address + 18),
                        ByteSizes::uint16Size,
                        EndiannessTypes::little,
                        SignednessTypes::nosign))*/ {
  
  readFromData(rom,
               address__);
  
}
  
void RawLevelHeader::readFromData(LoadedROM& rom,
                                  Taddress address__) {

  address_ = address__;
  
  const Tbyte* data = rom.directRead(address__);

  int metatileStructureBank = ByteConversion::fromBytes(
                        data + 0,
                        ByteSizes::uint8Size,
                        EndiannessTypes::little,
                        SignednessTypes::nosign);
  int metatileStructureBankedAddress = ByteConversion::fromBytes(
                        data + 1,
                        ByteSizes::uint16Size,
                        EndiannessTypes::little,
                        SignednessTypes::nosign);
  
  // Convert banked address to direct
  metatileStructureAddress_ = (Taddress)(LoadedROM::getDirectAddress(
                              metatileStructureBank,
                              metatileStructureBankedAddress));
  
  // If the metatile structure address is invalid, "repair" it.
  // This is done because there's not enough space in the bank to add
  // a new structure set in-place at that address
  if (metatileStructureAddress_ == invalidTableAddress) {
    metatileStructureAddress_ = invalidTableRepairAddress;
  }
                        
  // Get map layout bank and address
  int mapLayoutBank = ByteConversion::fromBytes(
                        data + 3,
                        ByteSizes::uint8Size,
                        EndiannessTypes::little,
                        SignednessTypes::nosign);
  int mapLayoutBankedAddress = ByteConversion::fromBytes(
                        data + 4,
                        ByteSizes::uint16Size,
                        EndiannessTypes::little,
                        SignednessTypes::nosign);
  
  // Convert banked address to direct
  mapLayoutAddress_ = (Taddress)(LoadedROM::getDirectAddress(mapLayoutBank,
                              mapLayoutBankedAddress));
                              
  visualWidth_ = ByteConversion::fromBytes(
                        data + 6,
                        ByteSizes::uint16Size,
                        EndiannessTypes::little,
                        SignednessTypes::nosign);
                              
  negativeRowLength_ = ByteConversion::fromBytes(
                        data + 8,
                        ByteSizes::int16Size,
                        EndiannessTypes::little,
                        SignednessTypes::sign);
                              
  loadableMetatileArea_ = ByteConversion::fromBytes(
                        data + 10,
                        ByteSizes::uint16Size,
                        EndiannessTypes::little,
                        SignednessTypes::nosign);
                        
  cameraLeftLimit_ = ByteConversion::fromBytes(
                        data + 12,
                        ByteSizes::uint16Size,
                        EndiannessTypes::little,
                        SignednessTypes::nosign);
                        
  cameraTopLimit_ = ByteConversion::fromBytes(
                        data + 14,
                        ByteSizes::uint16Size,
                        EndiannessTypes::little,
                        SignednessTypes::nosign);
                        
  cameraRightLimit_ = ByteConversion::fromBytes(
                        data + 16,
                        ByteSizes::uint16Size,
                        EndiannessTypes::little,
                        SignednessTypes::nosign);
                        
  cameraBottomLimit_ = ByteConversion::fromBytes(
                        data + 18,
                        ByteSizes::uint16Size,
                        EndiannessTypes::little,
                        SignednessTypes::nosign);
                        
  // Y-lookup tables must appear in bank 0 or bank 1, so this is a
  // direct address
  yTableAddress_ = ByteConversion::fromBytes(
                        data + 20,
                        ByteSizes::uint16Size,
                        EndiannessTypes::little,
                        SignednessTypes::nosign);
}

/*int RawLevelHeader::writeToData(Tbyte* data) const {
  
  ByteConversion::toBytes(cameraLeftLimit_,
                          data + 12,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  
  ByteConversion::toBytes(cameraTopLimit_,
                          data + 14,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  
  ByteConversion::toBytes(cameraRightLimit_,
                          data + 16,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  
  ByteConversion::toBytes(cameraBottomLimit_,
                          data + 18,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);

  return dataSize;
} */

Taddress RawLevelHeader::address() {
  return address_;
}

Taddress RawLevelHeader::metatileStructureAddress() const {
  return metatileStructureAddress_;
}


Taddress RawLevelHeader::mapLayoutAddress() const {
  return mapLayoutAddress_;
}
  
  
int RawLevelHeader::visualWidth() const {
  return visualWidth_;
}

int RawLevelHeader::negativeRowLength() const {
  return negativeRowLength_;
}

int RawLevelHeader::loadableMetatileArea() const {
  return loadableMetatileArea_;
}


int RawLevelHeader::cameraLeftLimit() const {
  return cameraLeftLimit_;
}


int RawLevelHeader::cameraTopLimit() const {
  return cameraTopLimit_;
}


int RawLevelHeader::cameraRightLimit() const {
  return cameraRightLimit_;
}


int RawLevelHeader::cameraBottomLimit() const {
  return cameraBottomLimit_;
}
 
Taddress RawLevelHeader::yTableAddress() const {
  return yTableAddress_;
}

//void RawLevelHeader::setMetatileStructureAddress(
//    Taddress metatileStructureAddress__) {
//  metatileStructureAddress_ = metatileStructureAddress__;
//}
 

//void RawLevelHeader::setMapLayoutAddress(
//    Taddress mapLayoutAddress__) {
//  mapLayoutAddress_ = mapLayoutAddress__;
//}


};
