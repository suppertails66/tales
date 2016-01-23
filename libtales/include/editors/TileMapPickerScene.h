#ifndef TILEMAPPICKERSCENE_H
#define TILEMAPPICKERSCENE_H


#include "editors/IndexedPickerScene.h"
#include "editors/TileMapEditorToolManager.h"
#include "gamedata/TileMap.h"
#include "gamegear/GGTileSet.h"
#include "gamegear/GGPalette.h"

namespace Tales {


class TileMapPickerScene : public IndexedPickerScene {
public:
  TileMapPickerScene();
                     
  TileMapPickerScene(TileMapEditorToolManager& toolManager__,
                     TileMap& tileMap__,
                     GGTileSet& graphic__,
                     GGPalette& palette0__,
                     int offset__);
  
  virtual void enterMouse();
  virtual void exitMouse();
  virtual void moveMouse(InputEventData eventData);
  virtual void pressMouse(InputEventData eventData);
  virtual void releaseMouse(InputEventData eventData);
  virtual void doubleClickMouse(InputEventData eventData);
  
  virtual void renderNative(Graphic& dst,
                            Box srcbox);
                            
  int nativeW();
  int nativeH();
protected:
  int indexToTileX(int index) const;
  int indexToTileY(int index) const;
  
  void drawPencil(int posIndex);
  void grabPencil(int posIndex);

  TileMapEditorToolManager* toolManager_;
  TileMap* tileMap_;
  GGTileSet* graphic_;
  GGPalette* palette0_;
  int offset_;
};


};


#endif
