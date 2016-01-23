#ifndef GRAPHICTILEPICKERSCENE_H
#define GRAPHICTILEPICKERSCENE_H


#include "editors/IndexedPickerScene.h"
#include "gamegear/GGTileSet.h"
#include "gamegear/GGPalette.h"

namespace Tales {


class GraphicTilePickerScene : public IndexedPickerScene {
public:
  GraphicTilePickerScene();
  
  GraphicTilePickerScene(GGTileSet& graphic__,
                         GGPalette& palette__);
  
  virtual void renderNative(Graphic& dst,
                            Box srcbox);
                            
  int nativeW();
  int nativeH();
protected:
  const static int tilesPerRow_ = 16;

  GGTileSet* graphic_;
  GGPalette* palette_;
  
};


};


#endif
