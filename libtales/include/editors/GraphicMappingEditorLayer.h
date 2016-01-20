#ifndef GRAPHICMAPPINGEDITORLAYER_H
#define GRAPHICMAPPINGEDITORLAYER_H


#include "structs/GraphicSceneLayer.h"
#include "editors/GraphicsEditorToolManager.h"
#include "editors/GridGraphicSceneLayer.h"
#include "structs/InputEventData.h"
#include "editors/ObjectDisplayCache.h"

namespace Tales {


class GraphicMappingEditorLayer : public GraphicSceneLayer {
public:
  GraphicMappingEditorLayer(
                 GraphicsEditorToolManager& toolManager__);
                 
  virtual void render(Graphic& dst,
      Box srcbox,
      double scale);
  
  void enterMouse();
  void exitMouse();
  void moveMouse(InputEventData eventData);
  void pressMouse(InputEventData eventData);
  void releaseMouse(InputEventData eventData);
  void doubleClickMouse(InputEventData eventData);
  
  int nativeWidth();
  int nativeHeight();
protected:
  int realToNative(int coordinate);
  void updatePencil(InputEventData eventData);
  void drawPencil(InputEventData eventData);
  void drawPencilPreview(Graphic& nativeBuf);
  
  GraphicsEditorToolManager* toolManager_;
  
  GridGraphicSceneLayer grid_;
  
  ObjectDisplayCache cache_;
  Graphic buffer_;
  
};


};


#endif
