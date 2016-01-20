#include "structs/FreeSpaceListing.h"
#include "exception/TGenericException.h"
#include "util/StringConversion.h"
#include "gamegear/LoadedROM.h"
#include <string>

using namespace Luncheon;

namespace Tales {


FreeSpaceListing::FreeSpaceListing() { };

FreeSpaceListing::FreeSpaceListing(
                 const RawFreeSpacePair freeSpace[],
                 int freeSpaceLength) {
  for (int i = 0; i < freeSpaceLength; i++) {
    freeSpaceList_.push_back(FreeSpaceListPair(
      freeSpace[i].address,
      freeSpace[i].length));
  }
}

FreeSpaceList& FreeSpaceListing::freeSpaceList() {
  return freeSpaceList_;
}

const FreeSpaceList& FreeSpaceListing::freeSpaceList() const {
  return freeSpaceList_;
}

void FreeSpaceListing::claimSpace(
                FreeSpaceList::iterator& position,
                int length) {
  // Throw if trying to claim more space than exists
  if (length > position->length()) {
    throw TGenericException(TALES_SRCANDLINE,
                           "FreeSpaceListing::claimSpace("
                           "FreeSpaceList::iterator,int",
                           std::string("Tried to claim ")
                           + StringConversion::toString(length)
                           + std::string(" bytes at position ")
                           + StringConversion::toString(position->address())
                           + std::string(" when only ")
                           + StringConversion::toString(position->length())
                           + std::string(" were available"));
  }
  
  // Increase address
  position->setAddress(position->address() + length);
  
  // Decrease length
  position->setLength(position->length() - length);
  
  // If all space at this address is claimed, remove it from the list
  if (position->length() == 0) {
    freeSpaceList_.erase(position);
  }
}

void FreeSpaceListing::giveSpace(
                 int address,
                 int length) {
  // Check to see if we can add this space to an existing entry
  for (FreeSpaceList::iterator it = freeSpaceList_.begin();
       it != freeSpaceList_.end();
       it++) {
    // Ensure that we don't cross bank boundaries
    // (needs more thorough checking)
    if ((it->address() % LoadedROM::bankSize)) {
      // If this space comes exactly before an existing one,
      // modify the existing space with the new amount
      if (it->address() == address + length) {
        it->setAddress(address);
        it->setLength(it->length() + length);
        return;
      }
      // If this space comes exactly after an existing one,
      // modify the existing space with the new amount
      // as long as this would not cross a bank boundary
      else if ((address % LoadedROM::bankSize)
               && (it->address() + it->length() == address)) {
        it->setLength(it->length() + length);
        return;
      }
    }
  }
                 
  // No existing space found: add new entry
  freeSpaceList_.push_back(FreeSpaceListPair(address, length));
}

FreeSpaceList::iterator FreeSpaceListing::getFreeSpace(int length) {
  FreeSpaceList::iterator it = freeSpaceList_.begin();
  
  // Iterate over free space list until end is reached
  // or a sufficiently large space is found
  while ((it != freeSpaceList_.end())
         && (it->length() < length)) {
    it++;
  }
  
  // Return result, or freeSpaceList_.end() on failure
  return it;
}

FreeSpaceList::iterator FreeSpaceListing::getFreeSpace(
                                     int length,
                                     int low,
                                     int high) {
  FreeSpaceList::iterator it = freeSpaceList_.begin();
  
  while ((it != freeSpaceList_.end())) {
    if (it->address() >= high) {
      break;
    }
    
    if ((it->address() >= low)
        && (it->address() < high)
        && (it->length() >= length)) {
      return it;
    }
  
    it++;
  }
  
  return freeSpaceList_.end();
}


}; 
