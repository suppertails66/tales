#include "structs/GraphicDependencyGroupEntry.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"

using namespace Luncheon;

namespace Tales {


GraphicDependencyGroupEntry::GraphicDependencyGroupEntry()
  : graphicAddress_(0) { };

GraphicDependencyGroupEntry::GraphicDependencyGroupEntry(
        Taddress graphicAddress__)
  : graphicAddress_(graphicAddress__) { };

Taddress GraphicDependencyGroupEntry::graphicAddress() {
  return graphicAddress_;
}

void GraphicDependencyGroupEntry
    ::setGraphicAddress(Taddress graphicAddress__) {
  graphicAddress_ = graphicAddress__;
}

GraphicPointerAddressCollection& GraphicDependencyGroupEntry
    ::pointerAddresses() {
  return pointerAddresses_;
}
  
void GraphicDependencyGroupEntry::save(std::string& data) {
  Tbyte buffer[ByteSizes::uint32Size];
  
  ByteConversion::toBytes(graphicAddress_,
                          buffer,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint32Size);
  
  ByteConversion::toBytes(pointerAddresses_.size(),
                          buffer,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint32Size);
  
  for (int i = 0; i < pointerAddresses_.size(); i++) {
    ByteConversion::toBytes(pointerAddresses_[i],
                            buffer,
                            ByteSizes::uint32Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    data += std::string((char*)buffer, ByteSizes::uint32Size);
  }
}

int GraphicDependencyGroupEntry::load(const Tbyte* data) {
  pointerAddresses_.clear();
  int byteCount = 0;
  
  graphicAddress_ = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint32Size;
  
  int numAddresses = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint32Size;
  
  for (int i = 0; i < numAddresses; i++) {
    Taddress address = ByteConversion::fromBytes(
                            data + byteCount,
                            ByteSizes::uint32Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    byteCount += ByteSizes::uint32Size;
    
    pointerAddresses_.push_back(address);
  }
  
  return byteCount;
}


}; 
