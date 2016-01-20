#include "gamedata/LevelObjectEntryGroup.h"
#include "exception/TalesException.h"
#include "exception/TGenericException.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"
#include <exception>
#include <iostream>

using namespace Luncheon;

namespace Tales {


LevelObjectEntryGroup::LevelObjectEntryGroup() { };

LevelObjectEntryGroup::LevelObjectEntryGroup(const Tbyte* data) {
  readFromData(data);
}

void LevelObjectEntryGroup::save(std::string& data) {
  // Allocate memory to hold data
  Tbyte* entryBuffer = new Tbyte[rawSize()];
  
  // Handle exceptions so we can clean up allocated memory if need be
  try {
    
    int byteCount = writeToData(entryBuffer);
    data += std::string((char*)entryBuffer, byteCount);
    
  }
  catch (std::exception& e) {
    // Clean up allocated memory
    delete[] entryBuffer;
    
    // Re-throw exception
    throw e;
  }
  
  // Clean up allocated memory
  delete[] entryBuffer;
}

int LevelObjectEntryGroup::load(const Tbyte* data) {
  return readFromData(data);
}

int LevelObjectEntryGroup::writeToData(Tbyte* data) {
  // Count of bytes written
  int byteCount = 0;
  
  // Write number of entries
/*  ByteConversion::toBytes(entries_.size(),
                          data + byteCount,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint32Size; */
  
  // Write each entry
//  int count = 0;
  for (LevelObjectEntryCollection::iterator it = entries_.begin();
       it != entries_.end();
       ++it) {
    byteCount += it->writeToData(data + byteCount);
//    ++count;
  }
//  std::cout << "count: " << count << std::endl;
  
  // Write terminator
  ByteConversion::toBytes(terminatorToken,
                          data + byteCount,
                          ByteSizes::uint8Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint8Size;
  
  // Return count of bytes written
  return byteCount;
}

int LevelObjectEntryGroup::readFromData(const Tbyte* data) {
  // Destroy existing data
  entries_.clear();

  // Count of bytes read
  int byteCount = 0;
  
  // Read number of entries
/*  int numEntries = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint32Size; */
  
  // Read entries until terminator reached
  Tbyte endCheck = data[byteCount];
  while (endCheck != terminatorToken) {
//    std::cout << "here" << std::endl;
    // Read entry
    LevelObjectEntry entry;
    byteCount += entry.readFromData(data + byteCount);
    
    // Add entry to storage
    entries_.push_back(entry);
    
    // Check for terminator
    endCheck = data[byteCount];
  }
  
  // Skip terminator
  ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint8Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint8Size;
  
  // Return count of bytes read
  return byteCount;
}

void LevelObjectEntryGroup::addEntry(const LevelObjectEntry& entry) {
  // Throw if list is full
  if (entries_.size() == maxGroupSize) {
    throw TGenericException(TALES_SRCANDLINE,
                           "LevelObjectEntryGroup::addEntry("
                           "const LevelObjectEntry&)",
                           "Max object limit reached");
  }

  // Add entry to storage
  entries_.push_back(entry);
}

void LevelObjectEntryGroup::eraseEntry(
    LevelObjectEntryCollection::iterator entryIt) {
  entries_.erase(entryIt);
}

int LevelObjectEntryGroup::size() const {
  return entries_.size();
}

LevelObjectEntryCollection::iterator LevelObjectEntryGroup::begin() {
  return entries_.begin();
}

LevelObjectEntryCollection::iterator LevelObjectEntryGroup::end() {
  return entries_.end();
}

LevelObjectEntryCollection::const_iterator
    LevelObjectEntryGroup::cbegin() const {
  return entries_.cbegin();
}

LevelObjectEntryCollection::const_iterator
    LevelObjectEntryGroup::cend() const {
  return entries_.cend();
}

int LevelObjectEntryGroup::rawSize() {
  // List size: size of all entries plus 1-byte terminator
  return (LevelObjectEntry::dataSize * entries_.size()) + 1;
}


};
