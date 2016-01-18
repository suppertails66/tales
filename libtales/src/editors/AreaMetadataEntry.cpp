#include "editors/AreaMetadataEntry.h"
#include "exception/InvalidLoadDataException.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"

using namespace Luncheon;

namespace Tales {


AreaMetadataEntry::AreaMetadataEntry()
  : hasVRAMIndices_(false),
    leafIndex_(0) { };

AreaMetadataEntry::AreaMetadataEntry(const std::string& name__)
  : name_(name__),
    hasVRAMIndices_(false),
    leafIndex_(0) { };

void AreaMetadataEntry::save(std::string& data) {
  SaveHelper saver(data,
                   DataChunkIDs::areaMetadataEntry,
                   0);
                   
  Tbyte buffer[ByteSizes::uint32Size];
  
  SaveHelper::saveString(data,
                         name_);
                         
  ByteConversion::toBytes((int)(hasVRAMIndices_),
                          buffer,
                          ByteSizes::uint8Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint8Size);
                         
  ByteConversion::toBytes((int)(leafIndex_),
                          buffer,
                          ByteSizes::uint8Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint8Size);
                   
  saver.finalize();
}

int AreaMetadataEntry::load(const Tbyte* data) {
  int byteCount = 0;

  LoadHelper loader(data,
                    byteCount);
                    
  if (loader.version() > 0) {
    throw InvalidLoadDataException(TALES_SRCANDLINE,
                                   "AreaMetadataEntry::load(const Tbyte*)");
  }
  
  byteCount += LoadHelper::loadString(data + byteCount,
                                      name_);
                         
  hasVRAMIndices_ = (bool)(ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint8Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign));
  byteCount += ByteSizes::uint8Size;
                         
  leafIndex_ = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint8Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint8Size;
                    
  return byteCount;
}

std::string AreaMetadataEntry::name() const {
  return name_;
}
  
bool AreaMetadataEntry::hasVRAMIndices() const {
  return hasVRAMIndices_;
}
  
int AreaMetadataEntry::leafIndex() const {
  return leafIndex_;
}

void AreaMetadataEntry::setName(const std::string& name__) {
  name_ = name__;
}
  
void AreaMetadataEntry::setLeafIndex(int leafIndex__) {
  leafIndex_ = leafIndex__;
}


}; 
