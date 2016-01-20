#ifndef EDITABLELEVELPALETTEHEADERS_H
#define EDITABLELEVELPALETTEHEADERS_H


#include "gamedata/LevelPaletteHeader.h"
#include "gamegear/LoadedROM.h"
#include "gamegear/WritableROM.h"
#include "structs/Tbyte.h"
#include "structs/Taddress.h"
#include "structs/TwoKeyedAddress.h"
#include "structs/SaveHelper.h"
#include "structs/LoadHelper.h"
#include <string>
#include <vector>

namespace Tales {


typedef std::vector<LevelPaletteHeader> LevelPaletteHeaderCollection;

class EditableLevelPaletteHeaders {
public:
  
  /**
   * Default constructor.
   */
  EditableLevelPaletteHeaders();
  
  /**
   * Constructor from ROM data.
   * @param rom ROM to load from.
   * @param tableHeaderAddress__ Base address of the table header.
   * @param tableContentAddress__ Base address of the table content.
   * @param subKeyTable Table of subkeys for address map.
   * @param numPrimaryKeys Number of primary keys for address map.
   */
  EditableLevelPaletteHeaders(LoadedROM& rom,
                              Taddress tableHeaderAddress__,
                              Taddress tableContentAddress__,
                              int numContentEntries,
                              const int subKeyTable[],
                              int numPrimaryKeys);
  
  /**
   * Saves to a string.
   * @param data String to save to.
   */
  void save(std::string& data);
  
  /**
   * Loads from data.
   * @param data Byte array to read from.
   * @return Number of bytes read.
   */
  int load(const Tbyte* data);
  
  /**
   * Exports to ROM as raw data.
   * @param rom ROM to write to.
   */
  void exportToROM(WritableROM& rom);
  
  /**
   * Returns the number of loaded headers.
   * @return The number of loaded headers.
   */
  int size();
  
  /**
   * Returns the index of a particular primary/submap pair.
   * @param primaryNum The primary map number.
   * @param subNum The submap number.
   * @return The index of a particular primary/submap pair.
   */
  int indexOfMapNum(int primaryNum,
                    int subNum);
  
  /**
   * Sets the header index for a particular primary/submap pair.
   * @param primaryNum The primary map number.
   * @param subNum The submap number.
   * @param index The index to set to.
   */
  void setIndexOfMapNum(int primaryNum,
                        int subNum,
                        int index);
  
  /**
   * Access the header at a particular index.
   * @param index The index to access.
   * @return Reference to the corresponding header.
   */
  LevelPaletteHeader& headerByIndex(int index);
  
protected:
  
  /**
   * Primary storage for palette headers.
   */
  LevelPaletteHeaderCollection primaryStorage_;
  
  /**
   * Association of map numbers with primary storage indices.
   */
  TwoKeyedAddress mapnumToIndex_;
  
  /**
   * Base address of the table header.
   */
  Taddress tableHeaderAddress_;
  
  /**
   * Base address of the table content.
   */
  Taddress tableContentAddress_;
  
};


};


#endif
