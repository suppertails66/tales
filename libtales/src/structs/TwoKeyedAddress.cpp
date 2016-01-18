#include "structs/TwoKeyedAddress.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"
#include <iostream>

using namespace Luncheon;

namespace Tales {


TwoKeyedAddress::TwoKeyedAddress()
  : TwoKeyedAddressType() { }

TwoKeyedAddress::TwoKeyedAddress(const int subKeyTable__[],
                int numPrimaryKeys__)
  : TwoKeyedAddressType(subKeyTable__,
                        numPrimaryKeys__) { };

TwoKeyedAddress::~TwoKeyedAddress() { };

TwoKeyedAddress::TwoKeyedAddress(const TwoKeyedAddress& twoKeyMappedData)
  : TwoKeyedAddressType(twoKeyMappedData) { };

TwoKeyedAddress& TwoKeyedAddress::operator=(
      const TwoKeyedAddress& twoKeyMappedData) {
  TwoKeyedAddressType::operator=(twoKeyMappedData);
  
  return *this;
}

void TwoKeyedAddress::writeToData(std::string& data) {
  // Buffer to hold data for byte conversion
  Tbyte buffer[ByteSizes::uint32Size];
  
  // Write number of primary keys
  ByteConversion::toBytes(numPrimaryKeys_,
                          buffer,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint16Size);
  
//  std::cout << "outkeys: " << numPrimaryKeys_ << std::endl;
  
  // Write each key and data
  for (int i = 0; i < numPrimaryKeys_; i++) {
/*    // Write primary key
    ByteConversion::toBytes(i,
                            buffer,
                            ByteSizes::uint16Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    data += std::string((char*)buffer, ByteSizes::uint16Size); */
    
//    std::cout << "keys for " << i << ": " << subKeyTable_[i] << std::endl;
    
    // Write number of subkeys
    ByteConversion::toBytes(subKeyTable_[i],
                            buffer,
                            ByteSizes::uint16Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    data += std::string((char*)buffer, ByteSizes::uint16Size);
    
//    std::cout << "xxx" << std::endl;
    // Write each subkey
    for (int j = 0; j < subKeyTable_[i]; j++) {
      int primarykey = i + primaryKeyBase;
      int subkey = j + subKeyBase;
      
//      std::cout << '\t' << subkey << std::endl;

//      std::cout << '\t' << refDataByKeys(primarykey, subkey) << std::endl;
    
      // Write address (stored as 32-bit)
      ByteConversion::toBytes(refDataByKeys(primarykey, subkey),
                              buffer,
                              ByteSizes::uint32Size,
                              EndiannessTypes::little,
                              SignednessTypes::nosign);
      data += std::string((char*)buffer, ByteSizes::uint32Size);
    }
    
  }
}

int TwoKeyedAddress::readFromData(const Tbyte* data) {
  // Count of bytes read
  int count = 0;

  // Deallocate existing memory
  deallocateMemory();
  
  // Get number of primary keys
  numPrimaryKeys_ = ByteConversion::fromBytes(
                          data + count,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  count += ByteSizes::uint16Size;
  
  // Allocate tables
  data_ = new Taddress*[numPrimaryKeys_];
  subKeyTable_ = new int[numPrimaryKeys_];
  
  // Write each key and data
  for (int i = 0; i < numPrimaryKeys_; i++) {
    // Get number of subkeys
    int numSubKeys = ByteConversion::fromBytes(
                            data + count,
                            ByteSizes::uint16Size,
                            EndiannessTypes::little,
                            SignednessTypes::nosign);
    count += ByteSizes::uint16Size;
    
    // Place in subkey table
    subKeyTable_[i] = numSubKeys;
    
    // Allocate memory for associated values, if they exist
    if (numSubKeys != 0) {
      data_[i] = new Taddress[numSubKeys + subKeyBase];
    }
    else {
      data_[i] = NULL;
    }
    
    // Read each subkey
    for (int j = 0; j < subKeyTable_[i]; j++) {
      int primarykey = i + primaryKeyBase;
      int subkey = j + subKeyBase;
      
      // Read address (stored as 32-bit)
      refDataByKeys(primarykey, subkey) = 
          ByteConversion::fromBytes(data + count,
                                    ByteSizes::uint32Size,
                                    EndiannessTypes::little,
                                    SignednessTypes::nosign);
      count += ByteSizes::uint32Size;
    }
    
  }
  
  // Return number of bytes read
  return count;
}


}; 
