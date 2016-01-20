#ifndef SPRITEMAPPINGCOORDINATETABLE_H
#define SPRITEMAPPINGCOORDINATETABLE_H


#include "structs/Tbyte.h"
#include "structs/Taddress.h"
#include "structs/Tmap.h"
#include "gamedata/SpriteMappingCoordinateTableEntry.h"
#include <vector>
#include <string>

namespace Tales {


class SpriteMappingCoordinateTable {
public:
  /**
   * Default constructor.
   */
  SpriteMappingCoordinateTable();
  
  /**
   * Constructor from raw data.
   * @param data Raw byte array to read from.
   * @param numSprites Number of sprites' worth of entries in the table.
   */
  SpriteMappingCoordinateTable(const Tbyte* data,
                               int numSprites);
                               
  int size() const;
  
  SpriteMappingCoordinateTableEntry& entry(int index);
  
  const SpriteMappingCoordinateTableEntry& entry(int index) const;
  
  /**
   * Saves to a string.
   * @param data String to save to.
   */
  void save(std::string& data);
  
  /**
   * Loads from raw data.
   * @param data Raw byte array to read from.
   * @return Number of bytes read.
   */
  int load(const Tbyte* data);
  
  /**
   * Reads from raw data.
   * @param data Raw byte array to read from.
   * @return Number of bytes read.
   */
  int readFromData(const Tbyte* data,
                   int numSprites);
  
  /**
   * Writes to data.
   * @param data Raw byte array to write to.
   * @return Number of bytes written.
   */
  int writeToData(Tbyte* data);
   
protected:

  typedef std::vector<SpriteMappingCoordinateTableEntry>
    SpriteMappingCoordinateTableEntryCollection;
  
  SpriteMappingCoordinateTableEntryCollection spriteCoordinates_;
  
};


};


#endif
