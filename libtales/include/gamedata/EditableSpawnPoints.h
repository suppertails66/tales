#ifndef EDITABLESPAWNPOINTS_H
#define EDITABLESPAWNPOINTS_H


#include "gamedata/BaseEditableMappedData.h"
#include "gamedata/TwoKeyEditableMappedData.h"
#include "gamedata/SpawnPoint.h"
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


typedef std::vector<SpawnPoint> BaseSpawnPointCollection;
typedef ConstSizeVector<SpawnPoint> SpawnPointCollection;

//typedef Tmap<Taddress, SpawnPointCollection> AddressSpawnsMap;
//typedef AddressSpawnsMap::PairType AddressSpawnsPair;

/**
 * Storage and access on Tails spawn points by (primary, sub) map number pairs.
 */
class EditableSpawnPoints
  : public TwoKeyEditableMappedData<SpawnPointCollection,
                                 BaseSpawnPointCollection> {
public:
  EditableSpawnPoints();
  
  EditableSpawnPoints(LoadedROM& rom,
                           Taddress tableHeaderAddress,
                           Taddress tableEndAddress);
               
  SpawnPointCollection& spawnsByMapnum(int primaryMapNum,
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
  virtual int readElements(BaseSpawnPointCollection& dst,
                           const Tbyte* data,
                           int numElements = 1);
  
  /**
   * Writes a T to a string.
   * @param data String to write to.
   * @param src T to write to data.
   */
  virtual void saveElement(std::string& data,
                           SpawnPointCollection& src);
  
  /**
   * Reads an S from a previously saved byte array.
   * @param dst S to write to.
   * @param data Byte array to read from.
   */
  virtual int loadElement(BaseSpawnPointCollection& dst,
                          const Tbyte* data);
  
  /**
   * Exports a T to ROM.
   * @param rom ROM to write to.
   * @param address Address in ROM to write to.
   * @param src T to write to ROM.
   */
  virtual void exportElementToROM(WritableROM& rom,
                                  Taddress address,
                                  SpawnPointCollection& src);
  
  virtual DataChunkIDs::DataChunkID dataChunkID();
  
  virtual std::string dataChunkName();
  
  virtual int chunkVersionNumber();
  
  virtual int maxRecognizedVersionNumber();
  
};


};


#endif
