#ifndef YTABLEADDRESSES_H
#define YTABLEADDRESSES_H


#include "structs/LevelWidth.h"
#include "gamedata/RawLevelHeaders.h"
#include "structs/Tbyte.h"
#include "structs/Taddress.h"
#include "structs/Tmap.h"
#include <string>

namespace Tales {


typedef Tmap<Taddress,int> AddressToWidthMap;
typedef AddressToWidthMap::PairType AddressToWidthPair;

typedef Tmap<int, Taddress> WidthToYTableMap;
typedef WidthToYTableMap::PairType WidthToYTablePair;

/**
 * Container for mapping of width values to corresponding y-tables.
 */
class YTableAddresses {
public:
  /**
   * Default constructor.
   */
  YTableAddresses();
  
  /**
   * Constructor from raw header data.
   * @param headers Raw headers to load from.
   */
  YTableAddresses(const RawLevelHeaders& headers);
  
  /**
   * Saves to a string.
   * @param data String to save to.
   */
  void save(std::string& data);
  
  /**
   * Loads from a byte array.
   * @param data Byte array to load from.
   * @return The number of bytes read.
   */
  int load(const Tbyte* data);
  
  /**
   * Returns the address corresponding to a width value.
   * @param width Integer width value.
   * @return The address of the y-table corresponding to the given width.
   */
  Taddress addressOfWidth(int width) const;
  
  /**
   * Returns number of width-to-y-table mappings.
   * @return Number of width-to-y-table mappings.
   */
  int widthToYMapSize();
  
  /**
   * Returns iterator to start of width-to-y-table map.
   * @return Iterator to start of width-to-y-table map.
   */
  WidthToYTableMap::iterator widthToYMapBegin();
  
  /**
   * Returns iterator to end of width-to-y-table map.
   * @return Iterator to end of width-to-y-table map.
   */
  WidthToYTableMap::iterator widthToYMapEnd();
  
  /**
   * Returns const iterator to start of width-to-y-table map.
   * @return Const iterator to start of width-to-y-table map.
   */
  WidthToYTableMap::const_iterator widthToYMapCbegin();
  
  /**
   * Returns const iterator to end of width-to-y-table map.
   * @return Const iterator to end of width-to-y-table map.
   */
  WidthToYTableMap::const_iterator widthToYMapCend();
  
  /**
   * Returns the index associated with a given initial address.
   * Only for initial ROM load.
   * @param address Address to get index of.
   * @return The index corresponding to the given address.
   */
  int widthOfInitialAddress(Taddress initialAddress) const;
  
protected:
  
  /**
   * Mapping of integer width values to y-table addresses.
   */
  WidthToYTableMap widthToYTableMap_;
  
  /**
   * Mapping of addresses to indices.
   * This is used only for the initial load from ROM to allow the level
   * headers to change their addresses into indices; it is neither needed nor
   * maintained afterward and should be ignored.
   */
  AddressToWidthMap addressToWidth_;
  
};


};


#endif 
