#ifndef GENERICGRAPHICSCENEOBJECT_H
#define GENERICGRAPHICSCENEOBJECT_H


#include "structs/Graphic.h"

namespace Tales {


/**
 * Base class for a generic "graphic" in a GenericGraphicSceneLayer.
 * Derived classes can provide rendering of bitmaps, vector graphics, etc.
 */
class GenericGraphicSceneObject {
public:
  /**
   * Default constructor.
   */
  GenericGraphicSceneObject();
  
  GenericGraphicSceneObject(int x__,
                            int y__,
                            bool visible__);
  
  /**
   * Virtual destructor.
   */
  virtual ~GenericGraphicSceneObject();
  
  /**
   * Renders the object.
   * Abstract; derived classes provide implementation.
   * @param dst Graphic to render to. Existing contents are kept and used
   * as the background for the rendered object.
   * @param srcbox Area of the parent scene to be rendered. Used to compute
   * target coordinates in dst.
   * @param scale Scale to apply to object when rendering.
   */
  virtual void render(Graphic& dst,
                      Box srcbox,
                      double scale = 1.00) =0;
  
  /**
   * Getter.
   */
  int x() const;
  
  /**
   * Getter.
   */
  int y() const;
  
  /**
   * Getter.
   */
  bool visible() const;
  
  /**
   * Setter.
   */
  void setX(int x__);
  
  /**
   * Setter.
   */
  void setY(int y__);
  
  /**
   * Setter.
   */
  void setVisible(bool visible__);
  
protected:
  
  /**
   * X-coordinate of the object's centerpoint.
   */
  int x_;
  
  /**
   * Y-coordinate of the object's centerpoint.
   */
  int y_;
  
  /**
   * True if object is visible, false otherwise.
   */
  bool visible_;
  
};


};


#endif
