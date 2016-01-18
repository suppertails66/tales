#ifndef KEYEDTABLEBUILDER_H
#define KEYEDTABLEBUILDER_H


#include "structs/TwoKeyedData.h"
#include "structs/TwoKeyedAddress.h"
#include "structs/Taddress.h"
#include "gamegear/LoadedROM.h"
#include <utility>

namespace Tales {


/**
 * An address of a data array and the number of elements in that array.
 */
typedef std::pair<Taddress, int> AddressSizePair;

/**
 * Class for function(s) to build a table addressed by map numbers.
 */
class KeyedTableBuilder {
public:
  /**
   * Builds an address table from a generic two-keyed table pair.
   * This is a utility function to deal with a common table format in
   * Tails Adventures.
   * In this format, there are two tables. The first is a table of 16-bit
   * banked addresses, indexed by primary map number. The addresses in the
   * first table index directly into the second. At the address given by the
   * first table, a submap number can be used as an index to retrieve the
   * banked address of the data associated with that (primary, sub) key pair.
   * This function automatically reads such a table, filling the passed
   * TwoKeyedAddress structure with the direct addresses corresponding to
   * each key pair.
   *
   * @param rom ROM to load data from.
   * @param address The direct address of the table to load.
   * @param table Container for read data that determines read size.
   * All the pairs in the subkey table will be filled.
   * @see KeyedAddressTableBuilder::buildKeyedAddressTable()
   */
  static void buildKeyedAddressTable(LoadedROM& rom,
                                     Taddress address,
                                     TwoKeyedAddress& table);
  
  /**
   * Builds an address table from a primary-key-only table.
   * In this format, there is only one explicit table of addresses,
   * which is indexed by the primary key. The target data is fixed-size,
   * and subkeys are defined implicitly by adding to a primary key address.
   *
   * @param rom ROM to load data from.
   * @param address Address of the table in ROM.
   * @param entryDataSize Size of one entry in the table content.
   * @param table Container for read data that determines read size.
   * All the pairs in the subkey table will be filled.
   * @see KeyedAddressTableBuilder::buildKeyedAddressTable()
   */
  static void buildKeyedPrimaryOnlyTable(LoadedROM& rom,
                                     Taddress address,
                                     int entryDataSize,
                                     TwoKeyedAddress& table);
                                     
  /**
   * Same as buildKeyedPrimaryOnlyTable() with indices instead of addresses.
   * @see buildKeyedPrimaryOnlyTable()
   */
  static void buildKeyedPrimaryOnlyIndexTable(LoadedROM& rom,
                                     Taddress address,
                                     Taddress contentAddress,
                                     int entryDataSize,
                                     TwoKeyedAddress& table);
                                     
  /**
   * Constructs a table of array addresses and sizes from ROM data.
   * This operates on the semi-standard two-tabled addressing scheme
   * described in KeyedAddressTableBuilder.
   *
   * @param rom ROM to load data from.
   * @param startAddress Direct address of the start of the table to analyze.
   * @param endAddress Direct address of one past the end of the table to
   * analyze.
   * @param elementSize Size of each array element.
   * @param table Storage for read data. Only the key pairs found in this table
   * will be read from the ROM.
   * @see KeyedAddressTableBuilder
   */
  static void buildTwoKeyedArrayTable(LoadedROM& rom,
                                     Taddress startAddress,
                                     Taddress endAddress,
                                     int elementSize,
                                     TwoKeyedData<AddressSizePair>& table);
                                     
protected:
  /**
   * Number of bytes per address to read.
   */
  const static int bytesPerAddress = 2;
  
};


};


#endif
