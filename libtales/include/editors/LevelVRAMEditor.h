#ifndef LEVELVRAMEDITOR_H
#define LEVELVRAMEDITOR_H


#include "editors/BaseEditor.h"
#include "gamedata/EditableLevelGraphicsData.h"
#include "gamedata/EditableLevelPaletteHeaders.h"
#include "gamedata/EditableStandardPalettes.h"
#include "gamedata/EditableLeafGraphicsTable.h"
#include "gamedata/EditableSmokePuffGraphicTable.h"
#include "gamedata/EditableWaterSplashGraphicTable.h"
#include "editors/EditorMetadata.h"
#include "editors/VRAMEditorLayeredGraphicScene.h"

namespace Tales {


class LevelVRAMEditor : public BaseEditor {
public:
  enum InputMode {
    standard,       /**< Click graphic to select for editing. */
    dragAndDrop,    /**< Drag graphic to move. */
    selectTile      /**< Waits for click to tile. */
  };
  
  enum SelectTileTarget {
    targetSelectedGraphicIndex,
    targetLeafIndex,
    targetSmokePuffIndex,
    targetWaterSplashIndex
  };

  LevelVRAMEditor(EditableLevelGraphicsData& levelGraphicsData__,
                  EditableLevelPaletteHeaders& paletteHeaders__,
                  EditableStandardPalettes& palettes__,
                  EditableLeafGraphicsTable& leafGraphicsTable__,
                  EditableSmokePuffGraphicTable& smokePuffGraphicTable__,
                  EditableWaterSplashGraphicTable& waterSplashGraphicTable__,
                  EditorMetadata& metadata__);
  
  virtual void refresh();
  
  void changeMap(int areaNum__,
                 int mapNum__);
                 
  int areaNum() const;
  int mapNum() const;
                 
  Graphic testRender();
  
  InputMode inputMode() const;
  
  void resetInputMode();
  
  void startSelectingTile(SelectTileTarget target);
  
  int previewWidth() const;
  
  int previewHeight() const;
  
  /**
   * Draws preview to an existing Graphic.
   * @param dst Graphic to draw to. Transparency model is not updated.
   * @see previewGraphic()
   */
  void drawPreviewGraphic(Graphic& dst);
  
  /**
   * Generates a new Graphic containing the preview image.
   * This is inherently slow due to the implicit reallocation of memory each
   * time the new Graphic is generated. Use drawPreviewGraphic() with a cached
   * Graphic for better performance.
   * @return Graphic containing preview image. Transparency model is not set.
   * @see drawPreviewGraphic()
   */
  Graphic previewGraphic();
  
  EditableLevelGraphicsData& levelGraphicsData();
  
  GGPalette& objectPalette();
  
  LevelGraphicsHeader& levelHeader();
  
  ObjectGraphicsHeader& objectHeader();
  
  ObjectGraphicSubheader& objectSubheader();
  
  EditorMetadata& metadata();
  
  bool objectIsSelected();
  
  int selectedObjectIndex();
  
  void selectObjectAtIndex(int index);
  
  void clearSelection();
  
  void moveSelectedUp();
  
  void moveSelectedDown();
  
  void eraseSelected();
  
  int mapGraphicIndex() const;
  
  void changeMapGraphic(int index);
  
  bool hasLeafIndex() const;
  int leafIndex() const;
  void setLeafIndex(int index);
  
  bool hasSmokePuffIndex() const;
  int smokePuffIndex() const;
  void setSmokePuffIndex(int index);
  
  bool hasWaterSplashIndex() const;
  int waterSplashIndex() const;
  void setWaterSplashIndex(int index);
  
  bool showLeaf() const;
  void setShowLeaf(bool showLeaf__);
  
  bool showSmokePuff() const;
  void setShowSmokePuff(bool showSmokePuff__);
  
  bool showWaterSplash() const;
  void setShowWaterSplash(bool showWaterSplash__);
  
  SelectTileTarget selectTileTarget() const;
  void setSelectTileTarget(SelectTileTarget selectTileTarget__);
  
  double scale() const;
  
  /**
   * When called, indicates a left click to the indicated point in the scene.
   * "Ideally" this would be pure virtual and we'd have various subclasses
   * implement it for each input library, but given the very limited input
   * needed for our purposes, it's not really worth the trouble.
   * @param x X-coordinate of the clicked point (scene-local).
   * @param y Y-coordinate of the clicked point (scene-local).
   * @see mouseMove()
   */
  void mouseLeftClick(int x, int y);
  
  /**
   * When called, indicates a left release to the indicated point in the scene.
   * @param x X-coordinate of the release point (scene-local).
   * @param y Y-coordinate of the release point (scene-local).
   * @see mouseClick()
   */
  void mouseLeftRelease(int x, int y);
  
  /**
   * When called, indicates a mouse movement at a point in the scene.
   * @param x X-coordinate of the clicked point (scene-local).
   * @param y Y-coordinate of the clicked point (scene-local).
   * @param leftButtonDown If nonzero, mouse button is down ("drag" event).
   * Currently functions as a bool -- this is left as an int just in case
   * it becomes necessary to add a bitfield of more specific information.
   * @see mouseLeftClick()
   */
  void mouseMove(int x, int y, int leftButtonDown);
  
  void mouseLeave();
protected:
  
  void setInputMode(InputMode inputMode__);

  void standardMouseLeftClick(int x, int y);

  void selectTileMouseLeftClick(int x, int y);

  void standardMouseMove(int x, int y, int leftButtonDown);

  void dragAndDropMouseMove(int x, int y, int leftButtonDown);
  
  void selectTileMouseMove(int x, int y, int leftButtonDown);

  VRAMEditorLayeredGraphicScene previewScene_;

  EditableLevelGraphicsData& levelGraphicsData_;
  
  EditableLevelPaletteHeaders& paletteHeaders_;
  
  EditableStandardPalettes& palettes_;
  
  EditableLeafGraphicsTable& leafGraphicsTable_;
  
  EditableSmokePuffGraphicTable& smokePuffGraphicTable_;
  
  EditableWaterSplashGraphicTable& waterSplashGraphicTable_;
  
  EditorMetadata& metadata_;
  
  InputMode inputMode_;
  
  SelectTileTarget selectTileTarget_;
  
  int dragAndDropTileOffset_;
  
  int areaNum_;
  
  int mapNum_;
  
};


};


#endif
