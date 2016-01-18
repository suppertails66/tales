#ifndef INDEXTOADDRESSMAP_H
#define INDEXTOADDRESSMAP_H


#include "structs/Tbyte.h"
#include "structs/Taddress.h"
#include "structs/Tmap.h"
#include <string>

namespace Tales {


typedef Tmap<int, Taddress> BaseIndexToAddressMap;

class IndexToAddressMap : public BaseIndexToAddressMap {
public:
  /**
   * Default constructor.
   */
  IndexToAddressMap();
  
  /**
   * Save to a string.
   * @param data String to save to.
   */
  void save(std::string& data);
  
  /**
   * Load from a byte array.
   * @param data Byte array to load from.
   * @return Number of bytes read.
   */
  int load(const Tbyte* data);
  
protected:
  
};

typedef IndexToAddressMap::PairType IndexToAddressPair;


};


#endif
