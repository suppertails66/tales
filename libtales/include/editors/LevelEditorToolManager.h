#ifndef LEVELEDITORTOOLMANAGER_H
#define LEVELEDITORTOOLMANAGER_H


#include "editors/LevelEditorTool.h"
#include "gamedata/MapLayout.h"
#include "structs/Tbyte.h"
#include "editors/ObjectDisplayCacheCollection.h"
#include "gamedata/EditableLevelObjectEntryGroups.h"
#include "gamedata/EditableSpawnPoints.h"
#include <vector>

namespace Tales {

typedef std::vector<ObjectDisplayCacheCollection::iterator>
  ObjectDisplayCacheCollectionIteratorCollection;
typedef std::vector<LevelObjectEntryCollection::iterator>
  LevelObjectEntryCollectionIteratorCollection;


class LevelEditorToolManager {
public:

  LevelEditorToolManager();
  
  ~LevelEditorToolManager();
  
  LevelEditorTools::LevelEditorTool currentTool() const;
  void setCurrentTool(LevelEditorTools::LevelEditorTool currentTool__);
  void setCurrentToolNoReset(LevelEditorTools::LevelEditorTool currentTool__);
  
  int pickedMetatileIndex() const;
  void setPickedMetatileIndex(int pickedMetatileIndex__);
  
  LevelEditorTools::MetatileAreaCloneState metatileAreaCloneState() const;
  void setMetatileAreaCloneState(
    LevelEditorTools::MetatileAreaCloneState metatileAreaCloneState__);
  int metatileAreaCloneBaseX() const;
  void setMetatileAreaCloneBaseX(int metatileAreaCloneBaseX__);
  int metatileAreaCloneBaseY() const;
  void setMetatileAreaCloneBaseY(int metatileAreaCloneBaseY__);
  int metatileAreaCloneWidth() const;
  void setMetatileAreaCloneWidth(int metatileAreaCloneWidth__);
  int metatileAreaCloneHeight() const;
  void setMetatileAreaCloneHeight(int metatileAreaCloneHeight__);
  void finalizeMetatileAreaClone(const MapLayout& mapLayout,
                                 int mapWidth);
  int metatileAreaCloneMetatile(int x, int y);
  
  LevelEditorTools::ObjectEditorState objectEditorState() const;
  ObjectDisplayCacheCollection::iterator objectEditorSingleCacheIt() const;
  LevelObjectEntryCollection::iterator objectEditorSingleGroupIt() const;
  ObjectDisplayCacheCollectionIteratorCollection&
     objectEditorMultipleCacheIts();
  LevelObjectEntryCollectionIteratorCollection&
     objectEditorMultipleGroupIts();
  int objectEditorLastRealX() const;
  int objectEditorLastRealY() const;
  void setObjectEditorState(LevelEditorTools
                              ::ObjectEditorState objectEditorState__);
  void setObjectEditorSingleCacheIt(ObjectDisplayCacheCollection::iterator
                                      objectEditorSingleCacheIt__);
  void setObjectEditorSingleGroupIt(LevelObjectEntryCollection::iterator
                                      objectEditorSingleGroupIt__);
  void setObjectEditorLastRealX(int objectEditorLastRealX__);
  void setObjectEditorLastRealY(int objectEditorLastRealY__);
  int objectEditorMultipleSelectX();
  void setObjectEditorMultipleSelectX(
      int objectEditorMultipleSelectX__);
  int objectEditorMultipleSelectY();
  void setObjectEditorMultipleSelectY(
      int objectEditorMultipleSelectY__);
  int objectEditorMultipleSelectW();
  void setObjectEditorMultipleSelectW(
      int objectEditorMultipleSelectW__);
  int objectEditorMultipleSelectH();
  void setObjectEditorMultipleSelectH(
      int objectEditorMultipleSelectH__);
  int objectEditorMultipleLastRealX() const;
  int objectEditorMultipleLastRealY() const;
  void setObjectEditorMultipleLastRealX(int objectEditorMultipleLastRealX__);
  void setObjectEditorMultipleLastRealY(int objectEditorMultipleLastRealY__);
  
  LevelEditorTools::SpawnEditorState spawnEditorState();
  ObjectDisplayCacheCollection::iterator spawnEditorSingleCacheIt();
  SpawnPointCollection::iterator spawnEditorSingleGroupIt();
  int spawnEditorLastRealX();
  int spawnEditorLastRealY();
  void setSpawnEditorState(LevelEditorTools
                              ::SpawnEditorState spawnEditorState__);
  void setSpawnEditorSingleCacheIt(ObjectDisplayCacheCollection::iterator
                                      spawnEditorSingleCacheIt__);
  void setSpawnEditorSingleGroupIt(SpawnPointCollection::iterator
                                      spawnEditorSingleGroupIt__);
  void setSpawnEditorLastRealX(int spawnEditorLastRealX__);
  void setSpawnEditorLastRealY(int spawnEditorLastRealY__);
  
protected:
  
  LevelEditorTools::LevelEditorTool currentTool_;
  
  // paint
  int pickedMetatileIndex_;
  
  // area clone
  LevelEditorTools::MetatileAreaCloneState metatileAreaCloneState_;
  int metatileAreaCloneBaseX_;
  int metatileAreaCloneBaseY_;
  int metatileAreaCloneWidth_;
  int metatileAreaCloneHeight_;
  // Pseudo-2D array of metatile IDs. Use metatileAreaCloneWidth_ and
  // metatileAreaCloneHeight_ as index limits.
  Tbyte* metatileAreaCloneMetatileArray_;
  
  // object editor
  LevelEditorTools::ObjectEditorState objectEditorState_;
  ObjectDisplayCacheCollection::iterator objectEditorSingleCacheIt_;
  LevelObjectEntryCollection::iterator objectEditorSingleGroupIt_;
  ObjectDisplayCacheCollectionIteratorCollection
     objectEditorMultipleCacheIts_;
  LevelObjectEntryCollectionIteratorCollection
     objectEditorMultipleGroupIts_;
  int objectEditorMultipleSelectX_;
  int objectEditorMultipleSelectY_;
  int objectEditorMultipleSelectW_;
  int objectEditorMultipleSelectH_;
  int objectEditorLastRealX_;
  int objectEditorLastRealY_;
  int objectEditorMultipleLastRealX_;
  int objectEditorMultipleLastRealY_;
  
  // spawn editor
  LevelEditorTools::SpawnEditorState spawnEditorState_;
  ObjectDisplayCacheCollection::iterator spawnEditorSingleCacheIt_;
  SpawnPointCollection::iterator spawnEditorSingleGroupIt_;
  int spawnEditorLastRealX_;
  int spawnEditorLastRealY_;
  
  
};


};


#endif
