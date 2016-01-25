#ifndef METATILESTRUCTUREEDITOR_H
#define METATILESTRUCTUREEDITOR_H


#include "editors/BaseEditor.h"
#include "structs/InputEventData.h"
#include "structs/Graphic.h"
#include "editors/MetatileStructureDefaultMap.h"
#include "editors/VisualMetatilePickerScene.h"
#include "editors/TilePickerScene.h"
#include "editors/MetatileSubtilePickerScene.h"
#include "gamedata/MetatileStructures.h"
#include "gamedata/EditableLevelGraphicsData.h"
#include "gamedata/EditableStandardPalettes.h"

namespace Tales {


class MetatileStructureEditor : public BaseEditor {
public:
  MetatileStructureEditor(MetatileStructureDefaultMap& defaults__,
                          MetatileStructures& metatileStructures__,
                          EditableLevelGraphicsData& levelGraphicsData__,
                          EditableStandardPalettes& standardPalettes__);
  
  virtual ~MetatileStructureEditor();
  
  virtual void refresh();
  
  void metatilePickerEnterMouse();
  void metatilePickerExitMouse();
  void metatilePickerMoveMouse(InputEventData eventData);
  void metatilePickerPressMouse(InputEventData eventData);
  void metatilePickerReleaseMouse(InputEventData eventData);
  void metatilePickerDoubleClickMouse(InputEventData eventData);
  
  void tilePickerEnterMouse();
  void tilePickerExitMouse();
  void tilePickerMoveMouse(InputEventData eventData);
  void tilePickerPressMouse(InputEventData eventData);
  void tilePickerReleaseMouse(InputEventData eventData);
  void tilePickerDoubleClickMouse(InputEventData eventData);
  
  void subtilePickerEnterMouse();
  void subtilePickerExitMouse();
  void subtilePickerMoveMouse(InputEventData eventData);
  void subtilePickerPressMouse(InputEventData eventData);
  void subtilePickerReleaseMouse(InputEventData eventData);
  void subtilePickerDoubleClickMouse(InputEventData eventData);
  
  void drawMetatilePickerGraphic(Graphic& dst);
  void drawTilePickerGraphic(Graphic& dst);
  void drawSubtilePickerGraphic(Graphic& dst);
  
  void setGridEnabled(bool gridEnabled__);
  
  int previewWidth();
  int previewHeight();
  
  int numMetatileStructureSets();
  int numGraphics();
  int numPalettes();
  
  MetatileStructureDefault defaultPreview(int index);
  
  void loadNewCurrentSet(int currentSet__);
  
  void loadPickedMetatile();
  
  void loadPickedSubtile();
  
  void updatePickedTile();
  
  GGTileSet& currentGraphic();
  GGPalette& currentPalette0();
  GGPalette& currentPalette1();
  
  void changeCurrentGraphic(int index);
  void changeCurrentPalette0(int index);
  void changeCurrentPalette1(int index);
  
  void setCurrentDefaults(MetatileStructureDefault defaults);
  
  MetatileStructureSet& currentMetatileStructureSet();
  MetatileStructure& currentMetatileStructure();
  
  int currentNumMetatileStructures();
  
  int currentMetatileIndex();
  int currentMetatileStructureIndex();
  
  void setStructureOfCurrentMetatile(int index);
  
  void appendMetatileStructureIndex();
  void removeCurrentMetatileStructureIndex();
  
  void pickMetatile(int index);
protected:
  const static int tileOffset_ = -256;
  const static int legalTileLowerBound_ = 256;
  const static int legalTileUpperBound_ = 512;

  void loadMetatile(int index);

  void loadSubtile(int index);
  
  MetatileStructureDefaultMap& defaults_;
  MetatileStructures& metatileStructures_;
  EditableLevelGraphicsData& levelGraphicsData_;
  EditableStandardPalettes& standardPalettes_;
  
  VisualMetatilePickerScene metatilePicker_;
  TilePickerScene tilePicker_;
  MetatileSubtilePickerScene subtilePicker_;
  
  int currentSet_;
  
};


};


#endif
