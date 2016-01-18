#ifndef GRAPHICSEDITORSCENE_H
#define GRAPHICSEDITORSCENE_H


#include "structs/LayeredGraphicScene.h"
#include "editors/GraphicsEditorToolManager.h"
#include "gamedata/EditableLevelGraphicsData.h"
#include "gamedata/EditableStandardPalettes.h"
#include "gamedata/EditableSpriteMappings.h"
#include "editors/GraphicTileEditorLayer.h"
#include "editors/GraphicMappingEditorLayer.h"
#include "structs/InputEventData.h"

namespace Tales {


class GraphicsEditorScene : public LayeredGraphicScene {
public:
  GraphicsEditorScene(
                 EditableLevelGraphicsData& levelGraphicsData__,
                 EditableStandardPalettes& palettes__,
                 EditableSpriteMappings& spriteMappings__,
                 GraphicsEditorToolManager& toolManager__);
                 
  virtual void render(Graphic& dst,
      Box srcbox,
      double scale);
                 
  virtual void renderTileLayer(Graphic& dst,
      Box srcbox,
      double scale);
                 
  virtual void renderMappingLayer(Graphic& dst,
      Box srcbox,
      double scale);
  
  void tileEditorEnterMouse();
  void tileEditorExitMouse();
  void tileEditorMoveMouse(InputEventData eventData);
  void tileEditorPressMouse(InputEventData eventData);
  void tileEditorReleaseMouse(InputEventData eventData);
  void tileEditorDoubleClickMouse(InputEventData eventData);
  
  void mappingEditorEnterMouse();
  void mappingEditorExitMouse();
  void mappingEditorMoveMouse(InputEventData eventData);
  void mappingEditorPressMouse(InputEventData eventData);
  void mappingEditorReleaseMouse(InputEventData eventData);
  void mappingEditorDoubleClickMouse(InputEventData eventData);
      
  int nativeTileLayerWidth();
  int nativeTileLayerHeight();
  int nativeMappingLayerWidth();
  int nativeMappingLayerHeight();
protected:
  EditableLevelGraphicsData* levelGraphicsData_;
  EditableStandardPalettes* palettes_;
  EditableSpriteMappings* spriteMappings_;
  GraphicsEditorToolManager* toolManager_;
  
  GraphicTileEditorLayer tileEditorLayer_;
  GraphicMappingEditorLayer mappingEditorLayer_;
};


};


#endif
