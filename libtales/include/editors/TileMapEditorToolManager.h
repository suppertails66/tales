#ifndef TILEMAPEDITORTOOLMANAGER_H
#define TILEMAPEDITORTOOLMANAGER_H


#include "editors/TileMapEditorTool.h"

namespace Tales {


class TileMapEditorToolManager {
public:
  TileMapEditorToolManager();
  
  TileMapEditorTools::TileMapEditorTool currentTool() const;
  void changeTool(TileMapEditorTools::TileMapEditorTool tool);
protected:
  TileMapEditorTools::TileMapEditorTool currentTool_;
};


};


#endif
