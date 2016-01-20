#ifndef GRAPHICSCENELAYER_H
#define GRAPHICSCENELAYER_H


#include "structs/Graphic.h"
#include "structs/Box.h"

namespace Tales {


/**
 * A "layer" of a LayeredGraphicScene.
 * Layers can be rendered to a Graphic using render() and composited by
 * their containing LayeredGraphicScene into (a portion of) the full scene.
 * @see LayeredGraphicScene
 */
class GraphicSceneLayer {
public:
  /**
   * Default constructor.
   */
  GraphicSceneLayer();
  
  /**
   * Virtual destructor.
   */
  virtual ~GraphicSceneLayer();
  
  /**
   * Abstract function to render scene to a Graphic.
   * @param dst Graphic to render to. Existing contents are maintained. Must
   * be the same size as or larger than the area given by srcbox.
   * @param srcbox Box indicating the area of the layer to be
   * rendered to the Graphic.
   * @param scale Scaling factor indicating amount of zoom to apply to the
   * layer.
   */
  virtual void render(Graphic& dst,
                      Box srcbox,
                      double scale) =0;
                      
  bool visible() const;
  
  void setVisible(bool visible__);
protected:

  bool visible_;
  
};


};


#endif
