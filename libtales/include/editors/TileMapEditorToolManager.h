#ifndef TILEMAPEDITORTOOLMANAGER_H
#define TILEMAPEDITORTOOLMANAGER_H


#include "editors/TileMapEditorTool.h"
#include "gamedata/TileMap.h"
#include "gamegear/TileReference.h"

namespace Tales {


class TileMapEditorToolManager {
public:
  TileMapEditorToolManager();
  
  ~TileMapEditorToolManager();
  
  TileMapEditorTools::TileMapEditorTool currentTool() const;
  void changeTool(TileMapEditorTools::TileMapEditorTool tool);
  
  void resetTools();
  
  int pencilDrawIndex() const;
  void setPencilDrawIndex(int pencilDrawIndex__);
  
  void finalizeCloneArea(TileMap& tileMap);
  
  TileReference areaCloneBuffer(int x, int y);
  
  TileMapEditorTools::AreaCloneState areaCloneState() const;
  int areaCloneBaseX() const;
  int areaCloneBaseY() const;
  int areaCloneW() const;
  int areaCloneH() const;
  
  void setAreaCloneState(
      TileMapEditorTools::AreaCloneState areaCloneState__);
  void setAreaCloneBaseX(
      int areaCloneBaseX__);
  void setAreaCloneBaseY(
      int areaCloneBaseY__);
  void setAreaCloneW(
      int areaCloneW__);
  void setAreaCloneH(
      int areaCloneH__);
  
protected:
  void clearAreaCloneBuffer();
  void reinitializeAreaCloneBuffer(int w, int h);

  TileMapEditorTools::TileMapEditorTool currentTool_;
  
  int pencilDrawIndex_;
  
  TileMapEditorTools::AreaCloneState areaCloneState_;
  int areaCloneBaseX_;
  int areaCloneBaseY_;
  int areaCloneW_;
  int areaCloneH_;
  TileReference** areaCloneBuffer_;
};


};


#endif
