#ifndef EDITABLELEAFGRAPHICSTABLE_H
#define EDITABLELEAFGRAPHICSTABLE_H


#include "structs/Tbyte.h"
#include "structs/Taddress.h"
#include "gamegear/LoadedROM.h"
#include "gamegear/WritableROM.h"
#include <string>

namespace Tales {


/**
 * Storage for and access on VRAM tile indices of leaf graphics.
 * Leaf graphics are used for the "wind gust" effect used when trying to fly
 * through certain types of tiles. Each area has an entry in this table
 * indicating where in VRAM the leaf graphic is found for that area.
 */
class EditableLeafGraphicsTable {
public:
  const static int dataSize = 0xF;
  
  const static int numGraphicTiles = 4;

  /**
   * Default constructor.
   */
  EditableLeafGraphicsTable();
  
  /**
   * Constructor from ROM.
   * @param rom ROM to read from.
   * @param address Address of the table.
   */
  EditableLeafGraphicsTable(LoadedROM& rom,
                            Taddress address__);
                            
  int& entry(int index);
                            
  void save(std::string& data);
  
  int load(const Tbyte* data);
  
  void exportToROM(WritableROM& rom);
  
  int writeToData(Tbyte* data);
  
  int readFromData(const Tbyte* data);
  
protected:
  
  Taddress address_;
  
  int tableEntries[dataSize];
  
};


};


#endif
