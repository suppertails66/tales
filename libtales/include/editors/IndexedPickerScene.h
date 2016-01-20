#ifndef INDEXEDPICKERSCENE_H
#define INDEXEDPICKERSCENE_H


#include "structs/LayeredGraphicScene.h"
#include "structs/InputEventData.h"
#include "editors/GridGraphicSceneLayer.h"

namespace Tales {


class IndexedPickerScene : public LayeredGraphicScene {
public:
  IndexedPickerScene(int totalSelectables__,
                     int selectablesPerRow__,
                     int selectableWidth__,
                     int selectableHeight__);
  
  virtual ~IndexedPickerScene();
  
  virtual void render(Graphic& dst,
                      Box srcbox,
                      double scale);
  
  virtual void renderNative(Graphic& dst,
                            Box srcbox) =0;
  
  virtual void enterMouse();
  virtual void exitMouse();
  virtual void moveMouse(InputEventData eventData);
  virtual void pressMouse(InputEventData eventData);
  virtual void releaseMouse(InputEventData eventData);
  virtual void doubleClickMouse(InputEventData eventData);
  
  int highlightedIndex();
  int pickedIndex();
  
  void clearHighlightedBox();
  void clearPickedBox();
  
  void pickIndex(int index);
  void highlightIndex(int index);
  
  void setGridLayerEnabled(bool gridLayerEnabled__);
  
  double sceneScale();
  void setSceneScale(double sceneScale__);
protected:
  int selectablesPerColumn() const;
  
  int realPosToSelectableIndex(int realX, int realY);
  int drawPosToSelectableIndex(int drawX, int drawY);
  int selectableIndexToDrawX(int index);
  int selectableIndexToDrawY(int index);
  int selectableIndexToNativeDrawX(int index);
  int selectableIndexToNativeDrawY(int index);
  
  Graphic nativeBuffer_;
  
  int totalSelectables_;
  int selectablesPerRow_;
  int selectableWidth_;
  int selectableHeight_;
  
  double sceneScale_;

  bool highlightedSelectableBoxEnabled_;
  int highlightedSelectableIndex_;

  bool pickedSelectableBoxEnabled_;
  int pickedSelectableIndex_;
  
  bool gridLayerEnabled_;
  
  GridGraphicSceneLayer gridLayer_;
};


};


#endif
