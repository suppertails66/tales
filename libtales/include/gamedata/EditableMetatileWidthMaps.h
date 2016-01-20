#ifndef EDITABLEMETATILEWIDTHMAPS_H
#define EDITABLEMETATILEWIDTHMAPS_H


#include "gamedata/EditableMetatileLengthMaps.h"
#include "structs/SaveHelper.h"
#include "structs/LoadHelper.h"

namespace Tales {


class EditableMetatileWidthMaps : public EditableMetatileLengthMaps {
public:
  /**
   * Default constructor.
   */
  EditableMetatileWidthMaps();
  
  /**
   * Constructor from ROM data.
   * @param rom ROM to load from.
   * @param address Address of metatile length maps.
   * @param numMaps Number of metatile length maps.
   */
  EditableMetatileWidthMaps(LoadedROM& rom,
                          Taddress baseAddress,
                          int numMaps);
  
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
protected:
  
};


};


#endif
