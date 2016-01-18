#ifndef MAPLAYOUTS_H
#define MAPLAYOUTS_H


#include "structs/Tbyte.h"
#include "structs/Taddress.h"
#include "structs/Tmap.h"
#include "gamedata/MapLayout.h"
#include "gamedata/RawLevelHeaders.h"
#include "gamegear/LoadedROM.h"
#include "gamegear/WritableROM.h"
#include <string>
#include <vector>

namespace Tales {


typedef std::vector<MapLayout> MapLayoutCollection;
typedef Tmap<Taddress,int> AddressToMapIndexMap;
typedef AddressToMapIndexMap::PairType AddressToMapIndexPair;

class MapLayouts {
public:
  
  /**
   * Default constructor.
   */
  MapLayouts();
  
  /**
   * Constructor from data.
   * @param headers Raw level headers to load data from.
   */
  MapLayouts(LoadedROM& rom,
                     const RawLevelHeaders& headers);
  
  /**
   * Saves data to a string.
   * @param data String to save to.
   */
  void save(std::string& data);
  
  /**
   * Loads data from a byte array.
   * @param data Byte array to load from.
   * @return Number of bytes read.
   */
  int load(const Tbyte* data);
  
  /**
   * Exports data to ROM.
   * Throws if there is not enough free space to write all maps.
   * @param rom ROM to write to.
   * @throws NotEnoughSpaceException
   */
  void exportToROM(WritableROM& rom);
  
  /**
   * Returns the number of maps loaded.
   * @return The number of maps loaded.
   */
  int numMaps();
  
  /**
   * Returns the map associated with the given index.
   * @param index A map index number.
   * @return The map associated with the given index.
   */
  MapLayout& mapAtIndex(int index);
  
  /**
   * Returns the map associated with the given index (const).
   * @param index A map index number.
   * @return The map associated with the given index (const).
   */
  const MapLayout& mapAtIndex(int index) const;
  
  /**
   * Returns the index associated with a given initial address.
   * Only for initial ROM load.
   * @param address Address to get index of.
   * @return The index corresponding to the given address.
   */
  int indexOfInitialAddress(Taddress initialAddress) const;
  
protected:
  
  /**
   * Storage for map layouts.
   */
  MapLayoutCollection mapLayouts_;
  
  /**
   * Mapping of addresses to indices.
   * This is used only for the initial load from ROM to allow the level
   * headers to change their addresses into indices; it is neither needed nor
   * maintained afterward and should be ignored.
   */
  AddressToMapIndexMap addressToIndex_;
  
};


};


#endif
