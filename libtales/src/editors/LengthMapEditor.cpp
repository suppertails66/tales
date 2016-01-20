#include "editors/LengthMapEditor.h"

namespace Tales {


LengthMapEditor::LengthMapEditor(
                  EditableMetatileWidthMaps&
                    metatileWidthMaps__,
                  EditableMetatileHeightMaps&
                    metatileHeightMaps__,
                  EditableSlopeSpeedValues&
                    slopeSpeedValues__)
  : metatileWidthMaps_(&metatileWidthMaps__),
    metatileHeightMaps_(&metatileHeightMaps__),
    slopeSpeedValues_(&slopeSpeedValues__),
    previewScene_() {
  previewScene_.setLengthMap(metatileWidthMaps_->mapAt(0),
                             LengthMapLayeredGraphicScene::mapTypeWidth);
}
  
LengthMapEditor::~LengthMapEditor() { };

void LengthMapEditor::refresh() {
  
}

void LengthMapEditor::editorEnterMouse() {
  previewScene_.enterMouse();
}

void LengthMapEditor::editorExitMouse() {
  previewScene_.exitMouse();
}

void LengthMapEditor::editorMoveMouse(InputEventData eventData) {
  previewScene_.moveMouse(eventData);
}

void LengthMapEditor::editorPressMouse(InputEventData eventData) {
  previewScene_.pressMouse(eventData);
}

void LengthMapEditor::editorReleaseMouse(InputEventData eventData) {
  previewScene_.releaseMouse(eventData);
}

void LengthMapEditor::editorDoubleClickMouse(InputEventData eventData) {
  previewScene_.doubleClickMouse(eventData);
}
  
void LengthMapEditor::setLengthMap(int index,
                  LengthMapLayeredGraphicScene::MapType mapType__) {
  switch (mapType__) {
  case LengthMapLayeredGraphicScene::mapTypeWidth:
    previewScene_.setLengthMap(metatileWidthMaps_->mapAt(index),
                             LengthMapLayeredGraphicScene::mapTypeWidth);
    break;
  case LengthMapLayeredGraphicScene::mapTypeHeight:
    previewScene_.setLengthMap(metatileHeightMaps_->mapAt(index),
                             LengthMapLayeredGraphicScene::mapTypeHeight);
    break;
  default:
    break;
  }
}
    
void LengthMapEditor::setCurrentMetatileToForward() {
  previewScene_.setCurrentMetatileToForward();
}

void LengthMapEditor::setCurrentMetatileToBackward() {
  previewScene_.setCurrentMetatileToBackward();
}

void LengthMapEditor::drawEditorGraphic(Graphic& dst) {
  previewScene_.render(dst,
                       Box(0, 0, 16, 16),
                       16.0);
}

void LengthMapEditor::setEditDialogCallback(
    bool (*editDialogCallback__)(int, LengthMapValue*, void*),
    void* editDialogCallbackParam__) {
  editDialogCallback_ = editDialogCallback__;
  editDialogCallbackParam_ = editDialogCallbackParam__;
  previewScene_.setEditDialogCallback(editDialogCallback_,
                                      editDialogCallbackParam_);
}

void LengthMapEditor::setGridEnabled(bool gridEnabled__) {
  previewScene_.setGridLayerEnabled(gridEnabled__);
}
  
int LengthMapEditor::numWidthMaps() {
  return metatileWidthMaps_->size();
}

int LengthMapEditor::numHeightMaps() {
  return metatileHeightMaps_->size();
}
  
int LengthMapEditor::previewWidth() {
  return 256;
}

int LengthMapEditor::previewHeight() {
  return 256;
}
  
int LengthMapEditor::numSlopeSpeedValues() {
  return slopeSpeedValues_->size();
}

int LengthMapEditor::slopeSpeedValue(int index) {
  return slopeSpeedValues_->speedValue(index);
}

void LengthMapEditor::setSlopeSpeedValue(int index, int value) {
  slopeSpeedValues_->speedValue(index) = value;
}


};
