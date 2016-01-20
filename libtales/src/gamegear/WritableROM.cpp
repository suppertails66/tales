#include "gamegear/WritableROM.h"
#include "exception/TGenericException.h"
#include "util/StringConversion.h"
#include <string>
#include <cstring>
#include <fstream>
#include <iostream>

using namespace Luncheon;

namespace Tales {


WritableROM::WritableROM(
              const LoadedROM& rom__,
              const FreeSpaceListing& freeSpace__)
  : rom_(new Tbyte[rom__.loadedFileSize()]),
    romSize_(rom__.loadedFileSize()),
    freeSpace_(freeSpace__) {
  // Copy contents of ROM
  std::memcpy((char*)rom_,
              (char*)(rom__.directRead(0)),
              rom__.loadedFileSize());
}

WritableROM::WritableROM(const WritableROM& writableROM)
  : rom_(new Tbyte[writableROM.romSize_]),
    romSize_(writableROM.romSize_),
    freeSpace_(writableROM.freeSpace_) {
  // Copy contents of ROM
  std::memcpy((char*)rom_,
              ((char*)writableROM.rom_),
              writableROM.romSize_);
}

WritableROM& WritableROM::operator=(const WritableROM& writableROM) {
  // Delete ROM data
  delete rom_;
  
  // Copy members
  romSize_ = writableROM.romSize_;
  freeSpace_ = writableROM.freeSpace_;
  
  // Copy contents of ROM
  std::memcpy((char*)rom_,
              ((char*)writableROM.rom_),
              writableROM.romSize_);
              
  // Return self-reference
  return *this;
}

WritableROM::~WritableROM() {
  delete rom_;
}

Tbyte* WritableROM::directWrite(int address) {
  return rom_ + address;
}

void WritableROM::directWrite(
                 int address,
                 const Tbyte* src,
                 int srclen) {
  std::memcpy((char*)(rom_ + address), (char*)src, srclen);
  
//  if ((address <= 16894) && (address + srclen >= 16894)) {
//    std::cerr << "why" << std::endl;
//    std::cerr << '\t' << address << std::endl;
//    std::cerr << '\t' << srclen << std::endl;
    
//    for (int i = 0; i < 8; i++) {
//      std::cerr << (int)(*(rom_ + address + i)) << " ";
//    }
//    std::cerr << std::endl;
//  }
}
                   
const Tbyte* WritableROM::directRead(int address) const {
  return (rom_ + address);
}

void WritableROM::writeToFile(const std::string& filename) const {
  // Open the output file, clearing any existing contents
  std::ofstream ofs(filename,
                    std::ios_base::binary
                      | std::ios_base::trunc);
  
  // Write all data
  ofs.write((char*)rom_, romSize_);
}

void WritableROM::expandROM(unsigned int newSize) {
  // Throw if new size is smaller than existing
  if (newSize < romSize_) {
    throw TGenericException(TALES_SRCANDLINE,
                           "WritableROM::expandROM(unsigned int)",
                           std::string("Tried to expand ROM to a smaller"
                            "size: ")
                           + StringConversion::toString(romSize_)
                           + " bytes to "
                           + StringConversion::toString(newSize)
                           + " bytes");
  }

  // Create array for newly-sized data
  Tbyte* newrom = new Tbyte[newSize];
  
  // Fill any unused part of new ROM with 0xFF
  if (newSize > romSize_) {
    std::memset(newrom + romSize_,
                0xFF,
                newSize - romSize_);
  }
  
  // Copy as much of existing ROM data as new size allows
  std::memcpy(newrom,
              rom_,
              (romSize_ < newSize) ? romSize_ : newSize);
              
  // Delete existing ROM data
  delete rom_;
  
  // Add free space as needed
  // Free space must fall within bank boundaries
  for (int i = romSize_; i < newSize; i += LoadedROM::bankSize) {
    freeSpace_.giveSpace(i, LoadedROM::bankSize);
  }
  
  // Replace existing data with new
  rom_ = newrom;
  romSize_ = newSize;
}

void WritableROM::doubleROMSize() {
  expandROM(romSize_ * 2);
}

int WritableROM::romSize() const {
  return romSize_;
}

FreeSpaceListing& WritableROM::freeSpace() {
  return freeSpace_;
}

const FreeSpaceListing& WritableROM::freeSpace() const {
  return freeSpace_;
}


}; 
