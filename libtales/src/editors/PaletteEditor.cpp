#include "editors/PaletteEditor.h"

namespace Tales {


PaletteEditor::PaletteEditor(EditableStandardPalettes& palettes__)
  : palettes_(palettes__),
    paletteIndex_(0) { };
  
PaletteEditor::~PaletteEditor() { };

void PaletteEditor::refresh() {
  picker_.setPalette(palettes_.palette(paletteIndex_));
}
  
void PaletteEditor::pickerEnterMouse() {
  picker_.enterMouse();
}

void PaletteEditor::pickerExitMouse() {
  picker_.exitMouse();
}

void PaletteEditor::pickerMoveMouse(InputEventData eventData) {
  picker_.moveMouse(eventData);
}

void PaletteEditor::pickerPressMouse(InputEventData eventData) {
  picker_.pressMouse(eventData);
}

void PaletteEditor::pickerReleaseMouse(InputEventData eventData) {
  picker_.releaseMouse(eventData);
}

void PaletteEditor::pickerDoubleClickMouse(InputEventData eventData) {
  picker_.doubleClickMouse(eventData);
}

void PaletteEditor::drawPickerGraphic(Graphic& dst) {
  picker_.render(dst,
                 Box(0, 0, picker_.previewWidth(), picker_.previewHeight()),
                 1.00);
}

void PaletteEditor::drawPreviewGraphic(Graphic& dst) {
  colorPreview_.setColor(
    Color(currentColor().realR(),
          currentColor().realG(),
          currentColor().realB(),
          Color::fullAlphaOpacity));
  colorPreview_.render(dst,
                       Box(0, 0, dst.w(), dst.h()),
                       1.00);
}

GGColor& PaletteEditor::currentColor() {
  return colorAtIndex(pickedIndex());
}
  
void PaletteEditor::setColorPickedCallback(
    void (*colorPickedCallback__)(int,void*),
    void* colorPickedCallbackParam__) {
  picker_.setColorPickedCallback(colorPickedCallback__,
                                 colorPickedCallbackParam__);
}
    
int PaletteEditor::numPalettes() {
  return palettes_.size();
}

void PaletteEditor::selectPalette(int paletteIndex__) {
  paletteIndex_ = paletteIndex__;
  picker_.setPalette(palettes_.palette(paletteIndex_));
}
  
int PaletteEditor::pickedIndex() {
  return picker_.pickedIndex();
}

GGColor& PaletteEditor::colorAtIndex(int colorIndex) {
  return palettes_.palette(paletteIndex_)[colorIndex];
}
  
double PaletteEditor::scale() {
  return picker_.scale();
}

void PaletteEditor::setScale(double scale__) {
  picker_.setScale(scale__);
}
  
int PaletteEditor::pickerPreviewWidth() {
  return picker_.previewWidth();
}

int PaletteEditor::pickerPreviewHeight() {
  return picker_.previewHeight();
}
  
std::string PaletteEditor::nameOfPalette(int paletteIndex__) {
  switch (paletteIndex__) {
  case 0:
    return "?";
    break;
  case 1:
    return "Sega logo";
    break;
  case 2:
    return "Level select font";
    break;
  case 3:
    return "Spark weapon flash";
    break;
  case 4:
    return "Standard object palette";
    break;
  case 5:
    return "?";
    break;
  case 6:
    return "?";
    break;
  case 7:
    return "Poloy Forest";
    break;
  case 8:
    return "Caron Forest";
    break;
  case 9:
    return "Volcanic Tunnel";
    break;
  case 10:
    return "Polly Mt. 1";
    break;
  case 11:
    return "Polly Mt. 2 (dark)";
    break;
  case 12:
    return "Polly Mt. 2 (bright)";
    break;
  case 13:
    return "Lake Rocky, type 1";
    break;
  case 14:
    return "Lake Rocky, type 2";
    break;
  case 15:
    return "Lake Rocky, type 3";
    break;
  case 16:
    return "Lake Rocky, type 4";
    break;
  case 17:
    return "Lake Crystal";
    break;
  case 18:
    return "?";
    break;
  case 19:
    return "?";
    break;
  case 20:
    return "Green Island";
    break;
  case 21:
    return "Cavern Island";
    break;
  case 22:
    return "Cavern Island boss";
    break;
  case 23:
    return "Coco Island";
    break;
  case 24:
    return "Battle Fortress 1";
    break;
  case 25:
    return "Battle Fortress 2";
    break;
  case 26:
    return "Title screen (tilemap)";
    break;
  case 27:
    return "Title screen (objects)";
    break;
  case 28:
    return "World map (tilemap)";
    break;
  case 29:
    return "World map (sprites)";
    break;
  case 30:
    return "?";
    break;
  case 31:
    return "?";
    break;
  case 32:
    return "?";
    break;
  case 33:
    return "?";
    break;
  case 34:
    return "?";
    break;
  case 35:
    return "Tails' House";
    break;
  case 36:
    return "Remote Robot dock cutscene";
    break;
  case 37:
    return "Credits";
    break;
  case 38:
    return "Game over";
    break;
  case 39:
    return "Cavern Island boss object palette";
    break;
  case 40:
    return "Coco Island boss object palette";
    break;
  case 41:
    return "Tails' House dock palette";
    break;
  default:
    return "?????";
    break;
  }
}


};
