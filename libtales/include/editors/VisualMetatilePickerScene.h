#ifndef VISUALMETATILEPICKERSCENE_H
#define VISUALMETATILEPICKERSCENE_H


#include "editors/IndexedPickerScene.h"
#include "gamegear/GGTileSet.h"
#include "gamegear/GGPalette.h"
#include "gamedata/MetatileStructureSet.h"

namespace Tales {


class VisualMetatilePickerScene : public IndexedPickerScene {
public:
  VisualMetatilePickerScene();
  
  virtual ~VisualMetatilePickerScene();
  
  virtual void renderNative(Graphic& dst,
                            Box srcbox);
  
  void setTiles(GGTileSet& tiles__);
  void setPalette0(GGPalette& palette0__);
  void setPalette1(GGPalette& palette1__);
  void setMetatiles(MetatileStructureSet& metatiles__);
  
  GGTileSet& tiles();
  GGPalette& palette0();
  GGPalette& palette1();
  MetatileStructureSet& metatiles();
protected:
  const static int tileOffset_ = -256;
//  static Graphic tileRenderBuffer_;

  GGTileSet* tiles_;
  GGPalette* palette0_;
  GGPalette* palette1_;
  MetatileStructureSet* metatiles_;
  
};


};


#endif
