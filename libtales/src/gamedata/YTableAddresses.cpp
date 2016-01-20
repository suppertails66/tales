#include "gamedata/YTableAddresses.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"
#include <iostream>

namespace Tales {


YTableAddresses::YTableAddresses() { };

YTableAddresses::YTableAddresses(const RawLevelHeaders& headers) {
  // Iterate over headers
  int tableNum = 0;
  for (AddressRawLevelHeaderMap::const_iterator it = headers.cbegin();
       it != headers.cend();
       it++) {
    
    // Check if this map has been loaded
    AddressToWidthMap::iterator findIt
      = addressToWidth_.find(it->second.yTableAddress());
    
    // Don't load if map already loaded
    if (findIt != addressToWidth_.end()) {
      continue;
    }
    
    // Add new mapping
    widthToYTableMap_.insert(WidthToYTablePair(
          it->second.visualWidth(),
          it->second.yTableAddress()));
          
//    std::cout << widthToYTableMap_.findOrThrow(it->second.visualWidth())->second << std::endl;
    
    // Add address mapping
    addressToWidth_.insert(AddressToWidthPair(
                it->second.yTableAddress(),
                it->second.visualWidth()));
    
    ++tableNum;
  }
}

void YTableAddresses::save(std::string& data) {
  // Write buffer
  char buffer[ByteSizes::uint32Size];
  
  // Write number of address mappings
  ByteConversion::toBytes(widthToYTableMap_.size(),
                          buffer,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string(buffer, ByteSizes::uint32Size);
  
  // Write each address mapping
  for (WidthToYTableMap::iterator it = widthToYTableMap_.begin();
       it != widthToYTableMap_.end();
       it++) {
    // Write width
    ByteConversion::toBytes(it->first,
                            buffer,
                            ByteSizes::uint16Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    data += std::string(buffer, ByteSizes::uint16Size);
    
    // Write address
    ByteConversion::toBytes(it->second,
                            buffer,
                            ByteSizes::uint32Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    data += std::string(buffer, ByteSizes::uint32Size);
  }
  
}

int YTableAddresses::load(const Tbyte* data) {
  // Count of read bytes
  int byteCount = 0;
  
  // Clear existing data
  widthToYTableMap_.clear();
  
  // Read number of address mappings
  int numAddresses = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint32Size;
  
  // Read each address mapping
  for (int i = 0; i < numAddresses; i++) {
    // Read width
    int width = ByteConversion::fromBytes(
                            data + byteCount,
                            ByteSizes::uint16Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    byteCount += ByteSizes::uint16Size;
    
    // Read address
    int address = ByteConversion::fromBytes(
                            data + byteCount,
                            ByteSizes::uint32Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    byteCount += ByteSizes::uint32Size;
    
    // Add to map
    widthToYTableMap_.insert(WidthToYTablePair(width, address));
  }        
  
  return byteCount;
}

Taddress YTableAddresses::addressOfWidth(int width) const {
  // Get value
  return widthToYTableMap_.findOrThrow(width)->second;
}

int YTableAddresses::widthToYMapSize() {
  return widthToYTableMap_.size();
}

WidthToYTableMap::iterator YTableAddresses::widthToYMapBegin() {
  return widthToYTableMap_.begin();
}

WidthToYTableMap::iterator YTableAddresses::widthToYMapEnd() {
  return widthToYTableMap_.end();
}

WidthToYTableMap::const_iterator YTableAddresses::widthToYMapCbegin() {
  return widthToYTableMap_.cbegin();
}

WidthToYTableMap::const_iterator YTableAddresses::widthToYMapCend() {
  return widthToYTableMap_.cend();
}

int YTableAddresses::widthOfInitialAddress(
    Taddress initialAddress) const {
  return addressToWidth_.findOrThrow(initialAddress)->second;
}


};
