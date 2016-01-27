#ifndef GRAPHICSEDITOR_H
#define GRAPHICSEDITOR_H


#include "editors/BaseEditor.h"
#include "editors/GraphicsEditorToolManager.h"
#include "gamedata/EditableLevelGraphicsData.h"
#include "gamedata/EditableStandardPalettes.h"
#include "gamedata/EditableSpriteMappings.h"
#include "editors/GraphicsEditorScene.h"
#include "editors/ColorPickerGraphicSceneLayer.h"
#include "editors/EditorMetadata.h"
#include "structs/InputEventData.h"

namespace Tales {


class GraphicsEditor : public BaseEditor {
public:
  enum GraphicCompressionType {
    uncompressed,
    compressed
  };

  GraphicsEditor(EditableLevelGraphicsData& levelGraphicsData__,
                 EditableStandardPalettes& palettes__,
                 EditableSpriteMappings& spriteMappings__,
                 EditorMetadata& metadata__);
  
  virtual void refresh();
  
  void drawTileGraphic(Graphic& dst);
  void drawMappingGraphic(Graphic& dst);
  void drawColorPickerGraphic(Graphic& dst);
  
  void tileEditorEnterMouse();
  void tileEditorExitMouse();
  void tileEditorMoveMouse(InputEventData eventData);
  void tileEditorPressMouse(InputEventData eventData);
  void tileEditorReleaseMouse(InputEventData eventData);
  void tileEditorDoubleClickMouse(InputEventData eventData);
  
  void mappingEditorEnterMouse();
  void mappingEditorExitMouse();
  void mappingEditorMoveMouse(InputEventData eventData);
  void mappingEditorPressMouse(InputEventData eventData);
  void mappingEditorReleaseMouse(InputEventData eventData);
  void mappingEditorDoubleClickMouse(InputEventData eventData);
  
  void colorPickerEnterMouse();
  void colorPickerExitMouse();
  void colorPickerMoveMouse(InputEventData eventData);
  void colorPickerPressMouse(InputEventData eventData);
  void colorPickerReleaseMouse(InputEventData eventData);
  void colorPickerDoubleClickMouse(InputEventData eventData);
  
  void changeTool(GraphicsEditorTools::GraphicsEditorTool tool);
  
  void setScale(double scale__);
  
  void changeGraphic(GraphicCompressionType compressionType,
                     int index);
                     
  void setGridEnabled(bool gridEnabled__);
  
  void setTransparencyEnabled(bool transparencyEnabled__);
  
  int numCompressedGraphics();
  int numUncompressedGraphics();
  int numPalettes();
  
  int currentPaletteIndex();
  void setCurrentPaletteIndex(int index);
  
  int currentColorIndex();
  void setCurrentColorIndex(int index);
  
  int colorPickerWidth();
  int colorPickerHeight();
  int colorPickerCurrentIndex();
  
  int tileEditorWidth();
  int tileEditorHeight();
  
  int mappingEditorWidth();
  int mappingEditorHeight();
  
  bool mappingExists();
  SpriteMapping& currentMapping();
  
  GGTileSet& currentGraphic();
  
  void changeMapping(int mappingSubIndex);
      
  bool collisionViewEnabled();
  void setCollisionViewEnabled(bool collisionViewEnabled__);
  
  void setCurrentPaletteDefault(int paletteNum);
  
  int compressedGraphicPaletteDefault(int index);
  void setCompressedGraphicPaletteDefault(int index, int paletteNum);
  
  int uncompressedGraphicPaletteDefault(int index);
  void setUncompressedGraphicPaletteDefault(int index, int paletteNum);
  
  void exportAllTiles(const std::string& folderpath,
                      bool transparency = true);
  
  void exportAllMappings(const std::string& folderpath);
protected:
  const static int exportTilesPerRow_ = 16;

  static std::string graphicToFilename(
                        GraphicCompressionType comp,
                        int graphicIndex);
                        
  static std::string graphicMappingToFilename(
                        GraphicCompressionType comp,
                        int graphicIndex,
                        int mappingIndex);
  
  void exportTiles(const std::string& folderpath,
                        GraphicCompressionType comp,
                        int graphicIndex,
                        bool transparency);
  
  void exportMappingSet(const std::string& folderpath,
                        GraphicCompressionType comp,
                        int graphicIndex);
                        
  GraphicsEditorToolManager toolManager_;

  EditableLevelGraphicsData& levelGraphicsData_;
  EditableStandardPalettes& palettes_;
  EditableSpriteMappings& spriteMappings_;
  EditorMetadata& metadata_;
  
  GraphicsEditorScene editorScene_;
  
  ColorPickerGraphicSceneLayer colorPicker_;
  
  int currentPaletteIndex_;
  
  GraphicCompressionType currentGraphicCompressionType_;
  int currentGraphicIndex_;
};


};


#endif
