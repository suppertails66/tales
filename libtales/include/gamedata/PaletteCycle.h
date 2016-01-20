#ifndef PALETTECYCLE_H
#define PALETTECYCLE_H


#include "structs/Tbyte.h"
#include "structs/Taddress.h"
#include "structs/Tmap.h"
#include "gamedata/PaletteCycleState.h"
#include <vector>
#include <string>

namespace Tales {


typedef std::vector<PaletteCycleState> PaletteCycleStateCollection;

class PaletteCycle {
public:
  /**
   * Default constructor.
   */
  PaletteCycle();
  
  void save(std::string& data);
  
  int load(const Tbyte* data);
  
  /**
   * Writes raw data in a standard format.
   * @param data Raw data to write to.
   * @return Number of bytes written.
   */
  int standardWriteToData(Tbyte* data);
  
  /**
   * Reads raw data in a standard format.
   * @param data Raw data to read from.
   * @param baseIndex Index of the lowest color. Each subsequent color is
   * assigned a sequentially higher index.
   * @param numColors Number of colors per state.
   * @param numStates Number of states to read.
   * @return Number of bytes read.
   */
  int standardReadFromData(const Tbyte* data,
                           int baseIndex,
                           int numColors,
                           int numStates);
  
  int numStates() const;
  
  PaletteCycleState& state(int index);
  
  void addState(const PaletteCycleState& state);
protected:
  
  PaletteCycleStateCollection states_;
  
};


};


#endif
