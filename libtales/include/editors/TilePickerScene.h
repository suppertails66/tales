#ifndef TILEPICKERSCENE_H
#define TILEPICKERSCENE_H


#include "editors/IndexedPickerScene.h"
#include "gamegear/GGTileSet.h"
#include "gamegear/GGPalette.h"

namespace Tales {


class TilePickerScene : public IndexedPickerScene {
public:
  TilePickerScene();
  
  virtual ~TilePickerScene();
  
  virtual void renderNative(Graphic& dst,
                            Box srcbox);
  
  void setTiles(GGTileSet& tiles__);
  void setPalette0(GGPalette& palette0__);
  void setPalette1(GGPalette& palette1__);
protected:
  GGTileSet* tiles_;
  GGPalette* palette0_;
  GGPalette* palette1_;
};


};


#endif
