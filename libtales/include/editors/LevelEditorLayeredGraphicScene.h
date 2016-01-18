#ifndef LEVELEDITORLAYEREDGRAPHICSCENE_H
#define LEVELEDITORLAYEREDGRAPHICSCENE_H


#include "structs/LayeredGraphicScene.h"
#include "structs/InputEventData.h"
#include "editors/GridGraphicSceneLayer.h"
#include "editors/LevelVisualGraphicSceneLayer.h"
#include "editors/LevelEffectGraphicSceneLayer.h"
#include "editors/LevelSolidityGraphicSceneLayer.h"
#include "editors/LevelObjectGraphicSceneLayer.h"
#include "editors/LevelBoundsGraphicSceneLayer.h"
#include "editors/LevelSpawnGraphicSceneLayer.h"
#include "editors/VRAMCache.h"
#include "editors/LevelEditorToolManager.h"
#include "gamedata/EditableLevelEffectsHeaders.h"
#include "gamedata/EditableLevelGraphicsData.h"
#include "gamedata/EditableLevelObjectEntryGroups.h"
#include "gamedata/EditableLevelPaletteHeaders.h"
#include "gamedata/EditableMapData.h"
#include "gamedata/EditableMetatileBehaviors.h"
#include "gamedata/EditableMetatileHeightMaps.h"
#include "gamedata/EditableMetatileWidthMaps.h"
#include "gamedata/EditableSpawnPoints.h"
#include "gamedata/EditableSpriteMappings.h"
#include "gamedata/EditableStandardPalettes.h"
#include "gamedata/EditableWarpDestinations.h"
#include <list>

namespace Tales {


class LevelEditorLayeredGraphicScene : public LayeredGraphicScene {
public:

  /**
   * Constructor.
   */
  LevelEditorLayeredGraphicScene(
              EditableLevelEffectsHeaders& levelEffectsHeaders__,
              EditableLevelGraphicsData& levelGraphicsData__,
              EditableLevelObjectEntryGroups& levelObjectEntryGroups__,
              EditableLevelPaletteHeaders& paletteHeaders__,
              EditableMapData& mapData__,
              EditableMetatileBehaviors& metatileBehaviors__,
              EditableMetatileHeightMaps& metatileHeightMaps__,
              EditableMetatileWidthMaps& metatileWidthMaps__,
              EditableSpawnPoints& spawnPoints__,
              EditableSpriteMappings& spriteMappings__,
              EditableStandardPalettes& palettes__,
              EditableWarpDestinations& warpDestinations__,
              LevelEditorToolManager& toolManager__,
              VRAMCache& vramCache__);
  
  /**
   * Renders scene to a Graphic.
   * @param dst Graphic to render to. Existing contents are discarded.
   * @param srcbox Box indicating the area of the contained Scene to be
   * rendered to the Graphic.
   */
  virtual void render(Graphic& dst,
                      Box srcbox,
                      double scale);
  
  void setObjectEditDialogCallback(
          bool (*objectEditDialogCallback__)(
            LevelObjectGraphicSceneLayer&,LevelObjectEntry&,void*),
          void* objectEditDialogCallbackParam__);
  void setObjectUpdateCallback(
          void (*objectUpdateCallback__)(
            LevelObjectGraphicSceneLayer&,void*),
          void* objectUpdateCallbackParam__);
  void setObjectSelectionCallback(
          void (*objectSelectionCallback__)(
            LevelObjectGraphicSceneLayer&,
            LevelObjectEntryCollection::iterator,
            void*),
          void* objectSelectionCallbackParam__);
  void setSpawnEditDialogCallback(
          bool (*spawnEditDialogCallback__)(
            LevelSpawnGraphicSceneLayer&,SpawnPoint&,void*),
          void* spawnEditDialogCallbackParam__);
  
  LevelObjectEntryGroup* currentObjectGroup();
  
  void selectObjectAtIndex(int index);
  void eraseObjectAtIndex(int index);
  void editSelectedObject();
  bool editAndAppendObject();
  void refreshAllObjectVRAMOffsets();
  
  int currentLevelMetatileWidth();
  void setCurrentLevelMetatileWidth(int width__);
  int currentLevelMetatileHeight();
  LevelHeader& currentLevelHeader();
                      
/*  virtual void render(Graphic& dst,
                      WrapScrollGraphic& cache,
                      Box srcbox,
                      double scale); */
  
  void changeMap(int levelHeaderIndex__);
  
  void resetSelection();
  
  void enterMouse();
  void exitMouse();
  void moveMouse(int x, int y, InputEventData eventData);
  void pressMouse(int x, int y, InputEventData eventData);
  void doubleClickMouse(int x, int y, InputEventData eventData);
  void releaseMouse(int x, int y, InputEventData eventData);
  
  int areaNum() const;
  int mapNum() const;
  int levelHeaderIndex() const;
  
  int scrollX() const;
  void setScrollX(int scrollX__);
  int scrollY() const;
  void setScrollY(int scrollY__);
  
  double scale() const;
  void setScale(double scale__);
  
