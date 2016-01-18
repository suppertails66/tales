#ifndef METATILEPICKERSCENEBASE_H
#define METATILEPICKERSCENEBASE_H


#include "structs/LayeredGraphicScene.h"
#include "editors/GridGraphicSceneLayer.h"
#include "structs/InputEventData.h"

namespace Tales {


class MetatilePickerSceneBase : public LayeredGraphicScene {
public:
  MetatilePickerSceneBase();
  
  virtual ~MetatilePickerSceneBase();
  
  virtual void enterMouse();
  virtual void exitMouse();
  virtual void moveMouse(int x, int y, InputEventData eventData);
  virtual void pressMouse(int x, int y, InputEventData eventData);
  virtual void releaseMouse(int x, int y, InputEventData eventData);
  virtual void doubleClickMouse(int x, int y, InputEventData eventData);
  
  void setGridLayerEnabled(bool gridLayerEnabled__);
protected:

  const static int numMetatiles_ = 256;
  const static int metatilesPerRow_ = 16;
  const static int metatilesPerColumn_ = numMetatiles_ / metatilesPerRow_;
  
  int metatileIndexToX(int index) const;
  int metatileIndexToY(int index) const;
  int coordinateToMetatileIndex(int x, int y) const;

  bool highlightedMetatileBoxEnabled_;
  int highlightedMetatileIndex_;

  bool pickedMetatileBoxEnabled_;
  int pickedMetatileIndex_;
  
  bool gridLayerEnabled_;
  
//  bool highlightedMetatileBoxEnabled_;
//  int highlightedMetatileIndex_;
  
  GridGraphicSceneLayer gridLayer_;
};


};


#endif
