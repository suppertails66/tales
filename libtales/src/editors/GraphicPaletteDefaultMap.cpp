#include "editors/GraphicPaletteDefaultMap.h"

namespace Tales {


GraphicPaletteDefaultEntry::GraphicPaletteDefaultEntry()
  : paletteNum_(0) { };
  
GraphicPaletteDefaultEntry::GraphicPaletteDefaultEntry(int paletteNum__)
  : paletteNum_(paletteNum__) { };
  
int GraphicPaletteDefaultEntry::paletteNum() {
  return paletteNum_;
}

void GraphicPaletteDefaultEntry::setPaletteNum(int paletteNum__) {
  paletteNum_ = paletteNum__;
}


};
