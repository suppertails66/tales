#ifndef WRITABLEROM_H
#define WRITABLEROM_H


#include "gamegear/LoadedROM.h"
#include "structs/Tbyte.h"
#include "structs/FreeSpaceListing.h"
#include <string>

namespace Tales {


/**
 * A ROM that can be overwritten.
 */
class WritableROM {
public:
  /**
   * Constructor.
   * @param rom__ A LoadedROM to copy the base ROM data from.
   * @param freeSpace__ Listing of free space in the ROM.
   */
  WritableROM(const LoadedROM& rom__,
              const FreeSpaceListing& freeSpace__);
              
  /**
   * Copy constructor.
   * @param writableROM A WritableROM to copy data from.
   */
  WritableROM(const WritableROM& writableROM);
  
  /**
   * Copy assignment.
   * @param writableROM A WritableROM to copy data from.
   */
  WritableROM& operator=(const WritableROM& writableROM);
  
  /**
   * Destructor.
   */
  ~WritableROM();
  
  /**
   * Returns a writable pointer to the given ROM address.
   * Address is direct (i.e. unbanked).
   * @param address The direct address to write to.
   * @return A writable pointer to the given ROM address.
   */
  Tbyte* directWrite(int address);
  
  /**
   * Writes a block of data to the given ROM address.
   * Address is direct (i.e. unbanked).
   * @param address The direct address to write to.
   * @param src The source data to copy.
   * @param srclen The number of bytes to copy from src.
   */
  void directWrite(int address,
                   const Tbyte* src,
                   int srclen);
                   
  const Tbyte* directRead(int address) const;
  
  /**
   * Writes the ROM to a file.
   * @param filename The filename to which to write.
   */
  void writeToFile(const std::string& filename) const;
  
  /**
   * Increases the size of the ROM.
   * Unused space will be padded with 0xFF.
   * Decreasing ROM size is not allowed.
   * @param newSize The new size, in bytes, of the ROM data.
   */
  void expandROM(unsigned int newSize);
  
  /**
   * Doubles the size of the ROM, following the conventions of expandROM().
   * @see expandROM
   */
  void doubleROMSize();
  
  /**
   * Getter for romSize_.
   */
  int romSize() const;
  
  /**
   * Accessor for freeSpace_.
   */
  FreeSpaceListing& freeSpace();
  
  /**
   * Const accessor for freeSpace_.
   */
  const FreeSpaceListing& freeSpace() const;
   
protected:
  
  /**
   * The loaded ROM data.
   */
  Tbyte* rom_;
  
  /**
   * The size of the loaded ROM.
   */
  int romSize_;
  
  /**
   * Listing of free (unused) spaces in the ROM.
   */
  FreeSpaceListing freeSpace_;
  
};


};


#endif 
