#ifndef EDITABLESPRITEMAPPINGS_H
#define EDITABLESPRITEMAPPINGS_H


#include "structs/Tbyte.h"
#include "structs/Taddress.h"
#include "structs/Tmap.h"
#include "gamegear/LoadedROM.h"
#include "gamegear/WritableROM.h"
#include "gamedata/RawSpriteMapping.h"
#include "gamedata/SpriteMapping.h"
#include "gamedata/SpriteMappingCoordinateTable.h"
#include "gamedata/SpriteMappingTileIndexTable.h"
#include "structs/SaveHelper.h"
#include "structs/LoadHelper.h"
#include <vector>
#include <string>

namespace Tales {


class EditableSpriteMappings {
public:
  typedef std::vector<Taddress> MappingTableAddressCollection;
  typedef Tmap<Taddress, int> MappingTableAddressToSize;
  typedef Tmap<Taddress, int> MappingTableAddressToIndex;
  typedef Tmap<Taddress, int> CoordinateTableAddressToSize;
  typedef Tmap<Taddress, int> TileIndexTableAddressToSize;
  typedef Tmap<int, Taddress> MappingIndexToAddress;
  typedef Tmap<int, Taddress> CoordinateTableIndexToAddress;
  typedef Tmap<int, Taddress> TileIndexTableIndexToAddress;
  typedef std::vector<int> ObjectIDToSpriteMappingIndex;
  typedef std::vector<Taddress> ObjectIDToAddress;
  typedef Tmap<Taddress, RawSpriteMapping> AddressToRawMapping;
  typedef std::vector<SpriteMapping>
    SpriteMappingCollection;
  typedef std::vector<SpriteMappingCoordinateTable>
    SpriteMappingCoordinateTableCollection;
  typedef std::vector<SpriteMappingTileIndexTable>
    SpriteMappingTileIndexTableCollection;
    
  typedef std::vector<Taddress> MappingAddressCollection;
  typedef std::vector<int> MappingIndexCollection;
  typedef std::vector<MappingAddressCollection> ObjectIDToMappingAddresses;
  typedef std::vector<MappingIndexCollection> ObjectIDToMappingIndices;
  
  /**
   * Default constructor.
   */
  EditableSpriteMappings();
  
  /**
   * Constructor from ROM.
   * @param rom LoadedROM to read from.
   */
  EditableSpriteMappings(LoadedROM& rom,
                         Taddress mappingTableAddress__,
                         int numObjects__);
  
  /**
   * Saves to a string.
   * @param data String to save to.
   */
  void save(std::string& data);
  
  /**
   * Reads from a raw byte array.
   * @param data Byte array to read from.
   * @return Number of bytes read.
   */
  int load(const Tbyte* data);
  
  /**
   * Exports data to ROM.
   * @param rom WritableROM to write to.
   */
  void exportToROM(WritableROM& rom);
  
  /**
   * Returns number of sprite mappings.
   * @return Number of sprite mappings.
   */
  int numSpriteMappings() const;
  
  /**
   * Returns number of coordinate tables.
   * @return Number of coordinate tables.
   */
  int numCoordinateTables() const;
  
  /**
   * Returns number of tile index tables.
   * @return Number of tile index tables.
   */
  int numTileIndexTables() const;
  
  SpriteMapping& spriteMapping(int index);
  
  SpriteMappingCoordinateTable& coordinateTable(int index);
  
  SpriteMappingCoordinateTable& flipCoordinateTable(int index);
  
  SpriteMappingTileIndexTable& tileIndexTable(int index);
  
  const SpriteMapping& spriteMapping(int index) const;
  
  const SpriteMappingCoordinateTable& coordinateTable(int index) const;
  
  const SpriteMappingCoordinateTable& flipCoordinateTable(int index) const;
  
  const SpriteMappingTileIndexTable& tileIndexTable(int index) const;
  
  MappingIndexCollection mappingsByObjectID(int objectID);
protected:

  const static int offsetToHorizontalFlip = 0x3C0;
    
  Taddress mappingTableAddress_;
  
  int numObjects_;
    
  SpriteMappingCollection spriteMappings_;
  SpriteMappingCoordinateTableCollection spriteMappingCoordinateTables_;
  SpriteMappingCoordinateTableCollection spriteMappingFlipCoordinateTables_;
  SpriteMappingTileIndexTableCollection spriteMappingTileIndexTables_;
  
  MappingIndexToAddress mappingIndexToAddress_;
  CoordinateTableIndexToAddress coordinateTableIndexToAddress_;
  TileIndexTableIndexToAddress tileIndexTableIndexToAddress_;
  
//  ObjectIDToSpriteMappingIndex mappingsByID_;

  ObjectIDToMappingIndices objectIDToMappingIndices_;
  
};


};


#endif
