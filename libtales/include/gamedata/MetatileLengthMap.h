#ifndef METATILELENGTHMAP_H
#define METATILELENGTHMAP_H


#include "structs/Tbyte.h"
#include "structs/Taddress.h"
#include "gamegear/LoadedROM.h"
#include "gamegear/WritableROM.h"
#include "gamedata/LengthMapValue.h"
#include <string>

namespace Tales {


/**
 * Mapping of metatile pixels positions to magnitudes.
 * Intended for use by MetatileWidthMap and MetatileHeightMap.
 * @see MetatileWidthMap
 * @see MetatileHeightMap
 */
class MetatileLengthMap {
public:
  /**
   * Number of elements in a length map.
   */
  const static int numElements = 0x10;

  /**
   * Number of bytes in a length map.
   */
  const static int dataSize = numElements
                                * LengthMapValue::dataSize;

  /**
   * Default constructor.
   * Initializes all lengths to zero.
   */
  MetatileLengthMap();
  
  /**
   * Constructor from raw data.
   * @param data Data to read map from.
   */
  MetatileLengthMap(const Tbyte* data);
  
  /**
   * Returns the length at the given index.
   * @param index Index of the value to return.
   */
  LengthMapValue& lengthAt(int index);
  
  /**
   * Sets the length at the given index to the given value.
   * @param index Index to set.
   * @param value The new value at the given index.
   */
  void setLengthAt(int index, LengthMapValue value);
  
  /**
   * Accesseor on lengths_.
   * @param index Index to access.
   * @return The length at the given index.
   */
  LengthMapValue& lengths(int index);
  
  /**
   * Const accessor on lengths_.
   * @param index Index to access.
   * @return The length at the given index.
   */
  const LengthMapValue& lengths(int index) const;
  
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
   * Writes raw data representation.
   * @param data Byte array to write to. Length must be at least (dataSize).
   */
  void writeToData(Tbyte* data);
  
protected:
  
  /**
   * Array of length mappings.
   */
  LengthMapValue lengths_[dataSize];
  
};


};


#endif
