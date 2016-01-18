#ifndef GRAPHICTILEEDITORLAYER_H
#define GRAPHICTILEEDITORLAYER_H


#include "structs/GraphicSceneLayer.h"
#include "editors/GraphicsEditorToolManager.h"
#include "gamedata/EditableLevelGraphicsData.h"
#include "gamedata/EditableStandardPalettes.h"
#include "gamedata/EditableSpriteMappings.h"
#include "editors/GridGraphicSceneLayer.h"
#include "structs/InputEventData.h"

namespace Tales {


class GraphicTileEditorLayer : public GraphicSceneLayer {
public:
  GraphicTileEditorLayer(
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
  int nativeToIndex(int x, int y);
  int nativeToTileX(int x);
  int nativeToTileY(int y);
  int tileIndexToDrawX(int index);
  int tileIndexToDrawY(int index);
  
  void drawPencil(InputEventData eventData);
  
  const static int tilesPerRow_ = 16;
  
  GraphicsEditorToolManager* toolManager_;
  
  GridGraphicSceneLayer grid_;
  
  Graphic buffer_;
};


};


#endif
