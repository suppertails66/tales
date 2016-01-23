#ifndef TILEMAPPICKERSCENE_H
#define TILEMAPPICKERSCENE_H


#include "editors/IndexedPickerScene.h"
#include "gamedata/TileMap.h"
#include "gamegear/GGTileSet.h"
#include "gamegear/GGPalette.h"

namespace Tales {


class TileMapPickerScene : public IndexedPickerScene {
public:
  TileMapPickerScene();
                     
  TileMapPickerScene(TileMap& tileMap__,
                     GGTileSet& graphic__,
                     GGPalette& palette0__,
                     int offset__);
  
  virtual void renderNative(Graphic& dst,
                            Box srcbox);
                            
  int nativeW();
  int nativeH();
protected:
  TileMap* tileMap_;
  GGTileSet* graphic_;
  GGPalette* palette0_;
  int offset_;
};


};


#endif
