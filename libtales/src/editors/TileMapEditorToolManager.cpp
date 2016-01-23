#include "editors/TileMapEditorToolManager.h"

namespace Tales {


TileMapEditorToolManager::TileMapEditorToolManager()
  : currentTool_(TileMapEditorTools::regular) { };
  
TileMapEditorTools::TileMapEditorTool TileMapEditorToolManager
    ::currentTool() const {
  return currentTool_;
}

void TileMapEditorToolManager
    ::changeTool(TileMapEditorTools::TileMapEditorTool tool) {
  currentTool_ = tool;
}


};
