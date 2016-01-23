#include "editors/TileMapEditor.h"
#include "exception/OutOfRangeIndexException.h"

namespace Tales {


TileMapEditor::TileMapEditor(EditableTileMaps& tileMaps__,
                EditableLevelGraphicsData& levelGraphicsData__,
                EditableStandardPalettes& standardPalettes__)
  : tileMaps_(tileMaps__),
    levelGraphicsData_(levelGraphicsData__),
    standardPalettes_(standardPalettes__),
    currentIndex_(0) { };

void TileMapEditor::refresh() {
  
}

void TileMapEditor::drawTileMapPreview(Graphic& dst) {
  
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
  
  currentIndex_ = index;
}

std::string TileMapEditor::nameOfTileMap(int index) {
  return (TileMapInfos::tileMapInfo(index).name);
}
  
int TileMapEditor::currentIndex() {
  return currentIndex_;
}
  
void TileMapEditor::tileMapEnter() {
  
}

void TileMapEditor::tileMapExit() {
  
}

void TileMapEditor::tileMapMouseMove(InputEventData eventData) {
  
}

void TileMapEditor::tileMapMousePress(InputEventData eventData) {
  
}

void TileMapEditor::tileMapMouseRelease(InputEventData eventData) {
  
}

void TileMapEditor::tileMapMouseDoubleClick(InputEventData eventData) {
  
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
