#ifndef GENERICGRAPHICSCENELAYER_H
#define GENERICGRAPHICSCENELAYER_H


#include "structs/GraphicSceneLayer.h"
#include "structs/GenericGraphicSceneObject.h"
#include "structs/Graphic.h"
#include <vector>

namespace Tales {


/**
 * Contains and renders arbitrary GenericGraphicSceneObjects.
 * NOT COPY SAFE.
 */
class GenericGraphicSceneLayer : public GraphicSceneLayer {
public:
  /**
   * Default constructor.
   */
  GenericGraphicSceneLayer();
  
  /**
   * Destructor.
   */
  virtual ~GenericGraphicSceneLayer();
  
  virtual void render(Graphic& dst,
                      Box srcbox,
                      double scale = 1.00);
  
  /**
   * Renders the scene.
   * @param dst Graphic to render to. Existing contents are kept and used
   * as the background for the rendered graphics.
   * @param srcbox Box outlining the area to be rendered. Coordinates are
   * scene-local; they will be scaled as needed using the scale factors.
   * @param preScale Scale to apply to objects when rendering.
   * This scaling is done per-object, so a vector-based object, for example,
   * can be drawn without "blockiness".
   * @param postScale Scale to apply to the final result of the render.
   * This is performed independently of the preScale.
   */
  virtual void render(Graphic& dst,
                      Box srcbox,
                      double preScale = 1.00,
                      double postScale = 1.00);
                      
  virtual void addObject(GenericGraphicSceneObject* object);
                      
  virtual void clearObjects();
protected:
  typedef std::vector<GenericGraphicSceneObject*>
    GenericGraphicSceneObjectPointerCollection;
  
  GenericGraphicSceneObjectPointerCollection graphicPointers_;
};


};


#endif
