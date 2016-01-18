#ifndef KEYEDADDRESSTABLEBUILDER_H
#define KEYEDADDRESSTABLEBUILDER_H


#include "structs/TwoKeyedAddress.h"
#include "structs/Taddress.h"
#include "gamegear/LoadedROM.h"

namespace Tales {


/**
 * Class for function(s) to build an address table.
 */
class KeyedAddressTableBuilder {
public:
  /**
   * "Alias" to KeyedTableBuilder::buildKeyedAddressTable().
   * TODO: remove this
   *
   * @param rom ROM to load data from.
   * @param address The direct address of the table to load.
   * @param table Container for read data that determines read size.
   * All the pairs in the subkey table will be filled.
   */
  static void buildKeyedAddressTable(LoadedROM& rom,
                                     Taddress address,
                                     TwoKeyedAddress& table);
                                     
protected:
  
  /**
   * Number of bytes per address to read.
   */
  const static int bytesPerAddress = 2;
};


};


#endif
