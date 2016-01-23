#ifndef TILEMAPEDITORTOOLMANAGER_H
#define TILEMAPEDITORTOOLMANAGER_H


#include "editors/TileMapEditorTool.h"

namespace Tales {


class TileMapEditorToolManager {
public:
  TileMapEditorToolManager();
  
  TileMapEditorTools::TileMapEditorTool currentTool() const;
  void changeTool(TileMapEditorTools::TileMapEditorTool tool);
  
  int pencilDrawIndex() const;
  void setPencilDrawIndex(int pencilDrawIndex__);
protected:
  TileMapEditorTools::TileMapEditorTool currentTool_;
  
  int pencilDrawIndex_;
};


};


#endif
