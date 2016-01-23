#include "editors/TileMapEditorToolManager.h"

namespace Tales {


TileMapEditorToolManager::TileMapEditorToolManager()
  : currentTool_(TileMapEditorTools::regular),
    pencilDrawIndex_(0) { };
  
TileMapEditorTools::TileMapEditorTool TileMapEditorToolManager
    ::currentTool() const {
  return currentTool_;
}

void TileMapEditorToolManager
    ::changeTool(TileMapEditorTools::TileMapEditorTool tool) {
  currentTool_ = tool;
}
  
int TileMapEditorToolManager
    ::pencilDrawIndex() const {
  return pencilDrawIndex_;
}

void TileMapEditorToolManager
    ::setPencilDrawIndex(int pencilDrawIndex__) {
  pencilDrawIndex_ = pencilDrawIndex__;
}


};
