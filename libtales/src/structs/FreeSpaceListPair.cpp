#include "structs/FreeSpaceListPair.h"


namespace Tales {


FreeSpaceListPair::FreeSpaceListPair()
  : address_(0),
    length_(0) { };

FreeSpaceListPair::FreeSpaceListPair(int address__, int length__)
  : address_(address__),
    length_(length__) { };

int FreeSpaceListPair::address() const {
  return address_;
}

int FreeSpaceListPair::length() const {
  return length_;
}

void FreeSpaceListPair::setAddress(int address__) {
  address_ = address__;
}

void FreeSpaceListPair::setLength(int length__) {
  length_ = length__;
}


};
