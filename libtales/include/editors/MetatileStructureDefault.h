#ifndef METATILESTRUCTUREDEFAULT_H
#define METATILESTRUCTUREDEFAULT_H


namespace Tales {


struct MetatileStructureDefault {
  MetatileStructureDefault();
  MetatileStructureDefault(int graphicIndex__,
                           int paletteIndex__,
                           int palette1Index__);

  int graphicIndex_;
  int paletteIndex_;
  int palette1Index_;
};


};


#endif
