#include "structs/GraphicDependencyGroup.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"

using namespace Luncheon;

namespace Tales {


GraphicDependencyGroup::GraphicDependencyGroup() { };

BankPointerAddressCollection& GraphicDependencyGroup::bankPointerAddresses() {
  return bankPointerAddresses_;
}

GraphicDependencyGroupEntryCollection& GraphicDependencyGroup::entries() {
  return entries_;
}

void GraphicDependencyGroup::save(std::string& data) {
  Tbyte buffer[ByteSizes::uint32Size];
  
  ByteConversion::toBytes(bankPointerAddresses_.size(),
                          buffer,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint32Size);
  
  for (int i = 0; i < bankPointerAddresses_.size(); i++) {
    ByteConversion::toBytes(bankPointerAddresses_[i],
                            buffer,
                            ByteSizes::uint32Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    data += std::string((char*)buffer, ByteSizes::uint32Size);
  }
  
  ByteConversion::toBytes(entries_.size(),
                          buffer,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint32Size);
  
  for (int i = 0; i < entries_.size(); i++) {
    entries_[i].save(data);
  }
}

int GraphicDependencyGroup::load(const Tbyte* data) {
  bankPointerAddresses_.clear();
  entries_.clear();
  int byteCount = 0;
  
  int numBankPointers = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint32Size;
  
  for (int i = 0; i < numBankPointers; i++) {
    Taddress address = ByteConversion::fromBytes(
                            data + byteCount,
                            ByteSizes::uint32Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    byteCount += ByteSizes::uint32Size;
    
    bankPointerAddresses_.push_back(address);
  }
  
  int numEntries = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint32Size;
  
  for (int i = 0; i < numEntries; i++) {
    GraphicDependencyGroupEntry entry;
    byteCount += entry.load(data + byteCount);
    entries_.push_back(entry);
  }
  
  return byteCount;
}


};
