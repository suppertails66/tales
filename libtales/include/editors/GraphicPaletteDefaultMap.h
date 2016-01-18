#ifndef GRAPHICPALETTEDEFAULTMAP_H
#define GRAPHICPALETTEDEFAULTMAP_H


#include "structs/Tmap.h"


namespace Tales {


class GraphicPaletteDefaultEntry {
public:
  GraphicPaletteDefaultEntry();
  GraphicPaletteDefaultEntry(int paletteNum__);
  
  int paletteNum();
  void setPaletteNum(int paletteNum__);
protected:
  int paletteNum_;
};

typedef Tmap<int, GraphicPaletteDefaultEntry> GraphicPaletteDefaultMap;


};


#endif
