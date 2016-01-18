#ifndef RAWFREESPACEPAIR_H
#define RAWFREESPACEPAIR_H


namespace Tales {


/**
 * Simple (address, length) pairs used for a FreeSpaceListing constructor.
 */
struct RawFreeSpacePair {
  int address;
  int length;
};


};


#endif 
