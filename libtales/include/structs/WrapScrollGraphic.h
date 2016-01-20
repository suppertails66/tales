#ifndef WRAPSCROLLGRAPHIC_H
#define WRAPSCROLLGRAPHIC_H


#include "structs/Graphic.h"

namespace Tales {

class WrapScrollGraphic {
public:
  WrapScrollGraphic();
  
  WrapScrollGraphic(int w, int h);
  
  void scrollInX(int amount);
  void scrollInY(int amount);
  
  Graphic& surface();
  int offsetX() const;
  int offsetY() const;

  void blit(const Graphic& src,
            Box dstbox,
            Box srcbox,
            Graphic::TransBlitOption updateTrans = Graphic::transUpdate);

  void copy(const Graphic& src,
            Box dstbox,
            Box srcbox,
            Graphic::TransBlitOption updateTrans = Graphic::transUpdate);
  
protected:
  Graphic surface_;
  int offsetX_;
  int offsetY_;
};
  

};


#endif
