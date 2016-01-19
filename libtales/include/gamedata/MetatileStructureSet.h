#ifndef METATILESTRUCTURESET
#define METATILESTRUCTURESET


#include <vector>
#include "gamegear/LoadedROM.h"
#include "gamegear/WritableROM.h"
#include "structs/Taddress.h"
#include "structs/Tmap.h"
#include "structs/Tbyte.h"
#include "gamedata/MetatileStructure.h"
#include <vector>
#include <string>

namespace Tales {


//typedef std::vector<MetatileStructure> MetatileStructureSet;
typedef std::vector<MetatileStructure> MetatileStructureCollection;
typedef Tmap<int, int> MetatileIndexToStructureMap;
typedef Tmap<int, int>::PairType MetatileIndexToStructurePair;

/**
 * A mapping of metatile indices to metatile structural definitions.
 */
class MetatileStructureSet {
public:
  /**
   * Default constructor.
   */
  MetatileStructureSet();
  
  /**
   * Constructor from data.
   * @param rom ROM to load from.
   * @param address__ Address of the structure definitions to load.
   */
  MetatileStructureSet(LoadedROM& rom,
                               Taddress address__);
  
  /**
   * Reads a structure definition table.
   * @param data Raw data source.
   * @return The number of bytes of data read.
   */
  int readFromData(LoadedROM& rom,
                   Taddress address__);
  
  /**
   * Saves structure definitions to a string.
   * @param data String to hold data.
   */
  void save(std::string& data);
  
  /**
   * Loads structure definitions from a string.
   * @param data Byte array to load from.
   */
  int load(const Tbyte* data);
  
  /**
   * Exports structure definitions to ROM.
   * @param rom ROM to write to.
   */
  void exportToROM(WritableROM& rom);
  
  /**
   * Returns structure index of the given metatile number.
   * @return Structure index of the given metatile number.
   */
  int structureIndex(int metatileIndex);
  
  /**
   * Sets the structure index of the given metatile mapping.
   * @param metatileIndex Index of the metatile.
   * @param structureIndex New structure index.
   */
  void setStructureIndex(int metatileIndex, int structureIndex);
  
  /**
   * Returns number of index to structure definition mappings.
   * @return Number of index to structure definition mappings.
   */
  int numMetatileMappings() const;
  
  /**
   * Returns number of actual structure definitions.
   * @return Number of actual structure definitions.
   */
  int numStructureDefinitions() const;
  
  /**
   * Returns structure definition corresponding to the given tile.
   * @return Structure definition corresponding to the given tile.
   */
  MetatileStructure& metatileMapping(int indexNum);
  
  /**
   * Returns structure definition corresponding to the given tile.
   * @return Structure definition corresponding to the given tile.
   */
  const MetatileStructure& metatileMapping(int indexNum) const;
  
  /**
   * Returns iterator to start of primaryStorage_.
   * @return Iterator to start of primaryStorage_.
   */
  MetatileStructureCollection::iterator metatileStructuresBegin();
  
  /**
   * Returns iterator to end of primaryStorage_.
   * @return Iterator to end of primaryStorage_.
   */
  MetatileStructureCollection::iterator metatileStructuresEnd();
  
  /**
   * Returns const iterator to start of primaryStorage_.
   * @return Const iterator to start of primaryStorage_.
   */
  MetatileStructureCollection::const_iterator metatileStructuresCbegin() const;
  
  /**
   * Returns const iterator to end of primaryStorage_.
   * @return Const iterator to end of primaryStorage_.
   */
  MetatileStructureCollection::const_iterator metatileStructuresCend() const;
  
  /**
   * Returns table's source address, or export position after an export.
   * @return table's source address, or export position after an export.
   */
  Taddress address() const;
  
  /**
   * Returns structure definition corresponding to the given tile.
   * @return Structure definition corresponding to the given tile.
   */
  MetatileStructure& operator[](int tileNum);
  
  /**
   * Returns number of tile mappings defined (always 256).
   * @return Number of tile mappings defined (always 256).
   */
  int size() const;
  
protected:
  /**
   * Token indicating invalid structure pointer.
   */
  const static int invalidStructureToken = 0xFFFF;
  
  /**
   * An invalid structure address.
   */
  const static Taddress invalidAddress = 0x53600;
  
  /**
   * Base address of the space used to fill in the invalid structure tables.
   */
  const static Taddress invalidRepairAddress = 0x53800;
  
  /**
   * Tile number used to repair invalid structure table.
   */
  const static int invalidRepairTile = 0x0100;
  
  /**
   * Source/export address.
   */
  Taddress address_;
  
  /**
   * Primary storage for metatile structure definitions.
   */
  MetatileStructureCollection primaryStorage_;
  
  /**
   * Mapping of metatile index numbers to structure definition indices.
   */
  MetatileIndexToStructureMap index_;
  
};


};


#endif
