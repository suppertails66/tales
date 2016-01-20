#include "gamedata/ObjectGraphicsHeader.h"
#include "exception/OutOfRangeIndexException.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"
#include <iostream>

using namespace Luncheon;

namespace Tales {


ObjectGraphicsHeader::ObjectGraphicsHeader() { };

void ObjectGraphicsHeader::save(std::string& data) {
  // Write buffer
  Tbyte buffer[ByteSizes::uint32Size];
  
  // Write number of subheaders
  ByteConversion::toBytes(objectGraphicSubheaders_.size(),
                          buffer,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint32Size);
  
  // Write each subheader
  for (ObjectGraphicSubheaderCollection::iterator it
          = objectGraphicSubheaders_.begin();
       it != objectGraphicSubheaders_.end();
       ++it) {
    it->save(data);
  }
  
}

int ObjectGraphicsHeader::load(const Tbyte* data) {
  // Clear existing data
  objectGraphicSubheaders_.clear();
  
  // Count of read bytes
  int byteCount = 0;
  
  // Read number of subheaders
  int numEntries = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint32Size;
  
  // Read each subheader
  for (int i = 0; i < numEntries; i++) {
    ObjectGraphicSubheader subheader;
    
    byteCount += subheader.load(data + byteCount);
    
    objectGraphicSubheaders_.push_back(subheader);
  }
  
  // Return count of bytes read
  return byteCount;
}

int ObjectGraphicsHeader::exportToData(
                 Tbyte* data,
                 const IndexToAddressMap& objectIndexToAddress) {
  // Export each subheader
  int putpos = 0;
  for (ObjectGraphicSubheaderCollection::iterator it
          = objectGraphicSubheaders_.begin();
       it != objectGraphicSubheaders_.end();
       ++it) {
    // Get address of subheader's graphic
    Taddress subheaderGraphicAddress
      = objectIndexToAddress.findValueOrThrow(
          it->objectGraphicIndex());
    
    // Export subheader to address
    putpos += it->exportToData(data + putpos,
                               subheaderGraphicAddress);
  }
  
  // Write end of header token
  data[putpos] = endOfHeaderToken;
  ++putpos;
  
  return putpos;
}

int ObjectGraphicsHeader::size() const {
  return objectGraphicSubheaders_.size();
}

int ObjectGraphicsHeader::rawSize() const {
  int total = 0;
  
  // Add total size of all subheaders
  total += (objectGraphicSubheaders_.size()
              * ObjectGraphicSubheader::dataSize);
              
  // Add size of terminator
  total += ByteSizes::uint8Size;
  
  return total;
}

void ObjectGraphicsHeader::push_back(
    const ObjectGraphicSubheader& subheader) {
  objectGraphicSubheaders_.push_back(subheader);
}

void ObjectGraphicsHeader::insert(
            int index,
            const ObjectGraphicSubheader& subheader) {
  objectGraphicSubheaders_.insert(objectGraphicSubheaders_.begin() + index,
                                  subheader);
}

void ObjectGraphicsHeader::erase(
    int index) {
  objectGraphicSubheaders_.erase(objectGraphicSubheaders_.begin() + index);
}

ObjectGraphicSubheader& ObjectGraphicsHeader::subheader(int index) {
  // Throw if index out of range
  if ((unsigned int)index >= objectGraphicSubheaders_.size()) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "ObjectGraphicsHeader::subheader(int)",
                                   index);
  }
  
  return objectGraphicSubheaders_[index];
}

const ObjectGraphicSubheader& ObjectGraphicsHeader
    ::subheader(int index) const {
  // Throw if index out of range
  if ((unsigned int)index >= objectGraphicSubheaders_.size()) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "ObjectGraphicsHeader::subheader(int)"
                                   " const",
                                   index);
  }
  
  return objectGraphicSubheaders_[index];
}


};
