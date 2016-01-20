#ifndef EDITABLEWARPDESTINATIONS_H
#define EDITABLEWARPDESTINATIONS_H


#include "gamedata/BaseEditableMappedData.h"
#include "gamedata/TwoKeyEditableMappedData.h"
#include "gamedata/WarpDestination.h"
#include "gamegear/LoadedROM.h"
#include "gamegear/WritableROM.h"
#include "structs/Tbyte.h"
#include "structs/Taddress.h"
#include "structs/Tmap.h"
#include "structs/TwoKeyedAddress.h"
#include "structs/ConstSizeVector.h"
#include "structs/SaveHelper.h"
#include "structs/LoadHelper.h"
#include <string>
#include <vector>

namespace Tales {


typedef std::vector<WarpDestination> BaseWarpDestinationCollection;
typedef ConstSizeVector<WarpDestination> WarpDestinationCollection;

//typedef Tmap<Taddress, WarpDestinationCollection> AddressWarpsMap;
//typedef AddressWarpsMap::PairType AddressWarpsPair;

//typedef BaseEditableMappedData<WarpDestinationCollection,
//                               BaseWarpDestinationCollection>
//    BaseEditableWarpDestinations;

class EditableWarpDestinations
  : public TwoKeyEditableMappedData<WarpDestinationCollection,
                                 BaseWarpDestinationCollection> {
public:
  EditableWarpDestinations();
  
  EditableWarpDestinations(LoadedROM& rom,
                           Taddress tableHeaderAddress,
                           Taddress tableEndAddress);
               
  WarpDestinationCollection& warpsByMapnum(int primaryMapNum,
                                           int subMapNum);
protected:
  /**
   * The limit of valid primary keys (highest valid key plus one).
   * This table does not use the full data range, and does not work
   * if the full range is allowed.
   */
  const static int primaryMapLimit = 0x10;
  
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
  virtual int readElements(BaseWarpDestinationCollection& dst,
                           const Tbyte* data,
                           int numElements = 1);
  
  /**
   * Writes a T to a string.
   * @param data String to write to.
   * @param src T to write to data.
   */
  virtual void saveElement(std::string& data,
                           WarpDestinationCollection& src);
  
  /**
   * Reads an S from a previously saved byte array.
   * @param dst S to write to.
   * @param data Byte array to read from.
   */
  virtual int loadElement(BaseWarpDestinationCollection& dst,
                          const Tbyte* data);
  
  /**
   * Exports a T to ROM.
   * @param rom ROM to write to.
   * @param address Address in ROM to write to.
   * @param src T to write to ROM.
   */
  virtual void exportElementToROM(WritableROM& rom,
                                  Taddress address,
                                  WarpDestinationCollection& src);
  
  virtual DataChunkIDs::DataChunkID dataChunkID();
  
  virtual std::string dataChunkName();
  
  virtual int chunkVersionNumber();
  
  virtual int maxRecognizedVersionNumber();
  
};


};


#endif
