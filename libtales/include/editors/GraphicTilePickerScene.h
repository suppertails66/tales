#ifndef GRAPHICTILEPICKERSCENE_H
#define GRAPHICTILEPICKERSCENE_H


#include "editors/IndexedPickerScene.h"
#include "editors/TileMapEditorToolManager.h"
#include "gamegear/GGTileSet.h"
#include "gamegear/GGPalette.h"

namespace Tales {


class GraphicTilePickerScene : public IndexedPickerScene {
public:
  GraphicTilePickerScene();
  
  GraphicTilePickerScene(TileMapEditorToolManager& toolManager__,
                         GGTileSet& graphic__,
                         GGPalette& palette__,
                         int offset__);
  
  virtual void renderNative(Graphic& dst,
                            Box srcbox);
  
  virtual void enterMouse();
  virtual void exitMouse();
  virtual void moveMouse(InputEventData eventData);
  virtual void pressMouse(InputEventData eventData);
  virtual void releaseMouse(InputEventData eventData);
  virtual void doubleClickMouse(InputEventData eventData);
                            
  int nativeW();
  int nativeH();
protected:
  const static int tilesPerRow_ = 16;

  TileMapEditorToolManager* toolManager_;
  GGTileSet* graphic_;
  GGPalette* palette_;
  int offset_;
  
};


};


#endif
