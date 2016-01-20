#ifndef GRIDGRAPHICSCENELAYER_H
#define GRIDGRAPHICSCENELAYER_H


#include "structs/GraphicSceneLayer.h"
#include "structs/Color.h"

namespace Tales {


class GridGraphicSceneLayer : public GraphicSceneLayer {
public:
  GridGraphicSceneLayer();
  
  GridGraphicSceneLayer(int lineSpacing__,
                        int lineWidth__ = 1,
                        Color color__ = Color(0, 0, 0,
                                              Color::fullAlphaOpacity),
                        bool enlargeOnZoom__ = false);
                        
  virtual void render(Graphic& dst,
                      Box srcbox,
                      double scale);
  
  int lineSpacing() const;
  
  int lineWidth() const;
  
  Color color() const;
  
  bool enlargeOnZoom() const;
  
  void setLineSpacing(int lineSpacing__);
  
  void setLineWidth(int lineWidth__);
  
  void setColor(Color color__);
  
  void setEnlargeOnZoom(bool enlargeOnZoom__);
  
  void setXLimit(int xLimit__);
  void setYLimit(int yLimit__);
  
protected:
  
  int lineSpacing_;
  
  int lineWidth_;
  
  Color color_;
  
  bool enlargeOnZoom_;
  
  int xLimit_;
  int yLimit_;
  
};


};


#endif
