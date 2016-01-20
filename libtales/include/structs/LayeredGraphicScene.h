#ifndef LAYEREDGRAPHICSCENE_H
#define LAYEREDGRAPHICSCENE_H


#include "structs/Box.h"
#include "structs/Graphic.h"

namespace Tales {


/**
 * A visible "scene" that can be partially or wholly rendered to a Graphic.
 * A "scene" consists of zero or more GraphicSceneLayers that can be rendered
 * to a Graphic and composited to form an image representing the modelled
 * scene. This composite image can be generated using the render() function.
 * This is an abstract base; details of updating and rendering the scene
 * must be provided by derived classes.
 * @see GraphicSceneLayer
 */
class LayeredGraphicScene {
public:
  /**
   * Default constructor.
   */
  LayeredGraphicScene();
  
  /**
   * Virtual destructor.
   */
  virtual ~LayeredGraphicScene();
  
  /**
   * Abstract function to render scene to a Graphic.
   * @param dst Graphic to render to. Existing contents are discarded.
   * @param srcbox Box indicating the area of the contained Scene to be
   * rendered to the Graphic.
   * @param scale Scaling factor indicating amount of zoom to apply to the
   * scene.
   */
  virtual void render(Graphic& dst,
                      Box srcbox,
                      double scale) =0;
              
protected:
  
};


};


#endif
