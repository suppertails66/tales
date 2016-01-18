#ifndef TALESDATA_H
#define TALESDATA_H


#include <string>
#include "gamedata/TailsAdvData.h"
#include "gamegear/LoadedROM.h"

namespace Tales {


/**
 * Primary class for initializing and using libtales.
 * Instantiating an instance of this object requires a clean Tails Adventures
 * ROM (a modified file may also be used with appropriate constructor
 * parameters). The constructor loads all necessary data from this file for
 * future use. The editor functions may then be used to manipulate the game
 * data, and the serialization functions to save and load projects and export
 * modified data to a ROM file.
 */
class TailsAdvROMLoader {
public:

  /**
   * The MD5 sum of a clean Tails Adventures ROM.
   * The only known version of the game was released globally.
   */
  const static char* expectedCleanRomMD5Base64;
  
  /**
   * Verifies that a file is a clean Tails Adventures ROM. If
   * throwIfFileInvalid is true, an InvalidFileException will be thrown
   * if the file's hash does not match the expected value; otherwise,
   * the program will attempt to read the data anyway.
   * @param romPath Path to a clean Tails Adventures ROM.
   * @param throwIfFileInvalid If true, an InvalidFileException will be thrown
   * if the specified file's hash does not match the expected value; if false,
   * the program will attempt to read the data anyway. Defaults to true.
   * @returns True if the file is valid.
   * @throws FileNotFoundException
   * @throws InvalidFileException
   */
  static bool checkROM(const std::string& romPath,
                       bool throwIfFileInvalid = true);
  
protected:
  
};


};


#endif 
