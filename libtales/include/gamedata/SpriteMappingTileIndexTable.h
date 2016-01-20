#ifndef SPRITEMAPPINGTILEINDEXTABLE_H
#define SPRITEMAPPINGTILEINDEXTABLE_H


#include "structs/Tbyte.h"
#include "structs/Taddress.h"
#include <vector>
#include <string>

namespace Tales {


class SpriteMappingTileIndexTable {
public:
  /**
   * Default constructor.
   */
  SpriteMappingTileIndexTable();
  
  /**
   * Constructor from raw data.
   * @param data Raw byte array to read from.
   * @param numSprites Number of sprites' worth of data to read.
   */
  SpriteMappingTileIndexTable(const Tbyte* data,
                              int numSprites);
  
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
  
  /**
   * Returns number of contained indices.
   * @return Number of contained indices.
   */
  int size() const;
  
  /**
   * Returns the tile index at the given position.
   * @param index Index position.
   * @returns The tile index at the given position.
   */
  int& tileIndex(int index);
  
  /**
   * Returns const reference to the tile index at the given position.
   * @param index Index position.
   * @returns Const reference to the tile index at the given position.
   */
  const int& tileIndex(int index) const;
protected:

  typedef std::vector<int> TileIndexTable;
  
  TileIndexTable tileIndices_;
  
};


};


#endif
