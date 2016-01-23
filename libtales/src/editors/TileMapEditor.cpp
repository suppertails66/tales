#include "editors/TileMapEditor.h"
#include "gamedata/TileMapInfos.h"
#include "exception/OutOfRangeIndexException.h"

namespace Tales {


TileMapEditor::TileMapEditor(EditableTileMaps& tileMaps__,
                EditableLevelGraphicsData& levelGraphicsData__,
                EditableStandardPalettes& standardPalettes__)
  : tileMaps_(tileMaps__),
    levelGraphicsData_(levelGraphicsData__),
    standardPalettes_(standardPalettes__),
    currentIndex_(0),
    gridEnabled_(true) {
  changeTileMap(0);
}

void TileMapEditor::refresh() {
  
}

void TileMapEditor::drawTileMapPreview(Graphic& dst) {
  TileMapInfo info = TileMapInfos::tileMapInfo(currentIndex_);
  dst = Graphic(tileMapPreview_.nativeW() * tileMapPreview_.sceneScale(),
                tileMapPreview_.nativeH() * tileMapPreview_.sceneScale());
  
  tileMapPreview_.render(dst,
                         Box(0, 0,
                             tileMapPreview_.nativeW(),
                             tileMapPreview_.nativeH()),
                         1.00);
}

void TileMapEditor::drawTilePicker(Graphic& dst) {
  
}

int TileMapEditor::numTileMaps() {
  return tileMaps_.size();
}

int TileMapEditor::changeTileMap(int index) {
  if (index >= numTileMaps()) {
    throw OutOfRangeIndexException(TALES_SRCANDLINE,
                                   "TileMapEditor::changeTileMap(int)",
                                   index);
  }
  
  TileMapInfo info = TileMapInfos::tileMapInfo(index);
  tileMapPreview_ = TileMapPickerScene(
                        tileMaps_.tileMap(index),
                        levelGraphicsData_.compressedGraphic(
                          info.graphicNum),
                        standardPalettes_.palette(
                          info.paletteNum),
                        info.offset);
  tileMapPreview_.setGridLayerEnabled(gridEnabled_);
  tileMapPreview_.setSceneScale(2.00);
  
  currentIndex_ = index;
}

std::string TileMapEditor::nameOfTileMap(int index) {
  return (TileMapInfos::tileMapInfo(index).name);
}
  
int TileMapEditor::currentIndex() {
  return currentIndex_;
}

bool TileMapEditor::gridEnabled() const {
  return gridEnabled_;
}
  
void TileMapEditor::setGridEnabled(bool gridEnabled__) {
  gridEnabled_ = gridEnabled__;
  tileMapPreview_.setGridLayerEnabled(gridEnabled__);
}
  
void TileMapEditor::tileMapEnter() {
  tileMapPreview_.enterMouse();
}

void TileMapEditor::tileMapExit() {
  tileMapPreview_.exitMouse();
}

void TileMapEditor::tileMapMouseMove(InputEventData eventData) {
  tileMapPreview_.moveMouse(eventData);
}

void TileMapEditor::tileMapMousePress(InputEventData eventData) {
  tileMapPreview_.pressMouse(eventData);
}

void TileMapEditor::tileMapMouseRelease(InputEventData eventData) {
  tileMapPreview_.releaseMouse(eventData);
}

void TileMapEditor::tileMapMouseDoubleClick(InputEventData eventData) {
  tileMapPreview_.doubleClickMouse(eventData);
}

void TileMapEditor::tilePickerEnter() {
  
}

void TileMapEditor::tilePickerExit() {
  
}

void TileMapEditor::tilePickerMouseMove(InputEventData eventData) {
  
}

void TileMapEditor::tilePickerMousePress(InputEventData eventData) {
  
}

void TileMapEditor::tilePickerMouseRelease(InputEventData eventData) {
  
}

void TileMapEditor::tilePickerMouseDoubleClick(InputEventData eventData) {
  
}


};
