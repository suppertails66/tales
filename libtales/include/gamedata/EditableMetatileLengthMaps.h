#ifndef EDITABLEMETATILELENGTHMAPS_H
#define EDITABLEMETATILELENGTHMAPS_H


#include "gamedata/MetatileLengthMap.h"
#include "gamegear/LoadedROM.h"
#include "gamegear/WritableROM.h"
#include "structs/Tbyte.h"
#include "structs/Taddress.h"
#include "structs/Tmap.h"
#include "structs/SaveHelper.h"
#include "structs/LoadHelper.h"
#include <string>
#include <vector>


namespace Tales {


typedef Tmap<int, Taddress> LengthIndexToAddressMap;
typedef LengthIndexToAddressMap::PairType LengthIndexToAddressPair;

typedef std::vector<MetatileLengthMap> MetatileLengthMapCollection;

/**
 * Provides storage, access, and serialization on metatile lengths.
 * Intended for width and height maps.
 */
class EditableMetatileLengthMaps {
public:
  /**
   * Default constructor.
   */
  EditableMetatileLengthMaps();
  
  /**
   * Constructor from ROM data.
   * @param rom ROM to load from.
   * @param address Address of metatile length maps.
   * @param numMaps Number of metatile length maps.
   */
  EditableMetatileLengthMaps(LoadedROM& rom,
                          Taddress baseAddress,
                          int numMaps);
  
  /**
   * Returns number of loaded maps.
   * @return Number of loaded maps.
   */
  int size();
  
  /**
   * Returns the loaded map at the given index.
   * @param index The index to retrieve.
   * @return The loaded map at the given index.
   */
  MetatileLengthMap& mapAt(int index);
  
  /**
   * Saves to a string.
   * @param data String to save to.
   */
  virtual void save(std::string& data) =0;
  
  /**
   * Loads from a byte array.
   * @param data Byte array to load from.
   * @return The number of bytes read.
   */
  virtual int load(const Tbyte* data) =0;
  
  /**
   * Exports data to ROM.
   * @param rom ROM to write to.
   */
  void exportToROM(WritableROM& rom);
  
protected:
  
  /**
   * Saves to a string.
   * @param data String to save to.
   */
  virtual void saveInternal(std::string& data);
  
  /**
   * Loads from a byte array.
   * @param data Byte array to load from.
   * @return The number of bytes read.
   */
  virtual int loadInternal(const Tbyte* data,
                           int& byteCount);
  
  /**
   * Primary storage for length maps.
   */
  MetatileLengthMapCollection primaryStorage_;
  
  /**
   * Mapping of indices to corresponding addresses.
   */
  LengthIndexToAddressMap indexToAddress_;
  
};


};


#endif 
