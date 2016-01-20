#ifndef LEVELHEADERS_H
#define LEVELHEADERS_H


#include "structs/Tmap.h"
#include "structs/Taddress.h"
#include "structs/TwoKeyedAddress.h"
#include "structs/IndexToAddressMap.h"
#include "gamedata/LevelHeader.h"
#include "gamedata/RawLevelHeaders.h"
#include "gamedata/MetatileStructures.h"
#include "gamedata/MapLayouts.h"
#include "gamedata/YTableAddresses.h"
#include "gamedata/AreaMapReference.h"

namespace Tales {


//typedef Tmap<Taddress, LevelHeader>::Type AddressLevelHeaderMap;
//typedef Tmap<Taddress, LevelHeader>::PairType AddressLevelHeaderPair;

typedef IndexToAddressMap IndexLevelHeaderAddressMap;
typedef Tmap<Taddress, LevelHeader> AddressLevelHeaderMap;
typedef AddressLevelHeaderMap::PairType AddressLevelHeaderPair;

class LevelHeaders {
public:
  const static int worldMapDupeHeaderIndex = 39;
  const static int introDupeHeaderIndex = 40;
  const static int lakeRocky1HeaderIndex = 44;
  const static int lakeRockyBossHeaderIndex = 46;
  const static int lakeRocky2HeaderIndex = 47;
  const static int pollyMt1BossHeaderIndex = 48;
  const static int cavernIslandBossHeaderIndex = 49;

  /**
   * Default constructor.
   */
  LevelHeaders();

  /**
   * Construct from ROM data.
   * @param rom ROM to load from.
   * @param address Address of metatile behavior table content.
   */
  LevelHeaders(LoadedROM& rom,
                       Taddress address,
                       const RawLevelHeaders& rawHeaders,
                       const MetatileStructures&
                         metatileStructures,
                       const MapLayouts& mapLayouts,
                       const YTableAddresses& yTableAddresses);
  
  /**  
   * Appends a loadable representation of edited state to the given string.
   * @param data A string to which the representation of the altered state
   * should be appended.
   * @see load()
   */
  void save(std::string& data);
  
  /**  
   * Loads edited state from a block of data written using save().
   * @param data A block of raw data corresponding to a previous call to
   * save().
   * @return The number of bytes loaded from the data.
   * @see save()
   */
  int load(const Tbyte* data);
  
  /**  
   * Writes the contained data to a WritableROM.
   * @param rom WritableROM to write data to.
   */
  void exportToROM(WritableROM& rom,
                   const MetatileStructures&
                     metatileStructures,
                   const MapLayouts& mapLayouts,
                   const YTableAddresses& yTableAddresses);
                   
  /**
   * Returns number of level headers.
   * @return Number of level headers.
   */
  int size() const;
  
  /**
   * Accesses headers by primary and submap number.
   * @param primaryMap The primary map number.
   * @param subMap The submap number.
   * @return The LevelHeader corresponding to the given keys.
   */
  LevelHeader& levelHeader(int primaryMap, int subMap);
  
  /**
   * Finds and returns the index number of an area/mapnum pair.
   * @return The index number of a level header.
   */
  int levelHeaderIndex(int primaryMap, int subMap);
  
  /**
   * Finds and returns the area/mapnum pair of an index.
   * Area and map will be zero if the index does not correspond to an
   * area/mapnum pair.
   * @return The area/mapnum pair of an index.
   */
  AreaMapReference areaMapNumOfIndex(int levelHeaderIndexNum);
   
  /**
   * Finds and returns the header corresponding to the given index.
   * @return The header corresponding to the given index.
   */
  LevelHeader& levelHeaderByIndex(int levelHeaderIndexNum);
  
  /**
   * Get an iterator to the start of the primary storage map.
   * @return Iterator the start of the primary storage map.
   */
  AddressLevelHeaderMap::iterator begin();
  
  /**
   * Get an iterator to the end of the primary storage map.
   * @return Iterator the end of the primary storage map.
   */
  AddressLevelHeaderMap::iterator end();
   
protected:
  
  /**
   * Mapping of index number to addresses.
   */
  IndexLevelHeaderAddressMap indexToAddress_;
  
  /**
   * Primary storage for the level headers.
   */
  AddressLevelHeaderMap primaryStorage_;
  
  /**
   * Access on primaryStorage_ by primary and submap number.
   */
  TwoKeyedAddress keyedAccess_;
  
  
};


};


#endif 
