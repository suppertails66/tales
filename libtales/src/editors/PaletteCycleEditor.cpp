#include "editors/PaletteCycleEditor.h"

namespace Tales {


PaletteCycleEditor
    ::PaletteCycleEditor(EditablePaletteCycles& paletteCycles__)
  : paletteCycles_(paletteCycles__),
    currentCycleID_(torch),
    stateNum_(0) {
  changeCycle(torch);
  colorPicker_.setPickedIndexBoxEnabled(true);
  colorPicker_.setScale(2.00);
}
  
void PaletteCycleEditor::refresh() {
  
}
  
void PaletteCycleEditor
    ::drawColorPickerGraphic(Graphic& dst) {
  dst = Graphic(colorPicker_.previewWidth(),
                colorPicker_.previewHeight());
  
  colorPicker_.render(dst,
                      Box(0, 0, colorPickerWidth_, colorPickerHeight_),
                      1.00);
}

void PaletteCycleEditor
    ::drawColorPreviewGraphic(Graphic& dst) {
  dst = Graphic(colorPreviewWidth_, colorPreviewHeight_);
  
  int currentNum = colorPicker_.pickedIndex();
  GGColor color = currentCycleState().color(currentNum);
  Color realColor = Color(color.realR(),
                          color.realG(),
                          color.realB(),
                          Color::fullAlphaOpacity);
  colorPreview_.setColor(realColor);
  
  colorPreview_.render(dst,
                       Box(0, 0, colorPreviewWidth_, colorPreviewHeight_),
                       1.00);
}
  
void PaletteCycleEditor
    ::changeCycle(CycleID currentCycleID__) {
  currentCycleID_ = currentCycleID__;
  changeCycleState(0);
  
  setDisabledColors();
}

void PaletteCycleEditor
    ::changeCycleState(int stateNum__) {
  stateNum_ = stateNum__;
  
  GGPalette currentPalette = generateCurrentPalette();
  colorPicker_.setPalette(currentPalette);
}

int PaletteCycleEditor
    ::numCurrentCycleStates() {
  return (currentCycle().numStates());
}
  
PaletteCycle& PaletteCycleEditor
    ::currentCycle() {
  switch (currentCycleID_) {
  case torch:
    return paletteCycles_.torchPaletteCycle();
    break;
  case lakeRocky1:
    return paletteCycles_.lakeRockyMainPaletteCycle();
    break;
  case lakeRocky2:
    return paletteCycles_.lakeRockyTopPaletteCycle1();
    break;
  case lakeRocky3:
    return paletteCycles_.lakeRockyTopPaletteCycle2();
    break;
  case lakeRocky4:
    return paletteCycles_.lakeRockyBottomPaletteCycle1();
    break;
  case lakeRocky5:
    return paletteCycles_.lakeRockyBottomPaletteCycle2();
    break;
  case lakeRocky6:
    return paletteCycles_.lakeRockyBottomPaletteCycle3();
    break;
  case cavernIsland:
    return paletteCycles_.cavernIslandPaletteCycle();
    break;
  case poloyForest:
    return paletteCycles_.poloyForestPaletteCycle();
    break;
  case worldMap:
    return paletteCycles_.worldMapPaletteCycle();
    break;
  default:
    break;
  }
}

PaletteCycleState& PaletteCycleEditor
    ::currentCycleState() {
  return currentCycle().state(stateNum_);
}
  
GGPalette PaletteCycleEditor::generateCurrentPalette() {
  GGPalette result;
  
  PaletteCycleState& state = currentCycleState();
  for (IndexToColorMap::const_iterator it = state.cbegin();
       it != state.cend();
       ++it) {
    result[it->first] = it->second;
  }
  
  return result;
}
  
void PaletteCycleEditor::setDisabledColors() {
  PaletteCycleState& state = currentCycleState();
  
  colorPicker_.disableAllColors();
  
  // hack to ensure first available color is selected by default
  bool foundFirstColor = false;
  
  for (int i = 0; i < GGPalette::numColorsInPalette; i++) {
    if (state.hasColor(i)) {
      colorPicker_.setColorEnabled(i, true);
      
      if (!foundFirstColor) {
        colorPicker_.setPickedIndex(i);
        foundFirstColor = true;
      }
    }
  }
}
  
void PaletteCycleEditor::changeCurrentColor(int r, int g, int b) {
  PaletteCycleState& state = currentCycleState();
  int currentNum = colorPicker_.pickedIndex();
  
  GGColor color;
  color.setRGB(r, g, b);
  
  state.modifyColor(currentNum, color);
  
  GGPalette currentPalette = generateCurrentPalette();
  colorPicker_.setPalette(currentPalette);
}

Color PaletteCycleEditor::currentColor() {
  int currentNum = colorPicker_.pickedIndex();
  GGColor color = currentCycleState().color(currentNum);
  Color realColor = Color(color.realR(),
                          color.realG(),
                          color.realB(),
                          Color::fullAlphaOpacity);
  return realColor;
}
  
void PaletteCycleEditor
    ::colorPickerEnterMouse() {
  colorPicker_.enterMouse();
}

void PaletteCycleEditor
    ::colorPickerExitMouse() {
  colorPicker_.exitMouse();
}

void PaletteCycleEditor
    ::colorPickerMoveMouse(InputEventData eventData) {
  colorPicker_.moveMouse(eventData);
}

void PaletteCycleEditor
    ::colorPickerPressMouse(InputEventData eventData) {
  colorPicker_.pressMouse(eventData);
}

void PaletteCycleEditor
    ::colorPickerReleaseMouse(InputEventData eventData) {
  colorPicker_.releaseMouse(eventData);
}

void PaletteCycleEditor
    ::colorPickerDoubleClickMouse(InputEventData eventData) {
  colorPicker_.doubleClickMouse(eventData);
}
  
std::string PaletteCycleEditor::nameOfCycle(CycleID cycleID) {
  switch (cycleID) {
  case torch:
    return "Tunnel/volcano torches";
    break;
  case lakeRocky1:
    return "Lake Rocky main";
    break;
  case lakeRocky2:
    return "Lake Rocky upper 1";
    break;
  case lakeRocky3:
    return "Lake Rocky upper 2";
    break;
  case lakeRocky4:
    return "Lake Rocky lower 1";
    break;
  case lakeRocky5:
    return "Lake Rocky lower 2";
    break;
  case lakeRocky6:
    return "Lake Rocky lower 3";
    break;
  case cavernIsland:
    return "Cavern Island";
    break;
  case poloyForest:
    return "Poloy Forest";
    break;
  case worldMap:
    return "World map";
    break;
  default:
    break;
  }
}



};
