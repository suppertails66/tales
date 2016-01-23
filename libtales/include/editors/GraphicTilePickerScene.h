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
                         GGPalette& palette__);
  
  virtual void renderNative(Graphic& dst,
                            Box srcbox);
                            
  int nativeW();
  int nativeH();
protected:
  const static int tilesPerRow_ = 16;

  TileMapEditorToolManager* toolManager_;
  GGTileSet* graphic_;
  GGPalette* palette_;
  
};


};


#endif
