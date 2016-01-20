#include "gamedata/MapLayout.h"
#include "gamedata/TailsAdvRLECompressor.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"
#include "util/StringConversion.h"
#include "exception/NotEnoughSpaceException.h"
#include "exception/OutOfRangeIndexException.h"
#include <cstring>
#include <iostream>

using namespace Luncheon;

namespace Tales {


MapLayout::MapLayout()
  : address_(0),
    compressedSize_(0) {
  // Initialize map layout
  std::memset(layout_, 0, actualStorageSize);
}
  
MapLayout::MapLayout(LoadedROM& rom,
                  Taddress address__)
  : address_(0),
    compressedSize_(0) {
  // Initialize map layout
  std::memset(layout_, 0, actualStorageSize);
  
  // Read map layout
  readFromData(rom, address__);
}

void MapLayout::readFromData(LoadedROM& rom,
                  Taddress address__) {
  // Remember read address
  address_ = address__;
  
  // Decompress map data
  compressedSize_ = TailsAdvRLECompressor::decompress(layout_,
                                    rom.directRead(address__),
                                    actualStorageSize);
}

void MapLayout::save(std::string& data) {
  // Output buffer
  char buffer[ByteSizes::uint32Size];
  
  // Write address
  ByteConversion::toBytes(address_,
                          buffer,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string(buffer, ByteSizes::uint32Size);
  
  // Write compressed size
  ByteConversion::toBytes(compressedSize_,
                          buffer,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string(buffer, ByteSizes::uint32Size);

  // Write map length
  ByteConversion::toBytes(actualStorageSize,
                          buffer,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string(buffer, ByteSizes::uint32Size);
  
  // Write map
  data += std::string((char*)layout_, actualStorageSize);
}

int MapLayout::load(const Tbyte* data) {
  // Count of read bytes
  int byteCount = 0;
  
  // Read address
  address_ = ByteConversion::fromBytes(data + byteCount,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint32Size;
  
  // Read compressed size
  compressedSize_ = ByteConversion::fromBytes(data + byteCount,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint32Size;
  
  // Skip map length
  ByteConversion::fromBytes(data + byteCount,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint32Size;
  
  // Read map
  std::memcpy(layout_, data + byteCount, actualStorageSize);
  byteCount += actualStorageSize;
  
  return byteCount;
}

void MapLayout::exportToFreeROM(WritableROM& rom) {
  // Buffer to hold compressed map
  Tbyte* outputBuffer = new Tbyte[TailsAdvRLECompressor
      ::safeCompressionSize(actualStorageSize)];
      
  try {

  // Compress map
  int newCompressedSize = 
    TailsAdvRLECompressor::compress(outputBuffer,
                                  layout_,
                                  dataSize);
                                  
//  std::cout << "old size: " << compressedSize_
//    << " new size: " << newCompressedSize << std::endl;

  
  // Copy to last known address if size is equal or smaller
/*  if (newCompressedSize <= compressedSize_) {
    rom.directWrite(address_,
                    outputBuffer,
                    newCompressedSize);
//    std::cout << "new map smaller" << std::endl;
  }
  // Otherwise, look for free space
  else { */
//    std::cout << "new map bigger" << std::endl;
//    std::cout << "Original: " << compressedSize_ << std::endl;
//    std::cout << "New: " << newCompressedSize << std::endl;
      
    // Search for free space of the size we need
    FreeSpaceList::iterator spaceIt
      = rom.freeSpace().getFreeSpace(newCompressedSize);
      
//    std::cout << "Got free space: address "
//      << spaceIt->address() << ", length " << spaceIt->length()
//      << std::endl;
      
    // If no space is available, throw
    if (spaceIt == rom.freeSpace().freeSpaceList().end()) {
      throw NotEnoughSpaceException(TALES_SRCANDLINE,
                                    "MapLayout::exportToFreeROM("
                                    "WritableROM&)",
                                    newCompressedSize);
    }
    
    int newAddress = spaceIt->address();
    
    // Claim new space
    rom.freeSpace().claimSpace(spaceIt,
                               newCompressedSize);
    
    // Add original space to free space list
//    rom.freeSpace().giveSpace(address_,
//                              compressedSize_);
    
    // Update address
    address_ = newAddress;
    
    // Write to ROM
    rom.directWrite(address_,
                    outputBuffer,
                    newCompressedSize);
    
    // Update compressed size
    compressedSize_ = newCompressedSize;
//  }
      
  }
  // If an exception is thrown, ensure we delete the output buffer
  catch (std::exception& e) {
    delete outputBuffer;
    // Re-throw exception
    throw e;
  }
  
  // Delete allocated buffer
  delete outputBuffer;
}

Tbyte MapLayout::getMetatile(int index) const {
  if ((unsigned int)index >= actualStorageSize) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                  "MapLayout::getMetatile("
                                  "int)",
                                  index);
  }
                                      
  return layout_[index];
}

void MapLayout::setMetatile(int index, Tbyte value) {
  if ((unsigned int)index >= actualStorageSize) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                  "MapLayout::getMetatile("
                                  "int)",
                                  index);
  }
  
  layout_[index] = value;
}

Tbyte& MapLayout::operator[](int index) {
  if ((unsigned int)index >= actualStorageSize) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                  "MapLayout::getMetatile("
                                  "int)",
                                  index);
  }
  
  return layout_[index];
}

const Tbyte& MapLayout::operator[](int index) const {
  if ((unsigned int)index >= actualStorageSize) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                  "MapLayout::getMetatile("
                                  "int)",
                                  index);
  }
  
  return layout_[index];
}

Taddress MapLayout::address() const {
  return address_;
}

Taddress MapLayout::compressedSize() const {
  return compressedSize_;
}


}
