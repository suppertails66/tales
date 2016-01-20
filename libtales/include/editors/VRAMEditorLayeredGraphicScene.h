#ifndef VRAMEDITORLAYEREDGRAPHICSCENE_H
#define VRAMEDITORLAYEREDGRAPHICSCENE_H


#include "structs/LayeredGraphicScene.h"
#include "editors/GridGraphicSceneLayer.h"
#include "gamedata/EditableLevelGraphicsData.h"
#include "gamedata/EditableLevelPaletteHeaders.h"
#include "gamedata/EditableStandardPalettes.h"
#include "gamedata/EditableLeafGraphicsTable.h"
#include "gamedata/EditableSmokePuffGraphicTable.h"
#include "gamedata/EditableWaterSplashGraphicTable.h"

namespace Tales {


class LevelVRAMEditor;

class VRAMEditorLayeredGraphicScene : public LayeredGraphicScene {
public:
  const static Color selectionBoxColor;
  const static Color fullGraphicSelectionBoxColor;
  const static Color leafBoxColor;
  const static Color smokePuffBoxColor;
  const static Color waterSplashBoxColor;

  VRAMEditorLayeredGraphicScene(
                  LevelVRAMEditor& parentEditor__,
                  EditableLevelGraphicsData& levelGraphicsData__,
                  EditableLevelPaletteHeaders& paletteHeaders__,
                  EditableStandardPalettes& palettes__,
                  EditableLeafGraphicsTable& leafGraphicsTable__,
                  EditableSmokePuffGraphicTable& smokePuffGraphicTable__,
                  EditableWaterSplashGraphicTable& waterSplashGraphicTable__);
  
  int nativeWidth() const;
 
  int nativeHeight() const;
  
  int tilesPerRow() const;
  
  /**
   * Renders scene to a Graphic.
   * @param dst Graphic to render to. Existing contents are discarded.
   * @param srcbox Box indicating the area of the contained Scene to be
   * rendered to the Graphic.
   */
  virtual void render(Graphic& dst,
                      Box srcbox,
                      double scale);
                      
  void refresh();
                      
  void findAndHandleTopGraphicIndex(int tileIndex);
                      
  void changeMap(int areaNum__,
                 int mapNum__);
                 
  bool gridEnabled() const;
  
  void setGridEnabled(bool gridEnabled__);
  
  bool selectionBoxEnabled() const;
  int selectionBoxX() const;
  int selectionBoxY() const;
  
  void setSelectionBoxEnabled(bool selectionBoxEnabled__);
  void setSelectionBoxX(int selectionBoxX__);
  void setSelectionBoxY(int selectionBoxY__);
  
  bool fullSelectionBoxEnabled() const;
  int fullSelectionBoxGraphicIndex() const;
  
  void setFullSelectionBoxEnabled(bool fullSelectionBoxEnabled__);
  void setFullSelectionBoxGraphicIndex(int fullSelectionBoxGraphicIndex__);
  
  bool tilePickerPreviewEnabled() const;
  int tilePickerPreviewIndex() const;
  int tilePickerPreviewLength() const;
  Color tilePickerPreviewColor() const;
  
  void setTilePickerPreviewEnabled(bool tilePickerPreviewEnabled__);
  void setTilePickerPreviewIndex(int tilePickerPreviewIndex__);
  void setTilePickerPreviewLength(int tilePickerPreviewLength__);
  void setTilePickerPreviewColor(Color tilePickerPreviewColor__);
  
  int tileIndexToXPos(int tileIndex) const;
  int tileIndexToYPos(int tileIndex) const;
  
  int tilePosToTileIndex(int tileX, int tileY);
  
  bool showLeaf() const;
  void setShowLeaf(bool showLeaf__);
  
  bool showSmokePuff() const;
  void setShowSmokePuff(bool showSmokePuff__);
  
  bool showWaterSplash() const;
  void setShowWaterSplash(bool showWaterSplash__);
protected:

  const static int vramAddressToTileIndexDivisor = 32;

  const static int tilesPerRow_ = 16;
  
  const static int numVRAMTiles = 512;
  
  void renderTiles(Graphic& g,
                   int tileIndex,
                   GGTileSet& tiles,
                   GGPalette& palette,
                   Graphic::TileTransferTransOption tileTransOption);
  
  static int vramAddressToTileIndex(int vramAddress);
  
  void boxGenericLength(Graphic& dst,
                      int baseIndex,
                      int numTiles,
                      Color color,
                      int width,
                      double scale);

  LevelVRAMEditor& parentEditor_;

  EditableLevelGraphicsData& levelGraphicsData_;
  
  EditableLevelPaletteHeaders& paletteHeaders_;
  
  EditableStandardPalettes& palettes_;
  
  EditableLeafGraphicsTable& leafGraphicsTable_;
  
  EditableSmokePuffGraphicTable& smokePuffGraphicTable_;
  
  EditableWaterSplashGraphicTable& waterSplashGraphicTable_;
  
  /**
   * Graphic cache to avoid repetitive memory de- and re-allocation.
   * Name is for quick and dirty compatibility.
   */
  Graphic g_;
  
  GridGraphicSceneLayer grid_;
  
  bool gridEnabled_;
  
  int areaNum_;
  
  int mapNum_;
  
  bool selectionBoxEnabled_;
  int selectionBoxX_;
  int selectionBoxY_;
  
  bool fullSelectionBoxEnabled_;
  int fullSelectionBoxGraphicIndex_;
  
  bool tilePickerPreviewEnabled_;
  int tilePickerPreviewIndex_;
  int tilePickerPreviewLength_;
  Color tilePickerPreviewColor_;
  
  bool showLeaf_;
  
  bool showSmokePuff_;
  
  bool showWaterSplash_;
  
};


};


#endif
