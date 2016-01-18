#ifndef RAWLEVELHEADERS_H
#define RAWLEVELHEADERS_H


#include "gamedata/RawLevelHeader.h"
#include "gamegear/LoadedROM.h"
#include "structs/Taddress.h"
#include "structs/Tmap.h"
#include "structs/TwoKeyedAddress.h"

namespace Tales {


typedef Tmap<Taddress, RawLevelHeader> AddressRawLevelHeaderMap;
typedef AddressRawLevelHeaderMap::PairType AddressRawLevelHeaderPair;

/**
 * Container for raw level headers.
 */
class RawLevelHeaders {
public:
  /**
   * Default constructor.
   */
  RawLevelHeaders();
  
  /**
   * Constructor from ROM.
   * @param rom ROM to load from.
   * @param tableAddress Address of the level header table, including key
   * tables.
   * @param contentAddress Address of the contents of the level header table.
   * @param contentEntries Number of header entries at contentAddress.
   */
  RawLevelHeaders(LoadedROM& rom,
                  Taddress tableAddress,
                  Taddress contentAddress,
                  int contentEntries);
                  
  /**
   * Const access to address keymap.
   */
  const TwoKeyedAddress& keyedAccess() const;
                  
  /**
   * Returns a reference to the raw header for the given map numbers.
   * @param primaryMap The primary map number.
   * @param subMap The submap number.
   * @return A reference to the raw header for the given map numbers.
   */
  RawLevelHeader& rawLevelHeader(int primaryMap,
                              int subMap);
                  
  /**
   * Returns a const reference to the raw header for the given map numbers.
   * @param primaryMap The primary map number.
   * @param subMap The submap number.
   * @return A const reference to the raw header for the given map numbers.
   */
  const RawLevelHeader& constRawLevelHeader(int primaryMap,
                                         int subMap) const;
                                         
  /**
   * Clears all entries.
   */
//  void clear();
  
  /**
   * Returns iterator to start of primaryStorage_.
   * @return Iterator to start of primaryStorage_.
   */
  AddressRawLevelHeaderMap::iterator begin();
  
  /**
   * Returns iterator to end of primaryStorage_.
   * @return Iterator to end of primaryStorage_.
   */
  AddressRawLevelHeaderMap::iterator end();
  
  /**
   * Returns const iterator to start of primaryStorage_.
   * @return Const terator to start of primaryStorage_.
   */
  AddressRawLevelHeaderMap::const_iterator cbegin() const;
  
  /**
   * Returns const iterator to end of primaryStorage_.
   * @return Const iterator to end of primaryStorage_.
   */
  AddressRawLevelHeaderMap::const_iterator cend() const;
  
protected:
  
  /**
   * Storage for raw level headers.
   */
  AddressRawLevelHeaderMap primaryStorage_;
  
  /**
   * Access on primaryStorage_ by primary and submap number.
   */
  TwoKeyedAddress keyedAccess_;
  
};


};


#endif 
