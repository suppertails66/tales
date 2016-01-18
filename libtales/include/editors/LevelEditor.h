#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H


#include "editors/BaseEditor.h"
#include "editors/LevelEditorLayeredGraphicScene.h"
#include "editors/MetatilePickerLayeredGraphicScene.h"
#include "editors/LevelEditorTool.h"
#include "editors/LevelEditorToolManager.h"
#include "structs/WrapScrollGraphic.h"
#include "editors/MetatileBehaviorEditor.h"
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
#include "editors/EditorMetadata.h"

namespace Tales {


class LevelEditor : public BaseEditor {
public:
  enum LevelViewMode {
    viewLevelVisual = 0,
    viewLevelEffect,
    viewLevelVerticalSolidity,
    viewLevelHorizontalSolidity
  };

  LevelEditor(EditableLevelEffectsHeaders& levelEffectsHeaders__,
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
              EditorMetadata& metadata__);
  
  virtual void refresh();
  
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
  
  void changeMap(int levelHeaderIndex__);
  
  void metatilePickerEnterMouse();
  void metatilePickerExitMouse();
  void metatilePickerMoveMouse(int x, int y, InputEventData eventData);
  void metatilePickerPressMouse(int x, int y, InputEventData eventData);
  
  void levelEditorEnterMouse();
  void levelEditorExitMouse();
  void levelEditorMoveMouse(int x, int y, InputEventData eventData);
  void levelEditorPressMouse(int x, int y, InputEventData eventData);
  void levelEditorDoubleClickMouse(int x, int y, InputEventData eventData);
  void levelEditorReleaseMouse(int x, int y, InputEventData eventData);
  
  void moveCurrentLevelSpawnsInBounds();
  
  LevelEditorTools::LevelEditorTool currentTool() const;
  void changeTool(LevelEditorTools::LevelEditorTool tool);
  
  double scale() const;
  void setScale(double scale__);
  
  void drawPreviewGraphic(Graphic& dst);
  void drawMetatilePickerGraphic(Graphic& dst);
  
  LevelObjectEntryGroup* currentObjectGroup();
  
  void selectObjectAtIndex(int index);
  void eraseObjectAtIndex(int index);
  void editSelectedObject();
  bool editAndAppendObject();
  void refreshAllObjectVRAMOffsets();
  
  int currentLevelWidth();
  void setCurrentLevelWidth(int width__);
  LevelEffectsHeader& currentLevelEffectsHeader();
  
  bool currentLevelHasWarps();
  WarpDestinationCollection& currentLevelWarps();
  EditableSpawnPoints& spawnPoints();
  
  LevelEditorToolManager& toolManager();
  
  LevelHeaders& levelHeaders();
  
  LevelViewMode levelViewMode() const;
  void setLevelViewMode(LevelViewMode levelViewMode__);
  
  void setBGEnabled(bool bgEnabled__);
  void setObjectsEnabled(bool objectsEnabled__);
  void setFGEnabled(bool fgEnabled__);
  void setSpawnsEnabled(bool spawnsEnabled__);
  void setBoundsEnabled(bool boundsEnabled__);
  
  int scrollX() const;
  int scrollY() const;
  
  void setScrollX(int scrollX__);
  void setScrollY(int scrollY__);
  
  int maxScrollX();
  int maxScrollY();
  
  bool gridEnabled() const;
  void setGridEnabled(bool gridEnabled__);
  
  int cameraTopBound();
  int cameraBottomBound();
  int cameraLeftBound();
  int cameraRightBound();
  void setCameraTopBound(int cameraTopBound__);
  void setCameraBottomBound(int cameraBottomBound__);
  void setCameraLeftBound(int cameraLeftBound__);
  void setCameraRightBound(int cameraRightBound__);
  
  LevelPaletteHeader& currentLevelPaletteHeader();
  
  int numPalettes();
  int numMetatileStructureSets();
  
  int currentLevelMetatileStructureIndex();
  void setCurrentLevelMetatileStructureIndex(int index);
  
  std::string nameOfArea(int areaNum);
  
  EditorMetadata& metadata();
  
protected:
  
  void cacheVRAM(int levelHeaderIndex);
  
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
  EditorMetadata& metadata_;
  
  LevelEditorToolManager toolManager_;
  
  VRAMCache vramCache_;
  
  LevelEditorLayeredGraphicScene previewScene_;
  MetatilePickerLayeredGraphicScene metatilePickerScene_;
  
//  WrapScrollGraphic wrapScrollCache_;
  
//  bool needWrapCacheRefresh_;
  
//  int lastRenderedScrollX_;
//  int lastRenderedScrollY_;

  LevelViewMode levelViewMode_;
  
//  int scrollX_;
//  int scrollY_;
  
};


};


#endif
