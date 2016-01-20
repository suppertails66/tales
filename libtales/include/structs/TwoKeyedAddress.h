#ifndef TWOKEYEDADDRESS_H
#define TWOKEYEDADDRESS_H


#include "structs/TwoKeyedData.h"
#include "structs/Taddress.h"
#include "structs/Tbyte.h"
#include <string>

namespace Tales {


/**
 * Helper typedef to simplify the definition of TwoKeyedAddress.
 * @see TwoKeyedAddress
 */
typedef TwoKeyedData<Taddress> TwoKeyedAddressType;

/**
 * A specialized kind of TwoKeyedData to hold Taddresses.
 */
class TwoKeyedAddress : public TwoKeyedAddressType {
public:
   /**
   * Default constructor.
   * Initializes tables to NULL and numPrimaryKeys_ to zero.
   */
  TwoKeyedAddress();
  
  /**
   * Constructor.
   * @param subKeyTable An array with (numPrimaryKeys) keys in which each entry
   * gives the number of subkeys for the primary key.
   * @param numPrimaryKeys Number of entries in subKeyTable.
   */
  TwoKeyedAddress(const int subKeyTable__[],
                  int numPrimaryKeys__);
  
  /**
   * Destructor.
   */
  virtual ~TwoKeyedAddress();
  
  /**
   * Copy constructor.
   * @param twoKeyMappedData Source from which to copy data.
   */
  TwoKeyedAddress(const TwoKeyedAddress& twoKeyMappedData);
  
  /**
   * Copy assignment.
   * @param twoKeyMappedData Source from which to copy data.
   */
  TwoKeyedAddress& operator=(const TwoKeyedAddress& twoKeyMappedData);
  
  /**
   * Writes a representation of the table to a string.
   * @param data The string to write to.
   * @see readFromData()
   */
  void writeToData(std::string& data);
  
  /**
   * Reads a representation of the table from a sequence of bytes.
   * @param data The sequence of bytes to read from.
   * @return The number of bytes of data read.
   * @see writeToData()
   */
  int readFromData(const Tbyte* data);
  
protected:
  
};


};


#endif 
