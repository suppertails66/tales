#ifndef SPRITEMAPPINGCOORDINATETABLEENTRY_H
#define SPRITEMAPPINGCOORDINATETABLEENTRY_H


#include "structs/Tbyte.h"
#include "structs/Taddress.h"
#include "structs/Tmap.h"

namespace Tales {


class SpriteMappingCoordinateTableEntry {
public:
  /**
   * Size in bytes of raw data representation.
   */
  const static int dataSize = 4;

  /**
   * Default constructor.
   */
  SpriteMappingCoordinateTableEntry();
  
  /**
   * Constructor from raw data.
   * @param data Raw byte array to load from.
   */
  SpriteMappingCoordinateTableEntry(const Tbyte* data);
  
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
  int readFromData(const Tbyte* data);
  
  /**
   * Writes to data.
   * @param data Raw byte array to write to.
   * @return Number of bytes written.
   */
  int writeToData(Tbyte* data);
  
  /**
   * Getter.
   */
  int offsetY() const;
  
  /**
   * Getter.
   */
  int offsetX() const;
  
  /**
   * Setter.
   */
  void setOffsetY(int offsetY__);
  
  /**
   * Setter.
   */
  void setOffsetX(int offsetX__);
protected:
  
  int offsetY_;
  
  int offsetX_;
  
};


};


#endif
