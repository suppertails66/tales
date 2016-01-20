#ifndef PALETTEEDITOR_H
#define PALETTEEDITOR_H


#include "editors/BaseEditor.h"
#include "structs/InputEventData.h"
#include "structs/Graphic.h"
#include "gamedata/EditableStandardPalettes.h"
#include "editors/ColorPickerGraphicSceneLayer.h"
#include "editors/ColorPreviewGraphicSceneLayer.h"
#include <string>

namespace Tales {


class PaletteEditor : public BaseEditor {
public:
  PaletteEditor(EditableStandardPalettes& palettes__);
  
  virtual ~PaletteEditor();
  
  virtual void refresh();
  
  void pickerEnterMouse();
  void pickerExitMouse();
  void pickerMoveMouse(InputEventData eventData);
  void pickerPressMouse(InputEventData eventData);
  void pickerReleaseMouse(InputEventData eventData);
  void pickerDoubleClickMouse(InputEventData eventData);
  
  void drawPickerGraphic(Graphic& dst);
  void drawPreviewGraphic(Graphic& dst);
  
  void setColorPickedCallback(
    void (*colorPickedCallback__)(int,void*),
    void* colorPickedCallbackParam__);
    
  int numPalettes();
  void selectPalette(int paletteIndex__);
  GGColor& colorAtIndex(int colorIndex);
  int pickedIndex();
  GGColor& currentColor();
  
  double scale();
  void setScale(double scale__);
  
  int pickerPreviewWidth();
  int pickerPreviewHeight();
  
  static std::string nameOfPalette(int paletteIndex__);
protected:

  EditableStandardPalettes& palettes_;
  
  ColorPickerGraphicSceneLayer picker_;
  
  ColorPreviewGraphicSceneLayer colorPreview_;
  
  int paletteIndex_;
  
};


};


#endif
