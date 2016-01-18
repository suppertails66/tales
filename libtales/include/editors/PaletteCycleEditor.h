#ifndef PALETTECYCLEEDITOR_H
#define PALETTECYCLEEDITOR_H


#include "editors/BaseEditor.h"
#include "editors/ColorPickerGraphicSceneLayer.h"
#include "editors/ColorPreviewGraphicSceneLayer.h"
#include "gamedata/EditablePaletteCycles.h"
#include "structs/Graphic.h"

namespace Tales {


class PaletteCycleEditor : public BaseEditor {
public:
  enum CycleID {
    torch = 0,
    lakeRocky1,
    lakeRocky2,
    lakeRocky3,
    lakeRocky4,
    lakeRocky5,
    lakeRocky6,
    cavernIsland,
    poloyForest,
    worldMap
  };

  PaletteCycleEditor(EditablePaletteCycles& paletteCycles__);
  
  void changeCycle(CycleID currentCycleID__);
  void changeCycleState(int stateNum__);
  int numCurrentCycleStates();
  
  void changeCurrentColor(int r, int g, int b);
  Color currentColor();
  
  virtual void refresh();
  
  void drawColorPickerGraphic(Graphic& dst);
  void drawColorPreviewGraphic(Graphic& dst);
  
  virtual void colorPickerEnterMouse();
  virtual void colorPickerExitMouse();
  virtual void colorPickerMoveMouse(InputEventData eventData);
  virtual void colorPickerPressMouse(InputEventData eventData);
  virtual void colorPickerReleaseMouse(InputEventData eventData);
  virtual void colorPickerDoubleClickMouse(InputEventData eventData);
  
  std::string nameOfCycle(CycleID cycleID);
protected:
  const static int colorPickerWidth_ = 16 * 16;
  const static int colorPickerHeight_ = 16;
  const static int colorPreviewWidth_ = 64;
  const static int colorPreviewHeight_ = 64;
  
  PaletteCycle& currentCycle();
  PaletteCycleState& currentCycleState();
  
  GGPalette generateCurrentPalette();
  
  void setDisabledColors();

  EditablePaletteCycles& paletteCycles_;
  
  ColorPickerGraphicSceneLayer colorPicker_;
  ColorPreviewGraphicSceneLayer colorPreview_;
  
  CycleID currentCycleID_;
  int stateNum_;
};


};


#endif
