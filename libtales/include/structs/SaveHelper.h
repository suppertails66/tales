#ifndef SAVEHELPER_H
#define SAVEHELPER_H


#include "structs/Tbyte.h"
#include "structs/Taddress.h"
#include "structs/DataChunkID.h"
#include <string>

namespace Tales {


class SaveHelper {
public:
  /**
   * Constructor.
   * Writes the chunk header and saves necessary data for finalization.
   * @param data__ String to save to.
   * @param id ID of the chunk being saved.
   * @param version Version identifier for the chunk.
   */
  SaveHelper(std::string& data__,
             DataChunkIDs::DataChunkID id,
             int version);
  
  /**
   * Fills in length field of chunk header.
   * This should be called after writing all data to the string.
   */
  void finalize();
  
  /**
   * Saves a string to a string.
   */
  static void saveString(std::string& data,
                         const std::string& saveString);
  
protected:
  
  std::string& data_;
  
  int startPos_;
  
};


}


#endif
