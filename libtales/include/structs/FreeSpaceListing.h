#ifndef FREESPACELISTING
#define FREESPACELISTING


#include <list>
#include "structs/FreeSpaceListPair.h"
#include "structs/RawFreeSpacePair.h"

namespace Tales {


typedef std::list<FreeSpaceListPair> FreeSpaceList;

/**
 * A listing of unused space in the form of (address, length) pairs.
 */
class FreeSpaceListing {
public:
  /**
   * Default constructor.
   * Initializes free space list to empty.
   */
  FreeSpaceListing();
  
  /**
   * Constructor from existing free space.
   * @param freeSpace An array of RawFreeSpacePairs specifying the existing
   * free space.
   * @param freeSpaceLength The number of entries in freeSpace.
   */
  FreeSpaceListing(const RawFreeSpacePair freeSpace[],
                   int freeSpaceLength);
  
  /**
   * Accessor for freeSpaceList_.
   */
  FreeSpaceList& freeSpaceList();
  
  /**
   * Const accessor for freeSpaceList_.
   */
  const FreeSpaceList& freeSpaceList() const;
  
  /**
   * Claims space from the free space list.
   * @param position A FreeSpaceList::iterator pointing to the pair from which
   * to claim space.
   * @param length The number of bytes to claim.
   */
  void claimSpace(FreeSpaceList::iterator& position,
                  int length);
  
  /**
   * Adds new space to the free space list.
   * Doesn't defragment or check that the incoming space doesn't overlap
   * with an existing entry.
   * @param address The starting address of the new free space.
   * @param length The number of bytes to return.
   */
  void giveSpace(int address,
                   int length);
                   
  /**
   * Attempts to find a free chunk of the specified size.
   * If no chunk that can fit the requested amount is found, an iterator
   * pointing to freeSpaceList_.end() will be returned instead.
   * @param length The number of bytes of data needed.
   */
  FreeSpaceList::iterator getFreeSpace(int length);
                   
  /**
   * Attempts to find a free chunk of the specified size in the given range.
   * @param length The number of bytes of data needed.
   * @param low Minimum number (inclusive) to search for.
   * @param high Maximum number (exclusive) to search for.
   */
  FreeSpaceList::iterator getFreeSpace(int length,
                                       int low,
                                       int high);
  
protected:
  
  /**
   * The (address, length) free space list pairs.
   */
  FreeSpaceList freeSpaceList_;
  
};


};


#endif 
