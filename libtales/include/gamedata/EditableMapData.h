#ifndef EDITABLEMAPDATA_H
#define EDITABLEMAPDATA_H


#include "gamedata/RawLevelHeaders.h"
#include "gamedata/YTableAddresses.h"
#include "gamedata/MetatileStructures.h"
#include "gamedata/MapLayouts.h"
#include "gamedata/LevelHeaders.h"
#include "structs/SaveHelper.h"
#include "structs/LoadHelper.h"

namespace Tales {


class EditableMapData {
public:
  /**
   * Default constructor.
   */
  EditableMapData();
  
  /**
   * Constructor from existing data.
   */
  EditableMapData(LoadedROM& rom,
                  Taddress levelHeaderTableAddress,
                  Taddress levelHeaderTableContentAddress,
                  int numLevelHeaderTableEntries);
                  
  void save(std::string& data);
  
  int load(const Tbyte* data);
  
  void exportToROM(WritableROM& rom);
  
  /**
   * Accessor.
   */
  MetatileStructures& metatileStructures();
  
  /**
   * Accessor.
   */
  MapLayouts& mapLayouts();
  
  /**
   * Accessor.
   */
  LevelHeaders& levelHeaders();
                  
protected:

  RawLevelHeaders rawLevelHeaders_;
  YTableAddresses yTableAddresses_;
  
  MetatileStructures metatileStructures_;
  MapLayouts mapLayouts_;
  LevelHeaders levelHeaders_;
  
  
};


};


#endif
