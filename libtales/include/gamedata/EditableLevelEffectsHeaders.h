#ifndef EDITABLELEVELEFFECTSHEADERS_H
#define EDITABLELEVELEFFECTSHEADERS_H


#include "gamedata/LevelEffectsHeader.h"
#include "gamedata/TwoKeyEditableMappedData.h"
#include "gamedata/TwoKeyIndexedEditableMappedData.h"
#include "gamegear/LoadedROM.h"
#include "structs/Tbyte.h"
#include "structs/Taddress.h"
#include "gamedata/PrimaryMaps.h"
#include "gamedata/SubMaps.h"
#include "structs/SaveHelper.h"
#include "structs/LoadHelper.h"

namespace Tales {


class EditableLevelEffectsHeaders
    : public TwoKeyIndexedEditableMappedData<LevelEffectsHeader> {
public:
  const static int primaryMapLimit = PrimaryMaps::primaryMapTableSize;

  /**
   * Default constructor.
   */
  EditableLevelEffectsHeaders();
  
  EditableLevelEffectsHeaders(LoadedROM& rom,
                           Taddress tableHeaderAddress,
                           Taddress tableContentAddress,
                           Taddress tableEndAddress,
                           int numEntries);
  
//  virtual void prepareIndices();
               
  LevelEffectsHeader& headersByMapnum(int primaryMapNum,
                                      int subMapNum);
  
protected:

  /**
   * Returns the data size of a single storage element.
   */
  virtual int dataSizeOfOneElement();
  
  /**
   * Reads (numElements) instances of an S from data and stores in dst.
   * @param dst S in which to place read data.
   * @param data Raw data source.
   * @param numElements Number of elements to read from data. Default is 1.
   * @return Number of bytes of data read.
   */
  virtual int readElements(LevelEffectsHeader& dst,
                           const Tbyte* data,
                           int numElements = 1);
  
  /**
   * Writes a T to a string.
   * @param data String to write to.
   * @param src T to write to data.
   */
  virtual void saveElement(std::string& data,
                           LevelEffectsHeader& src);
  
  /**
   * Reads an S from a previously saved byte array.
   * @param dst S to write to.
   * @param data Byte array to read from.
   */
  virtual int loadElement(LevelEffectsHeader& dst,
                          const Tbyte* data);
  
  /**
   * Exports a T to ROM.
   * @param rom ROM to write to.
   * @param address Address in ROM to write to.
   * @param src T to write to ROM.
   */
  virtual void exportElementToROM(WritableROM& rom,
                                  Taddress address,
                                  LevelEffectsHeader& src);
  
  virtual DataChunkIDs::DataChunkID dataChunkID();
  
  virtual std::string dataChunkName();
  
  virtual int chunkVersionNumber();
  
  virtual int maxRecognizedVersionNumber();
                                  
  /**
   * Reads the address table.
   * Default implementation is for "standard" arrangement of two tables,
   * the first one indexing into the second and the second indexing into
   * the table containing the actual content.
   * @param rom ROM to read from.
   * @param tableHeaderAddress Address of the header table.
   */
//  virtual void readAddressTable(LoadedROM& rom,
//                                Taddress tableHeaderAddress);
  
  /**
   * Maps read addresses to indices and stores.
   * Should modify addressToIndex_ and primaryStorage_.
   */
//  virtual void prepareIndices();

  /**
   * This should be called in derived classes' constructors.
   */
//  virtual void readAllDataAndConstruct(LoadedROM& rom,
//                        Taddress tableHeaderAddress,
//                        Taddress tableContentAddress,
//                        Taddress tableEndAddress,
//                        int numEntries);
  
};


};


#endif
