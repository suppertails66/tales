#include "editors/MetatileBehaviorEditor.h"
#include <cstdlib>

namespace Tales {


MetatileBehaviorEditor::MetatileBehaviorEditor(
                         EditableMetatileBehaviors&
                                metatileBehaviors__,
                         EditableMetatileWidthMaps&
                           metatileWidthMaps__,
                         EditableMetatileHeightMaps&
                           metatileHeightMaps__,
                         EditableSlopeSpeedValues&
                           slopeSpeedValues__)
  : metatileBehaviors_(metatileBehaviors__),
    metatileWidthMaps_(metatileWidthMaps__),
    metatileHeightMaps_(metatileHeightMaps__),
    slopeSpeedValues_(slopeSpeedValues__),
    metatilePickedCallback_(NULL),
    metatilePickedCallbackParam_(NULL),
    metatilePickerScene_(metatileBehaviors_,
                         metatileWidthMaps_,
                         metatileHeightMaps_),
    editingMode_(editingEffect) { };

MetatileBehaviorEditor::~MetatileBehaviorEditor() { };

void MetatileBehaviorEditor::refresh() {
  
}
  
void MetatileBehaviorEditor::pickMetatile(int index) {
  metatilePickerScene_.pickMetatile(index);
}

int MetatileBehaviorEditor::pickedMetatile() {
  return metatilePickerScene_.pickedMetatile();
}
  
void MetatileBehaviorEditor::metatilePickerEnterMouse() {
  metatilePickerScene_.enterMouse();
}

void MetatileBehaviorEditor::metatilePickerExitMouse() {
  metatilePickerScene_.exitMouse();
}

void MetatileBehaviorEditor
    ::metatilePickerMoveMouse(InputEventData eventData) {
  metatilePickerScene_.moveMouse(eventData);
}

void MetatileBehaviorEditor
    ::metatilePickerPressMouse(InputEventData eventData) {
  metatilePickerScene_.pressMouse(eventData);
}
  
void MetatileBehaviorEditor
    ::setMetatilePickedCallback(
    void (*metatilePickedCallback__)(int, void*),
    void* metatilePickedCallbackParam__) {
  metatilePickedCallback_ = metatilePickedCallback__;
  metatilePickedCallbackParam_ = metatilePickedCallbackParam__;
  metatilePickerScene_.setMetatilePickedCallback(
    metatilePickedCallback__,
    metatilePickedCallbackParam__);
}
  
void MetatileBehaviorEditor::drawMetatilePickerGraphic(Graphic& dst) {
  metatilePickerScene_.render(dst,
                              Box(0, 0, dst.w(), dst.h()),
                              1.00);
}
  
void MetatileBehaviorEditor::reloadMetatileDisplay() {
  metatilePickerScene_.reloadMetatileDisplay();
}
    
void MetatileBehaviorEditor::setEditingMode(EditingMode editingMode__) {
  editingMode_ = editingMode__;
  
  switch (editingMode_) {
  case editingEffect:
    metatilePickerScene_.setViewMode(
      MetatileBehaviorPickerScene::viewEffect);
    break;
  case editingVerticalSolidity:
    metatilePickerScene_.setViewMode(
      MetatileBehaviorPickerScene::viewVerticalSolidity);
    break;
  case editingHorizontalSolidity:
    metatilePickerScene_.setViewMode(
      MetatileBehaviorPickerScene::viewHorizontalSolidity);
    break;
  default:
    break;
  }
}
  
void MetatileBehaviorEditor::setGridEnabled(bool gridEnabled__) {
  metatilePickerScene_.setGridLayerEnabled(gridEnabled__);
}
  
MetatileBehavior& MetatileBehaviorEditor::currentMetatileBehavior() {
  return metatileBehaviors_.metatileBehavior(
    metatilePickerScene_.pickedMetatile());
}
  
Graphic& MetatileBehaviorEditor::currentMetatileEffectGraphic() {
  return metatileEffectGraphic(metatilePickerScene_.pickedMetatile());
}

Graphic& MetatileBehaviorEditor::currentMetatileVerticalSolidityGraphic() {
  return metatileVerticalSolidityGraphic(
      metatilePickerScene_.pickedMetatile());
}

Graphic& MetatileBehaviorEditor::currentMetatileHorizontalSolidityGraphic() {
  return metatileHorizontalSolidityGraphic(
      metatilePickerScene_.pickedMetatile());
}
  
int MetatileBehaviorEditor::numWidthMaps() {
  return metatileWidthMaps_.size();
}

int MetatileBehaviorEditor::numHeightMaps() {
  return metatileHeightMaps_.size();
}
  
Graphic& MetatileBehaviorEditor::metatileEffectGraphic(int index) {
  return metatilePickerScene_.metatileEffectGraphic(index);
}

Graphic& MetatileBehaviorEditor::metatileVerticalSolidityGraphic(int index) {
  return metatilePickerScene_.metatileVerticalSolidityGraphic(index);
}

Graphic& MetatileBehaviorEditor::metatileHorizontalSolidityGraphic(int index) {
  return metatilePickerScene_.metatileHorizontalSolidityGraphic(index);
}

int MetatileBehaviorEditor::numSlopeSpeedIndices() {
  return slopeSpeedValues_.size();
}
  
SlopeSpeedValue MetatileBehaviorEditor::slopeSpeedValue(int index) {
  return slopeSpeedValues_.speedValue(index);
}


};