  bool bgLayerEnabled() const;
  void setBGLayerEnabled(bool bgLayerEnabled__);
  bool objectLayerEnabled() const;
  void setObjectLayerEnabled(bool objectLayerEnabled__);
  bool fgLayerEnabled() const;
  void setFGLayerEnabled(bool fgLayerEnabled__);
  bool effectLayerEnabled() const;
  void setEffectLayerEnabled(bool effectLayerEnabled__);
  bool verticalSolidityLayerEnabled() const;
  void setVerticalSolidityLayerEnabled(
      bool verticalSolidityLayerEnabled__);
  bool horizontalSolidityLayerEnabled() const;
  void setHorizontalSolidityLayerEnabled(
      bool horizontalSolidityLayerEnabled__);
  bool spawnLayerEnabled() const;
  void setSpawnLayerEnabled(bool spawnLayerEnabled__);
  bool gridEnabled() const;
  void setGridEnabled(bool gridEnabled__);
  bool boundsLayerEnabled() const;
  void setBoundsLayerEnabled(bool boundsLayerEnabled__);
  
  int cameraTopBound();
  int cameraBottomBound();
  int cameraLeftBound();
  int cameraRightBound();
  void setCameraTopBound(int cameraTopBound__);
  void setCameraBottomBound(int cameraBottomBound__);
  void setCameraLeftBound(int cameraLeftBound__);
  void setCameraRightBound(int cameraRightBound__);
  
protected:

  enum TileDrawPriority {
    tilePriorityBG,
    tilePriorityFG
  };
  
  void drawToolPreview(Graphic& dst,
                       Box srcbox,
                       double scale);
                       
  void triggerMetatilePaint(InputEventData eventData);
  void doMetatileAreaClone(int x, int y, InputEventData eventData);
  void doMetatileAreaCloneRelease(int x, int y, InputEventData eventData);
  
  void metatileAreaCloneClickStep(int x, int y, InputEventData eventData);
  void metatileAreaCloneSelectionStep(int x, int y, InputEventData eventData);
  void metatileAreaCloneCloneStep(int x, int y, InputEventData eventData);
  
  void renderMetatile(Graphic& dst,
                      int metatileID,
                      int x, int y);
  
  int metatileIndexToX(int index);
  int metatileIndexToY(int index);
  int coordinateToMetatileIndex(int x, int y);
  int relativeXToMetatile(int x);
  int relativeYToMetatile(int y);
  int relativeToRealX(int x);
  int relativeToRealY(int y);
  int metatileXToRelative(int x);
  int metatileYToRelative(int y);
  MapLayout& currentMapLayout();
  
  bool (*objectEditDialogCallback_)(
          LevelObjectGraphicSceneLayer&,LevelObjectEntry&,void*);
  void* objectEditDialogCallbackParam_;
  void (*objectUpdateCallback_)(
          LevelObjectGraphicSceneLayer&,void*);
  void* objectUpdateCallbackParam_;
  void (*objectSelectionCallback_)(
          LevelObjectGraphicSceneLayer&,
          LevelObjectEntryCollection::iterator,
          void*);
  void* objectSelectionCallbackParam_;
  bool (*spawnEditDialogCallback_)(
          LevelSpawnGraphicSceneLayer&,SpawnPoint&,void*);
  void* spawnEditDialogCallbackParam_;

  EditableLevelEffectsHeaders& levelEffectsHeaders_;
  EditableLevelGraphicsData& levelGraphicsData_;
  EditableLevelObjectEntryGroups& levelObjectEntryGroups_;
  EditableLevelPaletteHeaders& paletteHeaders_;
  EditableMapData& mapData_;
  EditableMetatileBehaviors& metatileBehaviors_;
  EditableMetatileHeightMaps& metatileHeightMaps_;
  EditableMetatileWidthMaps& metatileWidthMaps_;
  EditableSpawnPoints& spawnPoints_;
  EditableSpriteMappings& spriteMappings_;
  EditableStandardPalettes& palettes_;
  EditableWarpDestinations& warpDestinations_;
  
  LevelEditorToolManager& toolManager_;
  
  VRAMCache& vramCache_;
  
  Graphic sourceCache_;
  
  /**
   * Area number (for everything except map data).
   */
  int areaNum_;
  
  /**
   * Map number (for everything except map data).
   */
  int mapNum_;
  
  /**
   * Level header index.
   * Due to an idiosyncracy in the way boss arenas are stored in the data,
   * not every map stored in the game is actually associated with an
   * area/mapnum pair. To handle those maps, we have to separately
   * handle the area/mapnum used to access the map's non-structural data
   * and the map index number identifying the map.
   * This gives the value of the 
   */
  int levelHeaderIndex_;
  
  bool bgLayerEnabled_;
  bool objectLayerEnabled_;
  bool fgLayerEnabled_;
  bool effectLayerEnabled_;
  bool verticalSolidityLayerEnabled_;
  bool horizontalSolidityLayerEnabled_;
  bool spawnLayerEnabled_;
  bool gridEnabled_;
  bool boundsLayerEnabled_;
  
  bool highlightedMetatileBoxEnabled_;
  int highlightedMetatileIndex_;
  
  int scrollX_;
  int scrollY_;
  
  int lastScrollX_;
  int lastScrollY_;
  
  double scale_;
  
  LevelVisualGraphicSceneLayer bgLayer_;
  
  LevelObjectGraphicSceneLayer objectLayer_;
  
  LevelVisualGraphicSceneLayer fgLayer_;
  
  LevelEffectGraphicSceneLayer effectLayer_;
  
  LevelSolidityGraphicSceneLayer verticalSolidityLayer_;
  
  LevelSolidityGraphicSceneLayer horizontalSolidityLayer_;
  
  LevelSpawnGraphicSceneLayer spawnLayer_;
  
  GridGraphicSceneLayer grid_;
  
  LevelBoundsGraphicSceneLayer boundsLayer_;
  
};


};


#endif
