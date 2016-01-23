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
  
int TileMapEditor::currentIndex() {
  return currentIndex_;
}


};
