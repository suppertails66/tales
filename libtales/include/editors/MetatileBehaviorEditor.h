#ifndef METATILEBEHAVIOREDITOR_H
#define METATILEBEHAVIOREDITOR_H


#include "editors/BaseEditor.h"
#include "editors/MetatileBehaviorPickerScene.h"
#include "gamedata/EditableSlopeSpeedValues.h"

namespace Tales {


class MetatileBehaviorEditor : public BaseEditor {
public:
  enum EditingMode {
    editingEffect = 0,
    editingVerticalSolidity,
    editingHorizontalSolidity
  };

  MetatileBehaviorEditor(EditableMetatileBehaviors&
                                metatileBehaviors__,
                         EditableMetatileWidthMaps&
                           metatileWidthMaps__,
                         EditableMetatileHeightMaps&
                           metatileHeightMaps__,
                         EditableSlopeSpeedValues&
                           slopeSpeedValues__);
  
  virtual ~MetatileBehaviorEditor();
  
  virtual void refresh();
  
  void pickMetatile(int index);
  int pickedMetatile();
  
  void metatilePickerEnterMouse();
  void metatilePickerExitMouse();
  void metatilePickerMoveMouse(InputEventData eventData);
  void metatilePickerPressMouse(InputEventData eventData);
  
  void drawMetatilePickerGraphic(Graphic& dst);
  
  void reloadMetatileDisplay();
  
  void setMetatilePickedCallback(
    void (*metatilePickedCallback__)(int, void*),
    void* metatilePickedCallbackParam__);
    
  void setEditingMode(EditingMode editingMode__);
  
  void setGridEnabled(bool gridEnabled__);
  
  MetatileBehavior& currentMetatileBehavior();
  
  Graphic& currentMetatileEffectGraphic();
  Graphic& currentMetatileVerticalSolidityGraphic();
  Graphic& currentMetatileHorizontalSolidityGraphic();
  
  int numWidthMaps();
  int numHeightMaps();
  int numSlopeSpeedIndices();
  
  SlopeSpeedValue slopeSpeedValue(int index);
protected:
  
  Graphic& metatileEffectGraphic(int index);
  Graphic& metatileVerticalSolidityGraphic(int index);
  Graphic& metatileHorizontalSolidityGraphic(int index);
  
  EditableMetatileBehaviors&
         metatileBehaviors_;
  EditableMetatileWidthMaps&
    metatileWidthMaps_;
  EditableMetatileHeightMaps&
    metatileHeightMaps_;
  EditableSlopeSpeedValues&
    slopeSpeedValues_;
  
  void (*metatilePickedCallback_)(int, void*);
  void* metatilePickedCallbackParam_;
    
  MetatileBehaviorPickerScene metatilePickerScene_;
  
  EditingMode editingMode_;
  
};


};


#endif
