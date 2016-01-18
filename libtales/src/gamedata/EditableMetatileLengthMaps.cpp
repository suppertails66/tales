#include "gamedata/EditableMetatileLengthMaps.h"
#include "exception/OutOfRangeIndexException.h"
#include "exception/UnrecognizedVersionException.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"
#include "util/StringConversion.h"
#include <iostream>

using namespace Luncheon;

namespace Tales {


EditableMetatileLengthMaps::EditableMetatileLengthMaps() { };

EditableMetatileLengthMaps::EditableMetatileLengthMaps(
                        LoadedROM& rom,
                        Taddress baseAddress,
                        int numMaps) {
  // Load each map
  for (int i = 0; i < numMaps; i++) {
    Taddress address = baseAddress
                        + (i * MetatileLengthMap::dataSize);
    
    // Read the map from the raw data
    MetatileLengthMap newLengthMap(rom.directRead(address));
    
    // Add map to loaded map collection
    primaryStorage_.push_back(newLengthMap);
    
    // Add index to address mapping
    indexToAddress_.insert(
      LengthIndexToAddressPair(i, address));
  }
}

int EditableMetatileLengthMaps::size() {
  return primaryStorage_.size();
}

MetatileLengthMap& EditableMetatileLengthMaps::mapAt(int index) {
  // Throw if index out of range
  if ((unsigned int)index >= primaryStorage_.size()) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "EditableMetatileLengthMaps::mapAt("
                                   "int)",
                                   index);
  }

  return primaryStorage_[index];
}

void EditableMetatileLengthMaps::saveInternal(std::string& data) {
  // Output buffer
  Tbyte buffer[ByteSizes::uint32Size];
  
  // Save number of maps
  ByteConversion::toBytes(primaryStorage_.size(),
                          buffer,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint16Size);

  // Save each map
  for (MetatileLengthMapCollection::iterator it = primaryStorage_.begin();
       it != primaryStorage_.end();
       it++) {
    it->save(data);
  }
  
  // Save address mappings
  for (LengthIndexToAddressMap::iterator it = indexToAddress_.begin();
       it != indexToAddress_.end();
       it++) {
    ByteConversion::toBytes(it->second,
                            buffer,
                            ByteSizes::uint32Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    data += std::string((char*)buffer, ByteSizes::uint32Size);
  }
}

int EditableMetatileLengthMaps::loadInternal(const Tbyte* data,
                                             int& byteCount) {
  // Clear existing data
  primaryStorage_.clear();
  indexToAddress_.clear();
  
  // Get number of maps
  int numMaps = ByteConversion::fromBytes(
                      data + byteCount,
                      ByteSizes::uint16Size,
                      EndiannessTypes::little,
                      SignednessTypes::nosign);
  byteCount += ByteSizes::uint16Size;
  
  // Get maps
  for (int i = 0; i < numMaps; i++) {
    // Read map
    MetatileLengthMap newLengthMap(data + byteCount);
    byteCount += MetatileLengthMap::dataSize;
    
    // Add to storage
    primaryStorage_.push_back(newLengthMap);
  }
  
  // Read addresses
  for (int i = 0; i < numMaps; i++) {
    // Get address
    Taddress address = ByteConversion::fromBytes(
                        data + byteCount,
                        ByteSizes::uint32Size,
                        EndiannessTypes::little,
                        SignednessTypes::nosign);
    byteCount += ByteSizes::uint32Size;
    
    // Add to index mapping
    indexToAddress_.insert(
        LengthIndexToAddressPair(
            i, address));
  }
  
  // Return number of bytes read
  return byteCount;
}

void EditableMetatileLengthMaps::exportToROM(WritableROM& rom) {
  // Write each map to corresponding address
  for (MetatileLengthMapCollection::size_type
         i = 0; i < primaryStorage_.size(); i++) {
    // Get target address
    Taddress address = indexToAddress_.findValueOrThrow(i);
    
    // Write map to data
    Tbyte buffer[MetatileLengthMap::dataSize];
    primaryStorage_[i].writeToData(buffer);
    
    // Write data to ROM
    rom.directWrite(address,
                    buffer,
                    MetatileLengthMap::dataSize);
  }
}


}; 
