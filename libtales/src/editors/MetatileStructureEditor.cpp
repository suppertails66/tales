#include "editors/MetatileStructureEditor.h"

namespace Tales {


MetatileStructureEditor::MetatileStructureEditor(
                        MetatileStructureDefaultMap& defaults__,
                        MetatileStructures& metatileStructures__,
                        EditableLevelGraphicsData& levelGraphicsData__,
                        EditableStandardPalettes& standardPalettes__)
  : defaults_(defaults__),
    metatileStructures_(metatileStructures__),
    levelGraphicsData_(levelGraphicsData__),
    standardPalettes_(standardPalettes__),
    currentSet_(0) {
  loadNewCurrentSet(0);
}
  
MetatileStructureEditor::~MetatileStructureEditor() { };
  
void MetatileStructureEditor::refresh() {
  
}
  
int MetatileStructureEditor::numMetatileStructureSets() {
  return metatileStructures_.size();
}

int MetatileStructureEditor::numGraphics() {
  return levelGraphicsData_.compressedGraphicsSize();
}

int MetatileStructureEditor::numPalettes() {
  return standardPalettes_.size();
}
  
MetatileStructureDefault MetatileStructureEditor::defaultPreview(int index) {
  return defaults_[index];
}
  
void MetatileStructureEditor::loadNewCurrentSet(int currentSet__) {
  currentSet_ = currentSet__;
  
  metatilePicker_.setMetatiles(
    currentMetatileStructureSet());
  subtilePicker_.setMetatile(
    currentMetatileStructure());
    
  changeCurrentGraphic(defaultPreview(currentSet_).graphicIndex_);
  changeCurrentPalette0(defaultPreview(currentSet_).paletteIndex_);
  changeCurrentPalette1(defaultPreview(currentSet_).palette1Index_);
}
  
void MetatileStructureEditor::changeCurrentGraphic(int index) {
  metatilePicker_.setTiles(
    levelGraphicsData_.compressedGraphic(index));
  tilePicker_.setTiles(
    levelGraphicsData_.compressedGraphic(index));
  subtilePicker_.setTiles(
    levelGraphicsData_.compressedGraphic(index));
}

void MetatileStructureEditor::changeCurrentPalette0(int index) {
  metatilePicker_.setPalette0(
    standardPalettes_.palette(index));
  tilePicker_.setPalette0(
    standardPalettes_.palette(index));
  subtilePicker_.setPalette0(
    standardPalettes_.palette(index));
}

void MetatileStructureEditor::changeCurrentPalette1(int index) {
  metatilePicker_.setPalette1(
    standardPalettes_.palette(index));
  tilePicker_.setPalette1(
    standardPalettes_.palette(index));
  subtilePicker_.setPalette1(
    standardPalettes_.palette(index));
}
  
void MetatileStructureEditor::drawMetatilePickerGraphic(Graphic& dst) {
  metatilePicker_.render(dst,
                         Box(0, 0,
                             dst.w(), dst.h()),
                         1.00);
}

void MetatileStructureEditor::drawTilePickerGraphic(Graphic& dst) {
  tilePicker_.render(dst,
                     Box(0, 0,
                         128, 128),
                     1.00);
}

void MetatileStructureEditor::drawSubtilePickerGraphic(Graphic& dst) {
  subtilePicker_.render(dst,
                        Box(0, 0,
                            16, 16),
                        1.00);
}
  
void MetatileStructureEditor::loadPickedMetatile() {
  loadMetatile(metatilePicker_.pickedIndex());
}
  
void MetatileStructureEditor::loadPickedSubtile() {
  loadSubtile(subtilePicker_.pickedIndex());
}

void MetatileStructureEditor::loadMetatile(int index) {
  subtilePicker_.setMetatile(
    currentMetatileStructure());
  loadPickedSubtile();
}

void MetatileStructureEditor::loadSubtile(int index) {
  int tileIndex = 0;
  switch (subtilePicker_.pickedIndex()) {
  case 0: // ul
    tileIndex = currentMetatileStructure().upperLeft()
                  .tileNum();
    break;
  case 1: // ur
    tileIndex = currentMetatileStructure().upperRight()
                  .tileNum();
    break;
  case 2: // ll
    tileIndex = currentMetatileStructure().lowerLeft()
                  .tileNum();
    break;
  case 3: // lr
    tileIndex = currentMetatileStructure().lowerRight()
                  .tileNum();
    break;
  default:
    break;
  }
  
  if (tileIndex >= legalTileLowerBound_) {
    tileIndex += tileOffset_;
    tilePicker_.pickIndex(tileIndex);
  }
  else {
    // unselect
    tilePicker_.clearPickedBox();
  }
}
  
void MetatileStructureEditor::updatePickedTile() {
  int tileIndex = tilePicker_.pickedIndex()
                    - tileOffset_;
  switch (subtilePicker_.pickedIndex()) {
  case 0: // ul
    currentMetatileStructure().upperLeft()
                  .setTileNum(tileIndex);
    break;
  case 1: // ur
    currentMetatileStructure().upperRight()
                  .setTileNum(tileIndex);
    break;
  case 2: // ll
    currentMetatileStructure().lowerLeft()
                  .setTileNum(tileIndex);
    break;
  case 3: // lr
    currentMetatileStructure().lowerRight()
                  .setTileNum(tileIndex);
    break;
  default:
    break;
  }
}

GGTileSet& MetatileStructureEditor::currentGraphic() {
  return metatilePicker_.tiles();
}
  
GGPalette& MetatileStructureEditor::currentPalette0() {
  return metatilePicker_.palette0();
}

GGPalette& MetatileStructureEditor::currentPalette1() {
  return metatilePicker_.palette1();
}
  
MetatileStructureSet& MetatileStructureEditor::currentMetatileStructureSet() {
  return metatileStructures_.metatileStructureSet(currentSet_);
}

MetatileStructure& MetatileStructureEditor::currentMetatileStructure() {
  return currentMetatileStructureSet().metatileMapping(
           metatilePicker_.pickedIndex());
}
  
int MetatileStructureEditor::currentNumMetatileStructures() {
  return currentMetatileStructureSet().numStructureDefinitions();
}
  
int MetatileStructureEditor::currentMetatileIndex() {
  return metatilePicker_.pickedIndex();
}

int MetatileStructureEditor::currentMetatileStructureIndex() {
  return currentMetatileStructureSet().structureIndex(
            currentMetatileIndex());
}

void MetatileStructureEditor::appendMetatileStructureIndex() {
  // Do not allow more metatile than physically accessible to be mapped
  if (currentNumMetatileStructures() >=
        MetatileStructures::numMetatilesPerTable) {
    return;
  }
  
  int index = currentMetatileStructureSet().appendStructureDefinition();
  
  // Map current metatile to new index
  setStructureOfCurrentMetatile(index);
}
  
void MetatileStructureEditor::removeCurrentMetatileStructureIndex() {
  // Do not allow the last structure definition to be removed
  if (currentNumMetatileStructures() <= 1) {
    return;
  }
  
  int currentIndex = currentMetatileStructureIndex();
  
  currentMetatileStructureSet().removeStructureDefinition(
    currentIndex);
  
  // Correct mappings
  for (MetatileIndexToStructureMap::iterator it
          = currentMetatileStructureSet().metatileStructureIndexBegin();
       it != currentMetatileStructureSet().metatileStructureIndexEnd();
       ++it) {
    // Anything mapped to current index is reset to 0
    if (it->second == currentIndex) {
      it->second = 0;
    }
    // Anything greater than current index is decremented
    else if (it->second > currentIndex) {
      --(it->second);
    }
  }
}
  
void MetatileStructureEditor::pickMetatile(int index) {
  metatilePicker_.pickIndex(index);
  loadPickedMetatile();
}
  
void MetatileStructureEditor::setStructureOfCurrentMetatile(int index) {
  currentMetatileStructureSet().setStructureIndex(
            metatilePicker_.pickedIndex(),
            index);
}
  
void MetatileStructureEditor::setGridEnabled(bool gridEnabled__) {
  metatilePicker_.setGridLayerEnabled(gridEnabled__);
  tilePicker_.setGridLayerEnabled(gridEnabled__);
  subtilePicker_.setGridLayerEnabled(gridEnabled__);
}

void MetatileStructureEditor
    ::setCurrentDefaults(MetatileStructureDefault defaults) {
  defaults_[currentSet_] = defaults;
}
  
void MetatileStructureEditor
    ::metatilePickerEnterMouse() {
  metatilePicker_.enterMouse();
}

void MetatileStructureEditor
    ::metatilePickerExitMouse() {
  metatilePicker_.exitMouse();
}

void MetatileStructureEditor
    ::metatilePickerMoveMouse(InputEventData eventData) {
  metatilePicker_.moveMouse(eventData);
}

void MetatileStructureEditor
    ::metatilePickerPressMouse(InputEventData eventData) {
  metatilePicker_.pressMouse(eventData);
}

void MetatileStructureEditor
    ::metatilePickerReleaseMouse(InputEventData eventData) {
  metatilePicker_.releaseMouse(eventData);
}

void MetatileStructureEditor
    ::metatilePickerDoubleClickMouse(InputEventData eventData) {
  metatilePicker_.doubleClickMouse(eventData);
}
  
void MetatileStructureEditor
    ::tilePickerEnterMouse() {
  tilePicker_.enterMouse();
}

void MetatileStructureEditor
    ::tilePickerExitMouse() {
  tilePicker_.exitMouse();
}

void MetatileStructureEditor
    ::tilePickerMoveMouse(InputEventData eventData) {
  tilePicker_.moveMouse(eventData);
}

void MetatileStructureEditor
    ::tilePickerPressMouse(InputEventData eventData) {
  tilePicker_.pressMouse(eventData);
}

void MetatileStructureEditor
    ::tilePickerReleaseMouse(InputEventData eventData) {
  tilePicker_.releaseMouse(eventData);
}

void MetatileStructureEditor
    ::tilePickerDoubleClickMouse(InputEventData eventData) {
  tilePicker_.doubleClickMouse(eventData);
}
  
void MetatileStructureEditor
    ::subtilePickerEnterMouse() {
  subtilePicker_.enterMouse();
}

void MetatileStructureEditor
    ::subtilePickerExitMouse() {
  subtilePicker_.exitMouse();
}

void MetatileStructureEditor
    ::subtilePickerMoveMouse(InputEventData eventData) {
  subtilePicker_.moveMouse(eventData);
}

void MetatileStructureEditor
    ::subtilePickerPressMouse(InputEventData eventData) {
  subtilePicker_.pressMouse(eventData);
}

void MetatileStructureEditor
    ::subtilePickerReleaseMouse(InputEventData eventData) {
  subtilePicker_.releaseMouse(eventData);
}

void MetatileStructureEditor
    ::subtilePickerDoubleClickMouse(InputEventData eventData) {
  subtilePicker_.doubleClickMouse(eventData);
}


};
