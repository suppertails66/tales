#ifndef PALETTECYCLESTATE_H
#define PALETTECYCLESTATE_H


#include "structs/Tbyte.h"
#include "structs/Taddress.h"
#include "structs/Tmap.h"
#include "gamegear/GGColor.h"
#include <string>

namespace Tales {


typedef Tmap<int, GGColor> IndexToColorMap;

class PaletteCycleState {
public:
  /**
   * Default constructor.
   */
  PaletteCycleState();
  
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
   * @param startingColor Starting color index. The first read color
   * is placed at that index, the second at the next, and so on.
   * @param numColors Number of colors to read from source.
   * @return Number of bytes read.
   */
  int standardReadFromData(const Tbyte* data,
                           int startingColor,
                           int numColors);
  
  bool hasColor(int index);
  
  GGColor color(int index);
  
  void modifyColor(int index,
                const GGColor& color);
                
  void insertColor(int index,
                   const GGColor& color);
                   
  IndexToColorMap::const_iterator cbegin() const;
                   
  IndexToColorMap::const_iterator cend() const;
  
protected:
  
  IndexToColorMap colors_;
  
};


};


#endif
