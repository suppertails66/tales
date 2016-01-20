#ifndef TAILSADVFREESPACE_H
#define TAILSADVFREESPACE_H


#include "structs/RawFreeSpacePair.h"

namespace Tales {


/**
 * Container for an array of free space pairs for a clean Tails Adventures ROM.
 */
class TailsAdvFreeSpace {
public:
  /**
   * The number of pairs in the array.
   */
  const static int numFreeSpacePairs = 17;

  /**
   * The free space (address, length) pairs.
   * Includes only runs of 256 bytes or more of 0xFF.
   */
  const static RawFreeSpacePair freeSpace[];
};


};


#endif 
