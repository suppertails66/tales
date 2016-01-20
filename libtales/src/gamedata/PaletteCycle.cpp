#include "gamedata/PaletteCycle.h"
#include "exception/OutOfRangeIndexException.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"
#include <iostream>

using namespace Luncheon;

namespace Tales {


PaletteCycle::PaletteCycle() { };

void PaletteCycle::save(std::string& data) {
  Tbyte buffer[ByteSizes::uint32Size];
  
  ByteConversion::toBytes(states_.size(),
                          buffer,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  data += std::string((char*)buffer, ByteSizes::uint16Size);
  
  for (PaletteCycleStateCollection::iterator it = states_.begin();
       it != states_.end();
       ++it) {
    it->save(data);
  }
}
  
int PaletteCycle::load(const Tbyte* data) {
  states_.clear();
  int byteCount = 0;
  
  int numStates = ByteConversion::fromBytes(
                          data + byteCount,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  byteCount += ByteSizes::uint16Size;
  
  for (int i = 0; i < numStates; i++) {
    PaletteCycleState state;
    byteCount += state.load(data + byteCount);
    states_.push_back(state);
  }
  
  return byteCount;
}

int PaletteCycle::standardWriteToData(Tbyte* data) {
  int byteCount = 0;
  
  for (PaletteCycleStateCollection::iterator it = states_.begin();
       it != states_.end();
       ++it) {
    byteCount += it->standardWriteToData(data + byteCount);
  }
  
  return byteCount;
}

int PaletteCycle::standardReadFromData(const Tbyte* data,
                                       int baseIndex,
                                       int numColors,
                                       int numStates) {
  int byteCount = 0;
  
  for (int i = 0; i < numStates; i++) {
    PaletteCycleState state;
    byteCount += state.standardReadFromData(data + byteCount,
                                            baseIndex,
                                            numColors);
    
    states_.push_back(state);
  }
  
  return byteCount;
}

int PaletteCycle::numStates() const {
  return states_.size();
}

PaletteCycleState& PaletteCycle::state(int index) {
  if (index >= states_.size()) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "PaletteCycle::state(int)",
                                   index);
  }
  
  return states_[index];
}

void PaletteCycle::addState(const PaletteCycleState& state) {
  states_.push_back(state);
}


};
