#include "structs/KeyedAddressTableBuilder.h"
#include "structs/KeyedTableBuilder.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"
#include <iostream>

using namespace Luncheon;

namespace Tales {


void KeyedAddressTableBuilder::
     buildKeyedAddressTable(LoadedROM& rom,
                            Taddress address,
                            TwoKeyedAddress& table) {
  KeyedTableBuilder::buildKeyedAddressTable(rom,
                                            address,
                                            table);

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


}; 
