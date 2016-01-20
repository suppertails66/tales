#ifndef COLORPICKERGRAPHICSCENELAYER_H
#define COLORPICKERGRAPHICSCENELAYER_H


#include "structs/GraphicSceneLayer.h"
#include "structs/InputEventData.h"
#include "gamegear/GGPalette.h"

namespace Tales {


class ColorPickerGraphicSceneLayer : public GraphicSceneLayer {
public:
  ColorPickerGraphicSceneLayer();
  
  virtual void render(Graphic& dst,
                      Box srcbox,
                      double scale);
  
  virtual void enterMouse();
  virtual void exitMouse();
  virtual void moveMouse(InputEventData eventData);
  virtual void pressMouse(InputEventData eventData);
  virtual void releaseMouse(InputEventData eventData);
  virtual void doubleClickMouse(InputEventData eventData);
  
  void setPickedIndex(int index);
  int pickedIndex();
  
  void setPickedIndexBoxEnabled(bool pickedIndexBoxEnabled__);
  
  void setPalette(GGPalette palette__);
  void setColorInPalette(GGColor color,
                         int index);
  
  void disableAllColors();
  void enableAllColors();
  
  bool colorEnabled(int index);
  void setColorEnabled(int index, bool enabled);
  
  void setColorPickedCallback(
    void (*colorPickedCallback__)(int,void*),
    void* colorPickedCallbackParam__);
  
  int previewWidth();
  int previewHeight();
  
  double scale();
  void setScale(double scale__);
protected:
  int colorIndexToLocalX(int index) const;
  int colorIndexToLocalY(int index) const;
  int realCoordinateToColorIndex(int x, int y) const;
  
  const static int numColors_ = GGPalette::numColorsInPalette;
  const static int colorsPerRow_ = 16;
  const static int colorsPerColumn_ = numColors_ / colorsPerRow_;
  const static int widthOfColor_ = 16;
  const static int heightOfColor_ = 16;
  const static int previewWidth_ = colorsPerRow_ * widthOfColor_;
  const static int previewHeight_ = colorsPerColumn_ * heightOfColor_;
  
  Graphic previewBuffer_;
  
  GGPalette palette;
  
  bool enabledColors_[numColors_];

  double scale_;
  
  bool pickedIndexBoxEnabled_;
  int pickedIndex_;
  
  bool highlightedIndexBoxEnabled_;
  int highlightedIndex_;
  
  void (*colorPickedCallback_)(int,void*);
  void* colorPickedCallbackParam_;
  
};


};


#endif
