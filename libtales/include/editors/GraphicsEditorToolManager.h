#ifndef GRAPHICSEDITORTOOLMANAGER_H
#define GRAPHICSEDITORTOOLMANAGER_H


#include "editors/GraphicsEditorTool.h"
#include "gamegear/GGPalette.h"
#include "gamegear/GGTileSet.h"
#include "gamedata/SpriteMapping.h"
#include "gamedata/SpriteMappingCoordinateTable.h"
#include "gamedata/SpriteMappingTileIndexTable.h"
#include "editors/GraphicToMappingEntry.h"

namespace Tales {


class GraphicsEditorToolManager {
public:
  GraphicsEditorToolManager();
  
  GraphicsEditorTools::GraphicsEditorTool currentTool() const;
  void changeCurrentTool(
      GraphicsEditorTools::GraphicsEditorTool currentTool__);
      
  double scale();
  void setScale(double scale__);
  
  GGPalette& palette();
  void setPalette(GGPalette& palette__);
  
  GGTileSet& tiles();
  void setTiles(GGTileSet& tiles__);
  
  SpriteMapping& mapping();
  void setMapping(SpriteMapping& mapping__);
  
  SpriteMappingCoordinateTable& mappingCoordinateTable();
  void setMappingCoordinateTable(SpriteMappingCoordinateTable&
      mappingCoordinateTable__);
  
  SpriteMappingTileIndexTable& mappingTileIndexTable();
  void setMappingTileIndexTable(SpriteMappingTileIndexTable&
      mappingTileIndexTable__);
  
  GraphicToMappingEntry& mappingEntry();
  void setMappingEntry(GraphicToMappingEntry&
      mappingEntry__);
      
  bool gridEnabled();
  void setGridEnabled(bool gridEnabled__);
      
  bool collisionViewEnabled();
  void setCollisionViewEnabled(bool collisionViewEnabled__);
  
  Graphic::TileTransferTransOption transOption();
  void setTransOption(Graphic::TileTransferTransOption transOption__);
  
  int currentColorIndex();
  void setCurrentColorIndex(int currentColorIndex__);
  
  bool pencilPreviewEnabled();
  int pencilTileIndex();
  int pencilTileX();
  int pencilTileY();
  void setPencilPreviewEnabled(bool pencilPreviewEnabled__);
  void setPencilTileIndex(int pencilTileIndex__);
  void setPencilTileX(int pencilTileX__);
  void setPencilTileY(int pencilTileY__);
  
  bool mappingExists();
  void clearMapping();
protected:
  GraphicsEditorTools::GraphicsEditorTool currentTool_;
  
  double scale_;
  
  GGPalette* palette_;
  
  GGTileSet* tiles_;
  
  SpriteMapping* mapping_;
  SpriteMappingCoordinateTable* mappingCoordinateTable_;
  SpriteMappingTileIndexTable* mappingTileIndexTable_;
  GraphicToMappingEntry mappingEntry_;
  
  bool gridEnabled_;
  
  bool collisionViewEnabled_;
  
  Graphic::TileTransferTransOption transOption_;
  
  int currentColorIndex_;
  
  bool pencilPreviewEnabled_;
  int pencilTileIndex_;
  int pencilTileX_;
  int pencilTileY_;
  
};


};


#endif
