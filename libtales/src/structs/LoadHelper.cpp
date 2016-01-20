#include "structs/LoadHelper.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"
#include <iostream>

using namespace Luncheon;

namespace Tales {


LoadHelper::LoadHelper(const Tbyte* data)
  : id_(DataChunkIDs::null),
    version_(0),
    size_(0) {
  readHeader(data);
}


LoadHelper::LoadHelper(const Tbyte* data,
             int& byteCount)
  : id_(DataChunkIDs::null),
    version_(0),
    size_(0) {
  readHeader(data,
             byteCount);
}
             
DataChunkIDs::DataChunkID LoadHelper::id() const {
  return id_;
}

int LoadHelper::version() const {
  return version_;
}

int LoadHelper::size() const {
  return size_;
}
  
void LoadHelper::readHeader(const Tbyte* data) {
  id_ = static_cast<DataChunkIDs::DataChunkID>(
          ByteConversion::fromBytes(data + 0,
                                    ByteSizes::uint16Size,
                                    EndiannessTypes::little,
                                    SignednessTypes::nosign));
                                    
  version_ = ByteConversion::fromBytes(data + 2,
                                    ByteSizes::uint16Size,
                                    EndiannessTypes::little,
                                    SignednessTypes::nosign);
                                    
  size_ = ByteConversion::fromBytes(data + 4,
                                    ByteSizes::uint32Size,
                                    EndiannessTypes::little,
                                    SignednessTypes::nosign);
}
  
void LoadHelper::readHeader(const Tbyte* data,
                            int& byteCount) {
  readHeader(data);
  
  byteCount += 8;
}

int LoadHelper::loadString(
                       const Tbyte* data,
                       std::string& dst) {
  int byteCount = 0;
     
  int length = ByteConversion::fromBytes(data + byteCount,
                                    ByteSizes::uint32Size,
                                    EndiannessTypes::little,
                                    SignednessTypes::nosign);
  byteCount += ByteSizes::uint32Size;
                     
  dst = std::string((char*)(data + byteCount), length);
  byteCount += length;
  
  return byteCount;
}


};
