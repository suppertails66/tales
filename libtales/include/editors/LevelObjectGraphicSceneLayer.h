#ifndef LEVELOBJECTGRAPHICSCENELAYER_H
#define LEVELOBJECTGRAPHICSCENELAYER_H


#include "structs/GraphicSceneLayer.h"
#include "editors/VRAMCache.h"
#include "gamedata/EditableLevelObjectEntryGroups.h"
#include "gamedata/EditableSpriteMappings.h"
#include "gamedata/ObjectGraphicsHeader.h"
#include "gamedata/EditableWarpDestinations.h"
#include "gamedata/EditableLevelGraphicsData.h"
#include "gamegear/GGPalette.h"
#include "editors/ObjectDisplayCache.h"
#include "editors/LevelEditorToolManager.h"
#include "structs/InputEventData.h"
#include "editors/ObjectDisplayCacheCollection.h"
#include "editors/ObjectToGraphics.h"
#include <list>

namespace Tales {


class LevelObjectGraphicSceneLayer : public GraphicSceneLayer {
public:

  static int warpParameterToLength(Tbyte parameter);
  static bool warpParameterIsVertical(Tbyte parameter);

  LevelObjectGraphicSceneLayer(const VRAMCache& vramCache__,
                               const EditableSpriteMappings&
                                 spriteMappings__,
                               const WarpDestinationCollection*
                                 warpDestinationCollection__,
                               const ObjectGraphicsHeader&
                                 objectGraphicsHeader__,
                               EditableLevelGraphicsData&
                                 levelGraphicsData__,
                               const GGPalette& palette0__,
                               const GGPalette& palette1__,
                               EditableLevelObjectEntryGroups&
                                 levelObjectEntryGroups__,
                               int levelObjectEntryGroupIndex__,
                               LevelEditorToolManager& toolManager__);
                        
  virtual void render(Graphic& dst,
                      Box srcbox,
                      double scale);
  
  void generateObjectPreview(ObjectDisplayCache& dst,
                             LevelObjectEntry entry);
  
  static int computeWidthOfMapping(
    SpriteMappingCoordinateTable coordinateTable);
  static int computeHeightOfMapping(
    SpriteMappingCoordinateTable coordinateTable);
  static Box computeDimensionsOfMapping(
    SpriteMappingCoordinateTable coordinateTable);
  
  void resetSelection();
    
  int findObjectGraphic(int index, bool wantFlipped = false);
  void refreshGraphicVRAMOffsets(LevelObjectEntry& entry,
                                 ObjectGraphicInfo graphicInfo);
  void refreshAllGraphicVRAMOffsets();
                           
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
          
  const WarpDestinationCollection* warpDestinationCollection() const;
  
  LevelObjectEntryGroup* currentGroup();
//  LevelObjectEntryCollection::iterator currentGroupBegin();
//  LevelObjectEntryCollection::iterator currentGroupEnd();

  void selectObjectAtIndex(int index);
  void eraseObjectAtIndex(int index);
  void eraseObject(ObjectDisplayCacheCollection::iterator cacheIt,
                   LevelObjectEntryCollection::iterator groupIt);
  void editSelectedObject();
  bool editAndAppendObject();
  bool appendObject(LevelObjectEntry newObject);
  void selectObject(ObjectDisplayCacheCollection::iterator cacheIt,
                    LevelObjectEntryCollection::iterator groupIt);
                             
  void moveMouse(int realX, int realY, InputEventData eventData);
  void pressMouse(int realX, int realY, InputEventData eventData);
  void doubleClickMouse(int realX, int realY, InputEventData eventData);
  void releaseMouse(int realX, int realY, InputEventData eventData);
  
protected:

  void regenerateObjectDisplayCache();
  
  void generateWarpPreview(ObjectDisplayCache& dst,
                           LevelObjectEntry entry);
  
  void generateEnemyMinePreview(ObjectDisplayCache& dst,
                           LevelObjectEntry entry);
  
  void generateMissileLauncherPreview(ObjectDisplayCache& dst,
                           LevelObjectEntry entry);
                           
  void generateItemPickupPreview(ObjectDisplayCache& dst,
                           LevelObjectEntry entry);
  
  void generateGenericPreview(ObjectDisplayCache& dst,
                            int objNum,
                            int stateNum,
                            int leftTileIndex,
                            int rightTileIndex,
                            LevelObjectEntry::XDirectionFlag
                              facingFlag);

  bool pointOverlaps(int realX, int realY,
                     ObjectDisplayCacheCollection::iterator cacheIt,
                     LevelObjectEntryCollection::iterator groupIt);

  bool boxOverlaps(Box srcbox,
                   ObjectDisplayCacheCollection::iterator cacheIt,
                   LevelObjectEntryCollection::iterator groupIt);
                     
  void handleInitialClick(int realX, int realY, InputEventData eventData);
  void handleSelectionClick(int realX, int realY, InputEventData eventData);
  void handleMultipleSelectionClick(
      int realX, int realY, InputEventData eventData);
  void handleSelectionDrag(int realX, int realY, InputEventData eventData);
  void handleMultipleSelectionPreDrag(
      int realX, int realY, InputEventData eventData);
  void handleMultipleSelectionDrag(
      int realX, int realY, InputEventData eventData);
  void handleMultipleSelectionPreRelease(
      int realX, int realY, InputEventData eventData);
  
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
  
  ObjectDisplayCacheCollection::iterator findCache(int index);
  
  const VRAMCache* vramCache_;
  const EditableSpriteMappings* spriteMappings_;
  const WarpDestinationCollection* warpDestinationCollection_;
  const ObjectGraphicsHeader* objectGraphicsHeader_;
  EditableLevelGraphicsData* levelGraphicsData_;
  const GGPalette* palette0_;
  const GGPalette* palette1_;
  EditableLevelObjectEntryGroups* levelObjectEntryGroups_;
  int levelObjectEntryGroupIndex_;
  LevelEditorToolManager* toolManager_;
  
  ObjectDisplayCacheCollection objectDisplayCaches_;
  
};


};


#endif
