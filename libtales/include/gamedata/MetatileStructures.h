#ifndef METATILESTRUCTURES_H
#define METATILESTRUCTURES_H


#include "gamedata/MetatileStructure.h"
#include "gamedata/MetatileStructureSet.h"
#include "gamedata/RawLevelHeaders.h"
#include "gamegear/LoadedROM.h"
#include "gamegear/WritableROM.h"
#include "structs/Tmap.h"
#include "structs/Taddress.h"
#include "structs/Tbyte.h"
#include <utility>
#include <string>
#include <vector>


namespace Tales {



typedef std::vector<MetatileStructureSet>
  MetatileStructureTableCollection;
  
typedef Tmap<Taddress, int> AddressMetatileStructureIndexMap;
typedef std::pair<Taddress, int> AddressMetatileStructureIndexPair;

class MetatileStructures {
public:
  /**
   * Number of metatile definitions in a metatile table.
   */
  const static int numMetatilesPerTable = 0x100;
  
  /**
   * Number of bytes per metatile definition.
   */
  const static int bytesPerMetatile = 8;

  /**
   * Default constructor.
   */
  MetatileStructures();
  
  /**
   * Constructor from raw level headers.
   */
  MetatileStructures(LoadedROM& rom,
                             const RawLevelHeaders& rawLevelHeaders);

  /**
   * Returns the index associated with a metatile structure table address.
   * @return The index associated with a metatile structure table address.
   */
  int indexOfAddress(Taddress address) const;

  /**
   * Returns a reference to the metatile structure set of an index.
   * @return A reference to the metatile structure set of an index.
   */
  MetatileStructureSet& metatileStructureSet(int index);

  /**
   * Returns a const reference to the metatile structure set of an index.
   * @return A const reference to the metatile structure set of an index.
   */
  const MetatileStructureSet& metatileStructureSet(int index) const;
  
  /**
   * Saves to a string.
   * @param data String to write to.
   */
  void save(std::string& data);
  
  /**
   * Loads from data.
   * @param data Data to load.
   * @return Number of bytes of data read.
   */
  int load(const Tbyte* data);
  
  /**
   * Exports metatile structure tables to ROM.
   * @param rom ROM to write to.
   */
  void exportToROM(WritableROM& rom);
  
  /**
   * Returns the index associated with a given initial address.
   * Only for initial ROM load.
   * @param address Address to get index of.
   * @return The index corresponding to the given address.
   */
  int indexOfInitialAddress(Taddress initialAddress) const;
  
  /**
   * Returns the number of contained MetatileStructureSets.
   * @return The number of contained MetatileStructureSets.
   */
  int size() const;
  
protected:
  
  /**
   * An invalid address used in the headers for the world map and Tails' House.
   */
  const static Taddress invalidTableAddress = 0x53600;
  
  /**
   * Replacement address for invalidTableAddress.
   * We need to move the table back in order to fit in the added
   * metatile definitions.
   */
//  const static Taddress invalidTableRepairAddress = 0x53600;

  /**
   * Map of metatile structure table addresses to indices.
   */
  AddressMetatileStructureIndexMap indexMap_;
  
  /**
   * Primary storage for MetatileStructureSets.
   */
  MetatileStructureTableCollection
    metatileStructureSets_;
  
};


};


#endif 
