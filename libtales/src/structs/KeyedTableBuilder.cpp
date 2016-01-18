#include "structs/KeyedTableBuilder.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"
#include "structs/KeyedAddressTableBuilder.h"
#include <iostream>

using namespace Luncheon;

namespace Tales {


void KeyedTableBuilder::
     buildKeyedAddressTable(LoadedROM& rom,
                            Taddress address,
                            TwoKeyedAddress& table) {
  // Get the bank number corresponding to this direct address for future
  // conversions
  int bankNum = LoadedROM::directToBankNum(address);
  
  // Iterate over primary keys
  for (int i = 0;
         i < table.numPrimaryKeys();
         i++) {
    // Read the first address
    int bankedPrimaryAddress = ByteConversion::fromBytes(
          rom.directRead(address + (i * bytesPerAddress)),
          ByteSizes::uint16Size,
          EndiannessTypes::little,
          SignednessTypes::nosign);
    
    // Convert to direct address
    int primaryAddress
      = LoadedROM::getDirectAddress(bankNum, bankedPrimaryAddress);
         
    // Iterate over subkeys
    int numSubKeys = table.subKeyTable()[i];
    for (int j = 0;
           j < numSubKeys;
           j++) {
      // Read the second address
      int bankedSecondaryAddress = ByteConversion::fromBytes(
            rom.directRead(primaryAddress + (j * bytesPerAddress)),
            ByteSizes::uint16Size,
            EndiannessTypes::little,
            SignednessTypes::nosign);
      
      // Convert to direct address
      int secondaryAddress
        = LoadedROM::getDirectAddress(bankNum, bankedSecondaryAddress);
      
      // Save address
      table.refDataByKeys(i + TwoKeyedAddress::primaryKeyBase,
                          j + TwoKeyedAddress::subKeyBase)
        = secondaryAddress;
    }
  }
}

void KeyedTableBuilder::buildKeyedPrimaryOnlyTable(
                                LoadedROM& rom,
                                Taddress address,
                                int entryDataSize,
                                TwoKeyedAddress& table) {
  // Get the bank number corresponding to this direct address for future
  // conversions
  int bankNum = LoadedROM::directToBankNum(address);
  
  // Iterate over primary keys
  for (int i = 0;
         i < table.numPrimaryKeys();
         i++) {
    // Read the address
    int bankedPrimaryAddress = ByteConversion::fromBytes(
          rom.directRead(address + (i * bytesPerAddress)),
          ByteSizes::uint16Size,
          EndiannessTypes::little,
          SignednessTypes::nosign);
    
    // Convert to direct address
    int primaryAddress
      = LoadedROM::getDirectAddress(bankNum, bankedPrimaryAddress);
         
    // Iterate over subkeys
    int numSubKeys = table.subKeyTable()[i];
    int offset = 0;   // Offset from first entry
    for (int j = 0;
           j < numSubKeys;
           j++) {
      // Save address
      table.refDataByKeys(i + TwoKeyedAddress::primaryKeyBase,
                          j + TwoKeyedAddress::subKeyBase)
        = primaryAddress + offset;
      offset += entryDataSize;
    }
  }
}

void KeyedTableBuilder::buildKeyedPrimaryOnlyIndexTable(
                                     LoadedROM& rom,
                                     Taddress address,
                                     Taddress contentAddress,
                                     int entryDataSize,
                                     TwoKeyedAddress& table) {
  buildKeyedPrimaryOnlyTable(rom,
                             address,
                             entryDataSize,
                             table);
  
  // Convert addresses to indices
  for (int i = 0;
         i < table.numPrimaryKeys();
         i++) {
    int numSubKeys = table.subKeyTable()[i];
    for (int j = 0;
           j < numSubKeys;
           j++) {
      // Get address
      Taddress& value 
        = table.refDataByKeys(i + TwoKeyedAddress::primaryKeyBase,
                              j + TwoKeyedAddress::subKeyBase);
      
      // Convert to index
      value = (value - contentAddress)/entryDataSize;
      
//      std::cout << value << std::endl;
    }
  }
}

void KeyedTableBuilder::buildTwoKeyedArrayTable(
                             LoadedROM& rom,
                             Taddress startAddress,
                             Taddress endAddress,
                             int elementSize,
                             TwoKeyedData<AddressSizePair>& table) {
/*  // Get the bank number corresponding to this direct address for future
  // conversions
  int bankNum = LoadedROM::directToBankNum(address);
  
  // Iterate over primary keys
  for (int i = 0;
         i < table.numPrimaryKeys();
         i++) {
    // Read the first address
    int bankedPrimaryAddress = ByteConversion::fromBytes(
          rom.directRead(address + (i * bytesPerAddress)),
          ByteSizes::uint16Size,
          EndiannessTypes::little,
          SignednessTypes::nosign);
    
    // Convert to direct address
    int primaryAddress
      = LoadedROM::getDirectAddress(bankNum, bankedPrimaryAddress);
         
    // Iterate over subkeys
    int numSubKeys = table.subKeyTable()[i];
    for (int j = 0;
           j < numSubKeys;
           j++) {
      // Read the second address
      int bankedSecondaryAddress = ByteConversion::fromBytes(
            rom.directRead(primaryAddress + (j * bytesPerAddress)),
            ByteSizes::uint16Size,
            EndiannessTypes::little,
            SignednessTypes::nosign);
      
      // Convert to direct address
      int secondaryAddress
        = LoadedROM::getDirectAddress(bankNum, bankedSecondaryAddress);
      
      // Save address
      table.refDataByKeys(i + TwoKeyedAddress::primaryKeyBase,
                          j + TwoKeyedAddress::subKeyBase)
        = secondaryAddress;
    }
  } */
}


}; 
