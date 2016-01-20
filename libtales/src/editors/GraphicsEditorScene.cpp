#include "editors/GraphicsEditorScene.h"

namespace Tales {


GraphicsEditorScene::GraphicsEditorScene(
                 EditableLevelGraphicsData& levelGraphicsData__,
                 EditableStandardPalettes& palettes__,
                 EditableSpriteMappings& spriteMappings__,
                 GraphicsEditorToolManager& toolManager__)
  : LayeredGraphicScene(),
    levelGraphicsData_(&levelGraphicsData__),
    palettes_(&palettes__),
    spriteMappings_(&spriteMappings__),
    toolManager_(&toolManager__),
    tileEditorLayer_(*toolManager_),
    mappingEditorLayer_(*toolManager_) { };
                 
void GraphicsEditorScene::render(Graphic& dst,
    Box srcbox,
    double scale) {
  
}
                 
void GraphicsEditorScene::renderTileLayer(Graphic& dst,
      Box srcbox,
      double scale) {
  tileEditorLayer_.render(dst, srcbox, scale);
}
                 
void GraphicsEditorScene::renderMappingLayer(Graphic& dst,
      Box srcbox,
      double scale) {
  mappingEditorLayer_.render(dst, srcbox, scale);
}
  
void GraphicsEditorScene::tileEditorEnterMouse() {
  tileEditorLayer_.enterMouse();
}

void GraphicsEditorScene::tileEditorExitMouse() {
  tileEditorLayer_.exitMouse();
}

void GraphicsEditorScene::tileEditorMoveMouse(InputEventData eventData) {
  tileEditorLayer_.moveMouse(eventData);
}

void GraphicsEditorScene::tileEditorPressMouse(InputEventData eventData) {
  tileEditorLayer_.pressMouse(eventData);
}

void GraphicsEditorScene::tileEditorReleaseMouse(InputEventData eventData) {
  tileEditorLayer_.releaseMouse(eventData);
}

void GraphicsEditorScene
    ::tileEditorDoubleClickMouse(InputEventData eventData) {
  tileEditorLayer_.doubleClickMouse(eventData);
}
  
void GraphicsEditorScene::mappingEditorEnterMouse() {
  mappingEditorLayer_.enterMouse();
}

void GraphicsEditorScene::mappingEditorExitMouse() {
  mappingEditorLayer_.exitMouse();
}

void GraphicsEditorScene::mappingEditorMoveMouse(InputEventData eventData) {
  mappingEditorLayer_.moveMouse(eventData);
}

void GraphicsEditorScene::mappingEditorPressMouse(InputEventData eventData) {
  mappingEditorLayer_.pressMouse(eventData);
}

void GraphicsEditorScene::mappingEditorReleaseMouse(InputEventData eventData) {
  mappingEditorLayer_.releaseMouse(eventData);
}

void GraphicsEditorScene
    ::mappingEditorDoubleClickMouse(InputEventData eventData) {
  mappingEditorLayer_.doubleClickMouse(eventData);
}
      
int GraphicsEditorScene::nativeTileLayerWidth() {
  return tileEditorLayer_.nativeWidth();
}

int GraphicsEditorScene::nativeTileLayerHeight() {
  return tileEditorLayer_.nativeHeight();
}

int GraphicsEditorScene::nativeMappingLayerWidth() {
  return mappingEditorLayer_.nativeWidth();
}

int GraphicsEditorScene::nativeMappingLayerHeight() {
  return mappingEditorLayer_.nativeHeight();
}


}; 
