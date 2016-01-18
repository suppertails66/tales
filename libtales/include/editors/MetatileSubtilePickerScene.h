#ifndef METATILESUBTILEPICKERSCENE_H
#define METATILESUBTILEPICKERSCENE_H


#include "editors/IndexedPickerScene.h"
#include "gamegear/GGTileSet.h"
#include "gamedata/MetatileStructure.h"

namespace Tales {


class MetatileSubtilePickerScene : public IndexedPickerScene {
public:
  MetatileSubtilePickerScene();
  
  virtual ~MetatileSubtilePickerScene();
  
  virtual void renderNative(Graphic& dst,
                            Box srcbox);
                            
  virtual void pressMouse(InputEventData eventData);
  
  void setTiles(GGTileSet& tiles__);
  void setPalette0(GGPalette& palette0__);
  void setPalette1(GGPalette& palette1__);
  void setMetatile(MetatileStructure& metatile__);
protected:
  const static int tileOffset_ = -256;
//  static Graphic tileRenderBuffer_;

  GGTileSet* tiles_;
  GGPalette* palette0_;
  GGPalette* palette1_;
  MetatileStructure* metatile_;
};


};


#endif
