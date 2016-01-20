#include "structs/IndexToAddressMap.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"

using namespace Luncheon;

namespace Tales {


IndexToAddressMap::IndexToAddressMap()
  : BaseIndexToAddressMap() { };
  
void IndexToAddressMap::save(std::string& data) {
  Tbyte buffer[ByteSizes::uint32Size];
  
  // Write number of entries
  ByteConversion::toBytes(this->size(),
                          buffer,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint32Size);
  
  // Write each entry
  for (IndexToAddressMap::iterator it = this->begin();
       it != this->end();
       it++) {
    // Write index
    ByteConversion::toBytes(it->first,
                            buffer,
                            ByteSizes::uint32Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    data += std::string((char*)buffer, ByteSizes::uint32Size);
    
    // Write address
    ByteConversion::toBytes(it->second,
                            buffer,
                            ByteSizes::uint32Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    data += std::string((char*)buffer, ByteSizes::uint32Size);
  }
}

int IndexToAddressMap::load(const Tbyte* data) {
  // Destroy existing content
  clear();
  
  // Count of read byte
  int byteCount = 0;
  
  // Read number of entries
  int numEntries = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint32Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint32Size;
  
  // Read each entry
  for (int i = 0; i < numEntries; i++) {
    // Read index
    int index = ByteConversion::fromBytes(
                            data + byteCount,
                            ByteSizes::uint32Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    byteCount += ByteSizes::uint32Size;
    
    // Read address
    int address = ByteConversion::fromBytes(
                            data + byteCount,
                            ByteSizes::uint32Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    byteCount += ByteSizes::uint32Size;
    
    this->insert(
      PairType(index, address));
  }
  
  // Return count of bytes read
  return byteCount;
}


};
