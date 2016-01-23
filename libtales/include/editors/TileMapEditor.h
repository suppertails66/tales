#ifndef TILEMAPEDITOR_H
#define TILEMAPEDITOR_H


#include "editors/BaseEditor.h"
#include "gamedata/EditableTileMaps.h"
#include "gamedata/EditableLevelGraphicsData.h"
#include "gamedata/EditableStandardPalettes.h"

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
   * Returns number of selectable tilemap indices.
   * @return Number of selectable tilemap indices.
   */
  int numTileMaps();
  
  /**
   * Selects the tilemap at the given index.
   * @param index New tilemap index.
   */
  int changeTileMap(int index);
  
  /**
   * Getter.
   */
  int currentIndex();
protected:
  EditableTileMaps& tileMaps_;
  EditableLevelGraphicsData& levelGraphicsData_;
  EditableStandardPalettes& standardPalettes_;
  
  /**
   * Index of the currently selected tilemap.
   */
  int currentIndex_;
};


};


#endif
