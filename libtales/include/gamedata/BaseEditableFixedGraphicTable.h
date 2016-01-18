#ifndef BASEEDITABLEFIXEDGRAPHICTABLE_H
#define BASEEDITABLEFIXEDGRAPHICTABLE_H


#include "structs/Tbyte.h"
#include "structs/Taddress.h"
#include "structs/TwoKeyedData.h"
#include "structs/TwoKeyedAddress.h"
#include "gamegear/LoadedROM.h"
#include "gamegear/WritableROM.h"
#include "structs/DataChunkID.h"
#include "structs/KeyedTableBuilder.h"
#include "structs/SaveHelper.h"
#include "structs/LoadHelper.h"
#include "gamedata/FixedGraphicTableEntry.h"
#include <string>

namespace Tales {


//template <class T>
class BaseEditableFixedGraphicTable {
public:

  /** 
   * Returns the DataChunkID of the object.
   */
  virtual DataChunkIDs::DataChunkID dataChunkID() =0;

  /** 
   * Returns the version number of the object.
   */
  virtual int version() =0;

  /** 
   * Returns the maximum loadable version number of the object.
   */
  virtual int maxVersion() =0;
  
  /**
   * Default constructor.
   */
  BaseEditableFixedGraphicTable();
  
  /**
   * Constructor from ROM.
   * @param rom ROM to read from.
   */
  BaseEditableFixedGraphicTable(LoadedROM& rom,
                                Taddress tableStart__,
                                const int subKeyTable[],
                                int numPrimaryKeys);
  
  void save(std::string& data);
  
  int load(const Tbyte* data);
  
  void exportToROM(WritableROM& rom);
  
  FixedGraphicTableEntry& entry(int areaNum,
                               int mapNum);
  
protected:

  typedef TwoKeyedData<FixedGraphicTableEntry> FixedGraphicTableKeyMap;

  /**
   * Address of the start of the table.
   */
//  Taddress tableStart_;

  /**
   * Address of the start of the table content.
   */
//  Taddress tableContentStart_;
  
  /**
   * Mapping of map numbers to their corresponding entry.
   */
  TwoKeyedAddress mapnumToAddress_;
  
  /**
   * Mapping of map numbers to their corresponding data.
   */
  FixedGraphicTableKeyMap mapnumToData_;
  
};


};


#endif
