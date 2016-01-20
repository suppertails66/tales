#include "gamedata/RawLevelHeaders.h"
#include "gamedata/TailsAdvAddresses.h"
#include "gamedata/PrimaryMaps.h"
#include "gamedata/SubMaps.h"
#include "structs/KeyedAddressTableBuilder.h"
#include <iostream>

namespace Tales {


RawLevelHeaders::RawLevelHeaders() { };

RawLevelHeaders::RawLevelHeaders(LoadedROM& rom,
                                 Taddress tableAddress,
                                 Taddress contentAddress,
                                 int contentEntries)
  : keyedAccess_(SubMaps::subMapCounts,
                 SubMaps::subMapCountsSize) {
  
  // Read address table
  KeyedAddressTableBuilder::buildKeyedAddressTable(
      rom,
      tableAddress,
      keyedAccess_);
  
  // Insert entries for all headers in the table. There are 51
  // headers in total.
  // Note that we can't just use the address table to do
  // this because several headers are not referenced by the table.
  // The unreferenced headers seem to be for cutscenes (intro, dock) and the
  // alternate boss areas used when a boss arena is re-entered once the boss
  // is defeated. Presumably, they are hardcoded for those circumstances.
  for (int i = 0; i < contentEntries; i++) {
      // Address of the target header
      int targetAddress = contentAddress + (i * RawLevelHeader::dataSize);
       
      // Generate insertion pair of address and header
      AddressRawLevelHeaderPair newPair(
            targetAddress,
            RawLevelHeader(rom, targetAddress));
      
      // Insert into storage
      primaryStorage_.insert(newPair);
  }
}

const TwoKeyedAddress& RawLevelHeaders::keyedAccess() const {
  return keyedAccess_;
}

RawLevelHeader& RawLevelHeaders::rawLevelHeader(int primaryMap,
                                             int subMap) {
  // Get address of target data
  Taddress address = keyedAccess_.refDataByKeys(primaryMap, subMap);
  
  // Return corresponding key
  return primaryStorage_.findValueOrThrow(address);
}

const RawLevelHeader& RawLevelHeaders::constRawLevelHeader(int primaryMap,
                                                        int subMap) const {
  // Get address of target data
  Taddress address = keyedAccess_.refDataByKeys(primaryMap, subMap);
  
  // Return corresponding key
  return primaryStorage_.findValueOrThrow(address);
}

/*void RawLevelHeaders::clear() {
  primaryStorage_.clear();
} */
  
AddressRawLevelHeaderMap::iterator RawLevelHeaders::begin() {
  return primaryStorage_.begin();
}

AddressRawLevelHeaderMap::iterator RawLevelHeaders::end() {
  return primaryStorage_.end();
}

AddressRawLevelHeaderMap::const_iterator RawLevelHeaders::cbegin() const {
  return primaryStorage_.cbegin();
}

AddressRawLevelHeaderMap::const_iterator RawLevelHeaders::cend() const {
  return primaryStorage_.cend();
}


}
