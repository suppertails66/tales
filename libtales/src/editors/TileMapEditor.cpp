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
  setGridEnabled(true);
}

void TileMapEditor::refresh() {
  
}

void TileMapEditor::drawTileMapPreview(Graphic& dst) {
  dst = Graphic(tileMapPreview_.nativeW() * tileMapPreview_.sceneScale(),
                tileMapPreview_.nativeH() * tileMapPreview_.sceneScale());
  
  tileMapPreview_.render(dst,
                         Box(0, 0,
                             tileMapPreview_.nativeW(),
                             tileMapPreview_.nativeH()),
                         1.00);
}

void TileMapEditor::drawTilePicker(Graphic& dst) {
  dst = Graphic(tilePickerPreview_.nativeW()
                  * tilePickerPreview_.sceneScale(),
                tilePickerPreview_.nativeH()
                  * tilePickerPreview_.sceneScale());
  
  tilePickerPreview_.render(dst,
                         Box(0, 0,
                             tilePickerPreview_.nativeW(),
                             tilePickerPreview_.nativeH()),
                         1.00);
}

int TileMapEditor::numTileMaps() {
  return tileMaps_.size();
}

void TileMapEditor::changeTileMap(int index) {
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
  
  tilePickerPreview_ = GraphicTilePickerScene(
                        levelGraphicsData_.compressedGraphic(
                          info.graphicNum),
                        standardPalettes_.palette(
                          info.paletteNum));
  tilePickerPreview_.setGridLayerEnabled(gridEnabled_);
  tilePickerPreview_.setSceneScale(2.00);
  
  currentIndex_ = index;
  
  updateFromTileMap();
}

bool TileMapEditor::currentEditingLimited() const {
  switch (currentTileMapInfo().format) {
  case TileMap::oneBytePerTile:
    return true;
    break;
  case TileMap::twoBytesPerTile:
    return false;
    break;
  default:
    return false;
    break;
  }
}

std::string TileMapEditor::nameOfTileMap(int index) const {
  return (TileMapInfos::tileMapInfo(index).name);
}

TileMap& TileMapEditor::currentTileMap() {
  return tileMaps_.tileMap(currentIndex_);
}

TileReference& TileMapEditor::currentTile() {
  return currentTileMap().tileData(tileMapPreview_.pickedIndex()
                              % currentTileMapInfo().w,
                            tileMapPreview_.pickedIndex()
                              / currentTileMapInfo().w);
}

TileMapInfo TileMapEditor::currentTileMapInfo() const {
  return TileMapInfos::tileMapInfo(currentIndex_);
}
  
int TileMapEditor::currentIndex() const {
  return currentIndex_;
}

bool TileMapEditor::gridEnabled() const {
  return gridEnabled_;
}
  
void TileMapEditor::setGridEnabled(bool gridEnabled__) {
  gridEnabled_ = gridEnabled__;
  tileMapPreview_.setGridLayerEnabled(gridEnabled__);
  tilePickerPreview_.setGridLayerEnabled(gridEnabled__);
}
  
void TileMapEditor::tileMapEnter() {
  tileMapPreview_.enterMouse();
//  updateFromTileMap();
}

void TileMapEditor::tileMapExit() {
  tileMapPreview_.exitMouse();
//  updateFromTileMap();
}

void TileMapEditor::tileMapMouseMove(InputEventData eventData) {
  tileMapPreview_.moveMouse(eventData);
//  updateFromTileMap();
}

void TileMapEditor::tileMapMousePress(InputEventData eventData) {
  tileMapPreview_.pressMouse(eventData);
  updateFromTileMap();
}

void TileMapEditor::tileMapMouseRelease(InputEventData eventData) {
  tileMapPreview_.releaseMouse(eventData);
//  updateFromTileMap();
}

void TileMapEditor::tileMapMouseDoubleClick(InputEventData eventData) {
  tileMapPreview_.doubleClickMouse(eventData);
//  updateFromTileMap();
}

void TileMapEditor::tilePickerEnter() {
  tilePickerPreview_.enterMouse();
//  updateFromTilePicker();
}

void TileMapEditor::tilePickerExit() {
  tilePickerPreview_.exitMouse();
//  updateFromTilePicker();
}

void TileMapEditor::tilePickerMouseMove(InputEventData eventData) {
  tilePickerPreview_.moveMouse(eventData);
//  updateFromTilePicker();
}

void TileMapEditor::tilePickerMousePress(InputEventData eventData) {
  tilePickerPreview_.pressMouse(eventData);
  updateFromTilePicker();
}

void TileMapEditor::tilePickerMouseRelease(InputEventData eventData) {
  tilePickerPreview_.releaseMouse(eventData);
//  updateFromTilePicker();
}

void TileMapEditor::tilePickerMouseDoubleClick(InputEventData eventData) {
  tilePickerPreview_.doubleClickMouse(eventData);
//  updateFromTilePicker();
}

void TileMapEditor::updateFromTileMap() {
  tilePickerPreview_.pickIndex(currentTile().tileNum()
                                      + currentTileMapInfo().offset);
}
  
void TileMapEditor::updateFromTilePicker() {
  currentTile().setTileNum(
    tilePickerPreview_.pickedIndex() - currentTileMapInfo().offset);
}


};
