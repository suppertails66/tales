#ifndef LEVELPALETTEHEADER_H
#define LEVELPALETTEHEADER_H


#include "structs/Tbyte.h"
#include "structs/Taddress.h"
#include "gamegear/LoadedROM.h"
#include "gamegear/WritableROM.h"
#include <string>

namespace Tales {


/**
 * Storage for a pair of palette entry indices for a level.
 */
class LevelPaletteHeader {
public:
  /**
   * Size in bytes of a raw header.
   */
  const static int dataSize = 2;
  
  /**
   * Default constructor.
   */
  LevelPaletteHeader();
  
  /**
   * Constructor from palette values.
   * @param palette0Index__ Index of the first palette.
   * @param palette1Index__ Index of the second palette.
   */
  LevelPaletteHeader(int palette0Index__,
                     int palette1Index__);
  
  /**
   * Constructor from data.
   * @param data Byte array to read from.
   */
  LevelPaletteHeader(const Tbyte* data);
  
  /**
   * Reads header from data.
   * @param data Byte array to read from.
   * @return Number of bytes read.
   */
  int readFromData(const Tbyte* data);
  
  /**
   * Writes header to data.
   * @param data Byte array to write to.
   * @return Number of bytes written.
   */
  int writeToData(Tbyte* data);
  
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
   * @param address Address to write data to.
   */
  void exportToROM(WritableROM& rom,
                   Taddress address);
  
  /**
   * Getter.
   */
  int palette0Index();
  
  /**
   * Getter.
   */
  int palette1Index();
  
  /**
   * Setter.
   */
  void setPalette0Index(int palette0Index__);
  
  /**
   * Setter.
   */
  void setPalette1Index(int palette1Index__);
  
protected:

  /**
   * Index of the first palette.
   */
  int palette0Index_;
  
  /**
   * Index of the second palette.
   */
  int palette1Index_;
  
};


};


#endif
