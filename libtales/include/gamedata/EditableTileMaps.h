#ifndef EDITABLETILEMAPS_H
#define EDITABLETILEMAPS_H


#include "structs/Tbyte.h"
#include "gamegear/LoadedROM.h"
#include "gamegear/WritableROM.h"
#include "gamedata/TileMap.h"
#include "structs/IndexToAddressMap.h"
#include <string>
#include <vector>

namespace Tales {


/**
 * Storage for and accessors on fixed-layout tilemaps.
 */
class EditableTileMaps {
public:
  typedef std::vector<TileMap> TileMapCollection;

  /**
   * Default constructor.
   */
  EditableTileMaps();
  
  /**
   * Constructor from ROM data.
   * @param rom ROM to load from.
   */
  EditableTileMaps(LoadedROM& rom);
  
  /**
   * Returns number of loaded tilemaps.
   * @return Number of loaded tilemaps.
   */
  int size() const;
  
  /**
   * Access on the tilemap at the given index.
   * @param index Index of the value to access.
   * @return Reference to the value at the given index.
   */
  TileMap& tileMap(int index);
  
  /**
   * Const access on the tilemap at the given index.
   * @param index Index of the value to access.
   * @return Const reference to the value at the given index.
   */
  const TileMap& tileMap(int index) const;
  
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
   * Data chunk version number.
   */
  const static int versionNum_ = 0;

  /**
   * Storage for read tilemaps.
   */
  TileMapCollection primaryStorage_;
  
  /**
   * Mapping of tilemap indices to ROM addresses.
   */
  IndexToAddressMap indexToAddress_;
};


};


#endif
