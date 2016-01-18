#ifndef LEVELSPAWNGRAPHICSCENELAYER_H
#define LEVELSPAWNGRAPHICSCENELAYER_H


#include "structs/GraphicSceneLayer.h"
#include "editors/LevelEditorToolManager.h"
#include "gamedata/EditableSpawnPoints.h"
#include "gamedata/EditableLevelGraphicsData.h"
#include "gamedata/EditableSpriteMappings.h"
#include "gamedata/MappingToGraphic.h"
#include "gamegear/GGPalette.h"
#include "editors/MappingAssembler.h"
#include "editors/ObjectDisplayCacheCollection.h"
#include "structs/InputEventData.h"

namespace Tales {


class LevelSpawnGraphicSceneLayer : public GraphicSceneLayer {
public:
  LevelSpawnGraphicSceneLayer(LevelEditorToolManager& toolManager__,
                              SpawnPointCollection* spawns__,
                              EditableLevelGraphicsData& levelGraphicsData__,
                              EditableSpriteMappings& spriteMappings__,
                              GGPalette& palette0__,
                              GGPalette& palette1__,
                              int areaNum__);
  
  virtual void render(Graphic& dst,
                      Box srcbox,
                      double scale);

  void setSpawnEditDialogCallback(
          bool (*spawnEditDialogCallback__)(
            LevelSpawnGraphicSceneLayer&,SpawnPoint&,void*),
          void* spawnEditDialogCallbackParam__);
          
  int selectedSpawnNumber();
                             
  void moveMouse(int realX, int realY, InputEventData eventData);
  void pressMouse(int realX, int realY, InputEventData eventData);
  void doubleClickMouse(int realX, int realY, InputEventData eventData);
  void releaseMouse(int realX, int realY, InputEventData eventData);
  
  void selectSpawn(ObjectDisplayCacheCollection::iterator cacheIt,
                    SpawnPointCollection::iterator groupIt);
protected:

  bool pointOverlaps(int realX, int realY,
                     ObjectDisplayCacheCollection::iterator cacheIt,
                     SpawnPointCollection::iterator groupIt);
                     
  void handleInitialClick(int realX, int realY, InputEventData eventData);
  void handleSelectionClick(int realX, int realY, InputEventData eventData);
  void handleSelectionDrag(int realX, int realY, InputEventData eventData);
  
  void searchAndSelectOrDeselect(int realX, int realY);

  const static int marginLeft_ = 5 * 8;
  const static int marginRight_ = marginLeft_ + (21 * 8);
  const static int marginTop_ = 5 * 8;
  const static int marginBottom_ = marginTop_ + (18 * 8);

  void regenerateDisplayCaches();
  
  LevelEditorToolManager* toolManager_;
  SpawnPointCollection* spawns_;
  EditableLevelGraphicsData* levelGraphicsData_;
  EditableSpriteMappings* spriteMappings_;
  GGPalette* palette0_;
  GGPalette* palette1_;
  int areaNum_;
  
  bool (*spawnEditDialogCallback_)(
          LevelSpawnGraphicSceneLayer&,SpawnPoint&,void*);
  void* spawnEditDialogCallbackParam_;
  
  ObjectDisplayCacheCollection spawnDisplayCaches_;
};


};


#endif
