#ifndef METATILEBEHAVIORPICKERSCENE_H
#define METATILEBEHAVIORPICKERSCENE_H


#include "editors/MetatilePickerSceneBase.h"
#include "editors/MetatileGraphicCollection.h"
#include "gamedata/EditableMetatileBehaviors.h"
#include "gamedata/EditableMetatileWidthMaps.h"
#include "gamedata/EditableMetatileHeightMaps.h"

namespace Tales {


class MetatileBehaviorPickerScene : public MetatilePickerSceneBase {
public:
  enum ViewMode {
    viewEffect = 0,
    viewVerticalSolidity,
    viewHorizontalSolidity
  };

  MetatileBehaviorPickerScene(EditableMetatileBehaviors&
                                metatileBehaviors__,
                              EditableMetatileWidthMaps&
                                metatileWidthMaps__,
                              EditableMetatileHeightMaps&
                                metatileHeightMaps__);
  
  virtual ~MetatileBehaviorPickerScene();
  
  virtual void render(Graphic& dst,
                      Box srcbox,
                      double scale);
  
  virtual void enterMouse();
  virtual void exitMouse();
  virtual void moveMouse(InputEventData eventData);
  virtual void pressMouse(InputEventData eventData);
//  virtual void releaseMouse(int x, int y, InputEventData eventData);
//  virtual void doubleClickMouse(int x, int y, InputEventData eventData);

  void pickMetatile(int index);
  int pickedMetatile();
  
  void reloadMetatileDisplay();

//  void setEffectLayerEnabled(bool effectLayerEnabled__);
  
  void setMetatilePickedCallback(
    void (*metatilePickedCallback__)(int, void*),
    void* metatilePickedCallbackParam__);
    
  void setViewMode(ViewMode viewMode__);
  
  Graphic& metatileEffectGraphic(int index);
  Graphic& metatileVerticalSolidityGraphic(int index);
  Graphic& metatileHorizontalSolidityGraphic(int index);
protected:
  EditableMetatileBehaviors* metatileBehaviors_;
  EditableMetatileWidthMaps* metatileWidthMaps_;
  EditableMetatileHeightMaps* metatileHeightMaps_;

  MetatileGraphicCollection metatilesEffect_;
  MetatileGraphicCollection metatilesVerticalSolidity_;
  MetatileGraphicCollection metatilesHorizontalSolidity_;
  
  bool effectLayerEnabled_;
  bool verticalSolidityLayerEnabled_;
  bool horizontalSolidityLayerEnabled_;
  
  void (*metatilePickedCallback_)(int, void*);
  void* metatilePickedCallbackParam_;
};


};


#endif
