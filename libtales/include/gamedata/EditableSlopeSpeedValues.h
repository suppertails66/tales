#ifndef EDITABLESLOPESPEEDVALUES_H
#define EDITABLESLOPESPEEDVALUES_H


#include "structs/Tbyte.h"
#include "structs/Taddress.h"
#include "gamegear/LoadedROM.h"
#include "gamegear/WritableROM.h"
#include "structs/SaveHelper.h"
#include "structs/LoadHelper.h"
#include <string>
#include <vector>

namespace Tales {


/**
 * Slope speed values are (signed) modifiers to pixel movement.
 * The value is added to Tails' targeted x-position each frame that he is
 * in contact with the ground in order to make him move faster or slower than
 * usual. Positive values mean faster movement to the right and slower to the
 * left, and vice versa for negative.
 */
typedef signed int SlopeSpeedValue;

typedef std::vector<SlopeSpeedValue> SlopeSpeedValueCollection;

/**
 * Storage and access on slope speed modifier values.
 * These values are used to make Tails walk faster or slower on
 * sloped terrain (although they work on any kind of solid ground).
 */
class EditableSlopeSpeedValues {
public:
  /**
   * Default constructor.
   */
  EditableSlopeSpeedValues();
  
  /**
   * Constructor from ROM data.
   * @param rom ROM to load from.
   * @param address Address of the slope speed adjustment table.
   * @param numEntries Number of entries in ROM's slope speed adjustment table.
   */
  EditableSlopeSpeedValues(LoadedROM& rom,
                           Taddress baseAddress__,
                           int numEntries);
  
  /**
   * Returns number of loaded slope speed value entries.
   * @return Number of loaded slope speed value entries.
   */
  int size() const;
  
  /**
   * Access on the slope speed value at the given index.
   * @param index The index to access.
   * @return Reference to the value at the given index.
   */
  SlopeSpeedValue& speedValue(int index);
  
  /**
   * Const access on the slope speed value at the given index.
   * @param index The index to access.
   * @return Const reference to the value at the given index.
   */
  const SlopeSpeedValue& speedValue(int index) const;
  
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
   * Exports data to ROM.
   * @param rom ROM to write to.
   */
  void exportToROM(WritableROM& rom);
  
protected:

  /**
   * Base address of table for exporting.
   */
  Taddress baseAddress_;
  
  /**
   * Slope speed adjustment values.
   */
  SlopeSpeedValueCollection speedValues_;
  
};


};


#endif 
