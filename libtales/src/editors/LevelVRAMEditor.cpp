#include "editors/LevelVRAMEditor.h"
#include "editors/EditorMetadata.h"
#include "util/MiscMath.h"

using namespace Luncheon;

namespace Tales {


LevelVRAMEditor::LevelVRAMEditor(
                    EditableLevelGraphicsData& levelGraphicsData__,
                    EditableLevelPaletteHeaders& paletteHeaders__,
                    EditableStandardPalettes& palettes__,
                    EditableLeafGraphicsTable& leafGraphicsTable__,
                    EditableSmokePuffGraphicTable& smokePuffGraphicTable__,
                    EditableWaterSplashGraphicTable& waterSplashGraphicTable__,
                    EditorMetadata& metadata__)
  : BaseEditor(),
    previewScene_(*this,
                  levelGraphicsData__,
                  paletteHeaders__,
                  palettes__,
                  leafGraphicsTable__,
                  smokePuffGraphicTable__,
                  waterSplashGraphicTable__),
    levelGraphicsData_(levelGraphicsData__),
    paletteHeaders_(paletteHeaders__),
    palettes_(palettes__),
    leafGraphicsTable_(leafGraphicsTable__),
    smokePuffGraphicTable_(smokePuffGraphicTable__),
    waterSplashGraphicTable_(waterSplashGraphicTable__),
    metadata_(metadata__),
    inputMode_(standard),
    selectTileTarget_(targetSelectedGraphicIndex),
    dragAndDropTileOffset_(0),
    areaNum_(1),
    mapNum_(1) { };
  
void LevelVRAMEditor::refresh() {
  changeMap(areaNum_,
            mapNum_);
            
  previewScene_.refresh();
}
  
void LevelVRAMEditor::changeMap(int areaNum__,
                                int mapNum__) {
  areaNum_ = areaNum__;
  mapNum_ = mapNum__;
  
  previewScene_.changeMap(areaNum__,
                          mapNum__);
}
                 
int LevelVRAMEditor::areaNum() const {
  return areaNum_;
}

int LevelVRAMEditor::mapNum() const {
  return mapNum_;
}
                 
Graphic LevelVRAMEditor::testRender() {
  Graphic g;
  previewScene_.render(g,
                       Box(0, 0, 0, 0),
                       2.00);
  return g;
}
  
LevelVRAMEditor::InputMode LevelVRAMEditor::inputMode() const {
  return inputMode_;
}
  
void LevelVRAMEditor::resetInputMode() {
  setInputMode(standard);
}
  
void LevelVRAMEditor::startSelectingTile(SelectTileTarget target) {
  switch (target) {
  case targetSelectedGraphicIndex:
//    if (!objectIsSelected()) {
//      break;
//    }
    previewScene_.setTilePickerPreviewIndex(
        objectSubheader().tileWriteIndex());
    previewScene_.setTilePickerPreviewLength(
        levelGraphicsData_.compressedGraphic(
          objectSubheader().objectGraphicIndex()).numTiles());
    previewScene_.setTilePickerPreviewColor(
        VRAMEditorLayeredGraphicScene::fullGraphicSelectionBoxColor);
    break;
  case targetLeafIndex:
    previewScene_.setTilePickerPreviewIndex(leafIndex());
    previewScene_.setTilePickerPreviewLength(
        EditableLeafGraphicsTable::numGraphicTiles);
    previewScene_.setTilePickerPreviewColor(
        VRAMEditorLayeredGraphicScene::leafBoxColor);
    break;
  case targetSmokePuffIndex:
    previewScene_.setTilePickerPreviewIndex(smokePuffIndex());
    previewScene_.setTilePickerPreviewLength(
        EditableSmokePuffGraphicTable::numGraphicTiles);
    previewScene_.setTilePickerPreviewColor(
        VRAMEditorLayeredGraphicScene::smokePuffBoxColor);
    break;
  case targetWaterSplashIndex:
    previewScene_.setTilePickerPreviewIndex(waterSplashIndex());
    previewScene_.setTilePickerPreviewLength(
        EditableWaterSplashGraphicTable::numGraphicTiles);
    previewScene_.setTilePickerPreviewColor(
        VRAMEditorLayeredGraphicScene::waterSplashBoxColor);
    break;
  default:
    break;
  }
  
  selectTileTarget_ = target;
  
  setInputMode(selectTile);
}
  
void LevelVRAMEditor::setInputMode(InputMode inputMode__) {
  // Alter settings as needed to disable current mode
  switch (inputMode_) {
  case standard:
    previewScene_.setSelectionBoxEnabled(false);
    break;
  case dragAndDrop:
    
    break;
  case selectTile:
    previewScene_.setTilePickerPreviewEnabled(false);
    break;
  default:
  
    break;
  }
  
  // Alter settings as needed to enable new mode
  switch (inputMode__) {
  case standard:
    
    break;
  case dragAndDrop:
    
    break;
  case selectTile:
    // moved to mouseMove(): wait until user puts mouse over
    // preview to activate display
//    previewScene_.setTilePickerPreviewEnabled(true);
    break;
  default:
  
    break;
  }

  inputMode_ = inputMode__;
}

int LevelVRAMEditor::previewWidth() const {
  return previewScene_.nativeWidth() * scale();
}

int LevelVRAMEditor::previewHeight() const {
  return previewScene_.nativeHeight() * scale();
}
  
void LevelVRAMEditor::drawPreviewGraphic(Graphic& dst) {
  previewScene_.render(dst,
                       Box(0, 0, 0, 0),
                       scale());
}
  
Graphic LevelVRAMEditor::previewGraphic() {
  Graphic g;
  previewScene_.render(g,
                       Box(0, 0, 0, 0),
                       scale());
  return g;
}
  
EditableLevelGraphicsData& LevelVRAMEditor::levelGraphicsData() {
  return levelGraphicsData_;
}
  
LevelGraphicsHeader& LevelVRAMEditor::levelHeader() {
  int levelGraphicsHeaderIndex
    = levelGraphicsData_.levelHeaderIndexByMapnum(areaNum_,
                                                  mapNum_);
  
  return levelGraphicsData_.levelGraphicsHeader(levelGraphicsHeaderIndex);
}
  
GGPalette& LevelVRAMEditor::objectPalette() {
  LevelPaletteHeader& levelPaletteHeader
    = paletteHeaders_.headerByIndex(
        paletteHeaders_.indexOfMapNum(areaNum_,
                                      mapNum_));
                                      
  return palettes_.palette(levelPaletteHeader.palette1Index());
}

ObjectGraphicsHeader& LevelVRAMEditor::objectHeader() {
  int levelGraphicsHeaderIndex
    = levelGraphicsData_.levelHeaderIndexByMapnum(areaNum_,
                                                  mapNum_);
  
  LevelGraphicsHeader& levelGraphicsHeader
    = levelGraphicsData_.levelGraphicsHeader(levelGraphicsHeaderIndex);
    
  // Get object graphics header index
  int objectGraphicsHeaderIndex
    = levelGraphicsHeader.objectGraphicsHeaderIndex();
    
  // Get object graphics header
  ObjectGraphicsHeader& result
    = levelGraphicsData_.objectGraphicsHeader(objectGraphicsHeaderIndex);
    
  return result;
}
  
ObjectGraphicSubheader& LevelVRAMEditor::objectSubheader() {
  return objectHeader().subheader(selectedObjectIndex());
}
  
EditorMetadata& LevelVRAMEditor::metadata() {
  return metadata_;
}
  
bool LevelVRAMEditor::objectIsSelected() {
  return previewScene_.fullSelectionBoxEnabled();
}
  
int LevelVRAMEditor::selectedObjectIndex() {
  return previewScene_.fullSelectionBoxGraphicIndex();
}
  
void LevelVRAMEditor::selectObjectAtIndex(int index) {
  previewScene_.setFullSelectionBoxEnabled(true);
  previewScene_.setFullSelectionBoxGraphicIndex(index);
}
  
void LevelVRAMEditor::clearSelection() {
  previewScene_.setFullSelectionBoxEnabled(false);
}
  
void LevelVRAMEditor::moveSelectedUp() {
  // Return if nothing selected
  if (!objectIsSelected()) {
    return;
  }
  
  // Return if selected graphic is first in list
  if (selectedObjectIndex() == 0) {
    return;
  }
  
  int levelGraphicsHeaderIndex
    = levelGraphicsData_.levelHeaderIndexByMapnum(areaNum_,
                                                  mapNum_);
  
  LevelGraphicsHeader& levelGraphicsHeader
    = levelGraphicsData_.levelGraphicsHeader(levelGraphicsHeaderIndex);
    
  // Get object graphics header index
  int objectGraphicsHeaderIndex
    = levelGraphicsHeader.objectGraphicsHeaderIndex();
    
  // Get object graphics header
  ObjectGraphicsHeader& objectGraphicsHeader
    = levelGraphicsData_.objectGraphicsHeader(objectGraphicsHeaderIndex);
    
  // Copy selected subheader
  ObjectGraphicSubheader objectGraphicSubheader
    = objectGraphicsHeader.subheader(selectedObjectIndex());
  
  // Erase existing subheader
  objectGraphicsHeader.erase(selectedObjectIndex());
  
  // Insert at new position
  objectGraphicsHeader.insert(selectedObjectIndex() - 1,
                              objectGraphicSubheader);
  
  // Select same graphic at new position
  selectObjectAtIndex(selectedObjectIndex() - 1);
}

void LevelVRAMEditor::moveSelectedDown() {
  // Return if nothing selected
  if (!objectIsSelected()) {
    return;
  }
  
  int levelGraphicsHeaderIndex
    = levelGraphicsData_.levelHeaderIndexByMapnum(areaNum_,
                                                  mapNum_);
  
  LevelGraphicsHeader& levelGraphicsHeader
    = levelGraphicsData_.levelGraphicsHeader(levelGraphicsHeaderIndex);
    
  // Get object graphics header index
  int objectGraphicsHeaderIndex
    = levelGraphicsHeader.objectGraphicsHeaderIndex();
    
  // Get object graphics header
  ObjectGraphicsHeader& objectGraphicsHeader
    = levelGraphicsData_.objectGraphicsHeader(objectGraphicsHeaderIndex);
  
  // Return if selected graphic is last in list
  if (selectedObjectIndex() == objectGraphicsHeader.size() - 1) {
    return;
  }
    
  // Copy selected subheader
  ObjectGraphicSubheader objectGraphicSubheader
    = objectGraphicsHeader.subheader(selectedObjectIndex());
  
  // Erase existing subheader
  objectGraphicsHeader.erase(selectedObjectIndex());
  
  // Insert at new position
  objectGraphicsHeader.insert(selectedObjectIndex() + 1,
                              objectGraphicSubheader);
  
  // Select same graphic at new position
  selectObjectAtIndex(selectedObjectIndex() + 1);
}
  
void LevelVRAMEditor::eraseSelected() {
  // Return if nothing selected
  if (!objectIsSelected()) {
    return;
  }
  
  int oldIndex = selectedObjectIndex();
  objectHeader().erase(selectedObjectIndex());
  
  if (objectHeader().size()) {
    // Shift to next lowest index
    int newIndex = oldIndex - 1;
    
    // Don't go out of range
    if (newIndex < 0) {
      newIndex = 0;
    }
    
    selectObjectAtIndex(newIndex);
  }
  else {
    // Deselect
    clearSelection();
  }
}
  
int LevelVRAMEditor::mapGraphicIndex() const {
  int levelGraphicsHeaderIndex
    = levelGraphicsData_.levelHeaderIndexByMapnum(areaNum_,
                                                  mapNum_);
  
  LevelGraphicsHeader& levelGraphicsHeader
    = levelGraphicsData_.levelGraphicsHeader(levelGraphicsHeaderIndex);
    
  return levelGraphicsHeader.mapGraphicIndex();
}
  
void LevelVRAMEditor::changeMapGraphic(int index) {
  int levelGraphicsHeaderIndex
    = levelGraphicsData_.levelHeaderIndexByMapnum(areaNum_,
                                                  mapNum_);
  
  LevelGraphicsHeader& levelGraphicsHeader
    = levelGraphicsData_.levelGraphicsHeader(levelGraphicsHeaderIndex);
    
  levelGraphicsHeader.setMapGraphicIndex(index);
}
  
bool LevelVRAMEditor::hasLeafIndex() const {
  return EditorMetadata::areaNumHasVRAMIndices(areaNum_);
}
  
int LevelVRAMEditor::leafIndex() const {
  return leafGraphicsTable_.entry(areaNum_);
}

void LevelVRAMEditor::setLeafIndex(int index) {
  leafGraphicsTable_.entry(areaNum_) = index;
}

bool LevelVRAMEditor::hasSmokePuffIndex() const {
  return EditorMetadata::areaNumHasVRAMIndices(areaNum_);
}

int LevelVRAMEditor::smokePuffIndex() const {
  return smokePuffGraphicTable_.entry(areaNum_, mapNum_).leftTileIndex();
}

void LevelVRAMEditor::setSmokePuffIndex(int index) {
  smokePuffGraphicTable_.entry(areaNum_, mapNum_)
    .setLeftTileIndex(index);
}

bool LevelVRAMEditor::hasWaterSplashIndex() const {
  return EditorMetadata::areaNumHasVRAMIndices(areaNum_);
}

int LevelVRAMEditor::waterSplashIndex() const {
  return waterSplashGraphicTable_.entry(areaNum_, mapNum_).leftTileIndex();
}

void LevelVRAMEditor::setWaterSplashIndex(int index) {
  waterSplashGraphicTable_.entry(areaNum_, mapNum_)
    .setLeftTileIndex(index);
}

double LevelVRAMEditor::scale() const {
  return 2.0;
}
  
bool LevelVRAMEditor::showLeaf() const {
  return previewScene_.showLeaf();
}

void LevelVRAMEditor::setShowLeaf(bool showLeaf__) {
  previewScene_.setShowLeaf(showLeaf__);
}

bool LevelVRAMEditor::showSmokePuff() const {
  return previewScene_.showSmokePuff();
}

void LevelVRAMEditor::setShowSmokePuff(bool showSmokePuff__) {
  previewScene_.setShowSmokePuff(showSmokePuff__);
}

bool LevelVRAMEditor::showWaterSplash() const {
  return previewScene_.showWaterSplash();
}

void LevelVRAMEditor::setShowWaterSplash(bool showWaterSplash__) {
  previewScene_.setShowWaterSplash(showWaterSplash__);
}
  
LevelVRAMEditor::SelectTileTarget LevelVRAMEditor
    ::selectTileTarget() const {
  return selectTileTarget_;
}

void LevelVRAMEditor
    ::setSelectTileTarget(SelectTileTarget selectTileTarget__) {
  selectTileTarget_ = selectTileTarget__;
}

void LevelVRAMEditor
    ::mouseLeftClick(int x, int y) {
  switch (inputMode_) {
  case standard:
  
    standardMouseLeftClick(x, y);
    break;
  case dragAndDrop:
    // shouldn't happen
//    inputMode_ = standard;
    setInputMode(standard);
    break;
  case selectTile:
    selectTileMouseLeftClick(x, y);
    break;
  default:
    
    break;
  }
}

void LevelVRAMEditor::mouseLeftRelease(int x, int y) {
  switch (inputMode_) {
  case standard:
    
    break;
  case dragAndDrop:
//    inputMode_ = standard;
    setInputMode(standard);
    previewScene_.setSelectionBoxEnabled(true);
    previewScene_.setSelectionBoxX((x / GGTile::width));
    previewScene_.setSelectionBoxY((y / GGTile::height));
    break;
  default:
    
    break;
  }
}

void LevelVRAMEditor
    ::mouseMove(int x, int y, int leftButtonDown) {
  switch (inputMode_) {
  case standard:
    standardMouseMove(x, y, leftButtonDown);
    break;
  case dragAndDrop:
    dragAndDropMouseMove(x, y, leftButtonDown);
    break;
  case selectTile:
    selectTileMouseMove(x, y, leftButtonDown);
    break;
  default:
    
    break;
  }
}
  
void LevelVRAMEditor::mouseLeave() {
  switch (inputMode_) {
  case standard:
    previewScene_.setSelectionBoxEnabled(false);
    break;
  case dragAndDrop:
//    inputMode_ = standard;
    setInputMode(standard);
    break;
  default:
    
    break;
  }
}

void LevelVRAMEditor::standardMouseLeftClick(int x, int y) {
  // Find the clicked graphic
  
  // Clip coordinates to valid area
  if (x >= previewScene_.nativeWidth()) {
    x = previewScene_.nativeWidth() - GGTile::width;
  }

  if (y >= previewScene_.nativeHeight()) {
    y = previewScene_.nativeHeight() - GGTile::height;
  }
  
  if (x < 0) {
    x = 0;
  }
  
  if (y < 0) {
    y = 0;
  }

  // Get clicked tile x/y
  int tileX = x / GGTile::width;
  int tileY = y / GGTile::height;
  
  // Convert to tile index
  int tileIndex = previewScene_.tilePosToTileIndex(tileX, tileY);
  
//  std::cout << "clicked index: " << tileIndex << std::endl;
  
  // Remember initially selected graphic
  int initialSelection = previewScene_.fullSelectionBoxGraphicIndex();
  
  // Search for a graphic that overlaps the area
  previewScene_.findAndHandleTopGraphicIndex(tileIndex);
  
//  std::cout << "old: " << initialSelection << std::endl;
  
  // Check if search was successful
  if (previewScene_.fullSelectionBoxEnabled()) {
    // Check if new selection is same as old
//    if (previewScene_.fullSelectionBoxGraphicIndex() == initialSelection) {
//      std::cout << "new: " << previewScene_.fullSelectionBoxGraphicIndex() << std::endl;
      // Start drag and drop mode
      previewScene_.setSelectionBoxEnabled(false);
//      inputMode_ = dragAndDrop;
      setInputMode(dragAndDrop);
      dragAndDropTileOffset_ = objectSubheader().tileWriteIndex()
                                  - tileIndex;
//      std::cout << dragAndDropTileOffset_ << std::endl;
//    }
  }
  else {
    
  }
}

void LevelVRAMEditor::selectTileMouseLeftClick(int x, int y) {
  int index = previewScene_.tilePickerPreviewIndex();

  if ((index >= 0) && (index <= 255)) {
    switch (selectTileTarget_) {
    case targetSelectedGraphicIndex:
      objectSubheader().setTileWriteIndex(index);
      break;
    case targetLeafIndex:
      setLeafIndex(index);
      break;
    case targetSmokePuffIndex:
      setSmokePuffIndex(index);
      break;
    case targetWaterSplashIndex:
      setWaterSplashIndex(index);
      break;
    default:
      
      break;
    }
  }
  
  setInputMode(standard);
}

void LevelVRAMEditor::standardMouseMove(int x, int y, int leftButtonDown) {
  switch (inputMode_) {
  case standard:
    previewScene_.setSelectionBoxEnabled(true);

    // Clip coordinates to valid area
    if (x >= previewScene_.nativeWidth()) {
      x = previewScene_.nativeWidth() - GGTile::width;
    }

    if (y >= previewScene_.nativeHeight()) {
      y = previewScene_.nativeHeight() - GGTile::height;
    }

    // Set selection box position
    previewScene_.setSelectionBoxX((x / GGTile::width));
    previewScene_.setSelectionBoxY((y / GGTile::height));
    break;
  default:
    break;
  }
}

void LevelVRAMEditor::dragAndDropMouseMove(int x, int y, int leftButtonDown) {
  // Clip coordinates to valid area
  if (x >= previewScene_.nativeWidth()) {
    x = previewScene_.nativeWidth() - GGTile::width;
  }

  if (y >= previewScene_.nativeHeight()) {
    y = previewScene_.nativeHeight() - GGTile::height;
  }

  // Get clicked tile x/y
  int tileX = x / GGTile::width;
  int tileY = y / GGTile::height;
  
  // Convert to tile index
  int tileIndex = previewScene_.tilePosToTileIndex(tileX, tileY);
  
  // Add offset
  tileIndex += dragAndDropTileOffset_;
  
  // If out of range, clip
  MiscMath::clamp(tileIndex, 0, 255);
  
  // Move graphic to target location
  objectSubheader().setTileWriteIndex(tileIndex);
}
  
void LevelVRAMEditor::selectTileMouseMove(int x, int y, int leftButtonDown) {
  previewScene_.setTilePickerPreviewEnabled(true);
    
  // Clip coordinates to valid area
  if (x >= previewScene_.nativeWidth()) {
    x = previewScene_.nativeWidth() - GGTile::width;
  }

  if (y >= previewScene_.nativeHeight()) {
    y = previewScene_.nativeHeight() - GGTile::height;
  }

  // Get clicked tile x/y
  int tileX = x / GGTile::width;
  int tileY = y / GGTile::height;
  
  // Convert to tile index
  int tileIndex = previewScene_.tilePosToTileIndex(tileX, tileY);
  
  // Move selection graphic
  previewScene_.setTilePickerPreviewIndex(tileIndex);
}


};
