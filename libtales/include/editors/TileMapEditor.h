#ifndef TILEMAPEDITOR_H
#define TILEMAPEDITOR_H


#include "editors/BaseEditor.h"
#include "editors/TileMapEditorToolManager.h"
#include "editors/TileMapPickerScene.h"
#include "editors/GraphicTilePickerScene.h"
#include "gamedata/EditableTileMaps.h"
#include "gamedata/EditableLevelGraphicsData.h"
#include "gamedata/EditableStandardPalettes.h"
#include "gamedata/TileMapInfos.h"
#include "structs/Graphic.h"
#include "structs/InputEventData.h"

namespace Tales {


/**
 * Editor class for fixed-layout tilemaps.
 */
class TileMapEditor : public BaseEditor {
public:
  /**
   * Default constructor.
   */
  TileMapEditor(EditableTileMaps& tileMaps__,
                EditableLevelGraphicsData& levelGraphicsData__,
                EditableStandardPalettes& standardPalettes__);
  
  /**
   * Refreshes loaded data.
   */
  virtual void refresh();
  
  /**
   * Draws the tilemap preview.
   * @param dst Graphic to draw to.
   */
  void drawTileMapPreview(Graphic& dst);
  
  /**
   * Draws the tile picker.
   * @param dst Graphic to draw to.
   */
  void drawTilePicker(Graphic& dst);
  
  /**
   * Returns number of selectable tilemap indices.
   * @return Number of selectable tilemap indices.
   */
  int numTileMaps();
  
  /**
   * Selects the tilemap at the given index.
   * @param index New tilemap index.
   */
  void changeTileMap(int index);
  
  /**
   * Returns true if editing is limited to tile number for the current tilemap.
   * @return True if editing is limited to tile number for the current tilemap.
   */
  bool currentEditingLimited() const;
  
  /**
   * Returns name of the tilemap at the given index.
   * @param index Index of the tilemap.
   * @return Name of the tilemap at the given index.
   */
  std::string nameOfTileMap(int index) const;
  
  /**
   * Returns the current tilemap.
   * @return The current tilemap.
   */
  TileMap& currentTileMap();
  
  /**
   * Returns the currently selected tile of the tilemap.
   * @return The currently selected tile of the tilemap.
   */
  TileReference& currentTile();
  
  /**
   * Getter.
   */
  int currentIndex() const;
  
  bool gridEnabled() const;
  void setGridEnabled(bool gridEnabled__);
  
  void tileMapEnter();
  void tileMapExit();
  void tileMapMouseMove(InputEventData eventData);
  void tileMapMousePress(InputEventData eventData);
  void tileMapMouseRelease(InputEventData eventData);
  void tileMapMouseDoubleClick(InputEventData eventData);
  
  void tilePickerEnter();
  void tilePickerExit();
  void tilePickerMouseMove(InputEventData eventData);
  void tilePickerMousePress(InputEventData eventData);
  void tilePickerMouseRelease(InputEventData eventData);
  void tilePickerMouseDoubleClick(InputEventData eventData);
protected:
  TileMapInfo currentTileMapInfo() const;
  
  void updateFromTileMap();
  void updateFromTilePicker();
  
  TileMapEditorToolManager toolManager_;

  EditableTileMaps& tileMaps_;
  EditableLevelGraphicsData& levelGraphicsData_;
  EditableStandardPalettes& standardPalettes_;
  
  /**
   * Index of the currently selected tilemap.
   */
  int currentIndex_;
  
  TileMapPickerScene tileMapPreview_;
  
  GraphicTilePickerScene tilePickerPreview_;
  
  bool gridEnabled_;
};


};


#endif
