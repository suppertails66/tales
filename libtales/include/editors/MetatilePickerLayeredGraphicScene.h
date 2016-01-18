#ifndef METATILEPICKERLAYEREDGRAPHICSCENE_H
#define METATILEPICKERLAYEREDGRAPHICSCENE_H


#include "structs/LayeredGraphicScene.h"
#include "structs/InputEventData.h"
#include "editors/VRAMCache.h"
#include "gamedata/MetatileStructureSet.h"
#include "gamedata/EditableMetatileBehaviors.h"
#include "gamedata/EditableMetatileWidthMaps.h"
#include "gamedata/EditableMetatileHeightMaps.h"
#include "editors/MetatileGraphicCollection.h"
#include "editors/GridGraphicSceneLayer.h"
#include "editors/LevelEditorToolManager.h"

namespace Tales {


class MetatilePickerLayeredGraphicScene
  : public LayeredGraphicScene {
public:
  MetatilePickerLayeredGraphicScene(const MetatileStructureSet&
                                      metatileStructureSet__,
                                    const EditableMetatileBehaviors&
                                      metatileBehaviors__,
                                    EditableMetatileWidthMaps&
                                      widthMaps__,
                                    EditableMetatileHeightMaps&
                                      heightMaps__,
                                    LevelEditorToolManager&
                                      toolManager__,
                                    const VRAMCache& vramCache__);
  
  /**
   * Renders scene to a Graphic.
   * @param dst Graphic to render to. Existing contents are discarded.
   * @param srcbox Box indicating the area of the contained Scene to be
   * rendered to the Graphic.
   */
  virtual void render(Graphic& dst,
                      Box srcbox,
                      double scale);
  
  void enterMouse();
  void exitMouse();
  void moveMouse(int x, int y, InputEventData eventData);
  void pressMouse(int x, int y, InputEventData eventData);
                      
  void setBGLayerEnabled(bool bgLayerEnabled__);
  void setFGLayerEnabled(bool fgLayerEnabled__);
  void setEffectLayerEnabled(bool effectLayerEnabled__);
  void setVerticalSolidityLayerEnabled(
      bool verticalSolidityLayerEnabled__);
  void setHorizontalSolidityLayerEnabled(
      bool horizontalSolidityLayerEnabled__);
  void setGridLayerEnabled(bool gridLayerEnabled__);
protected:

  const static int numMetatiles_ = 256;
  const static int metatilesPerRow_ = 16;
  const static int metatilesPerColumn_ = numMetatiles_ / metatilesPerRow_;
  
  int metatileIndexToX(int index) const;
  int metatileIndexToY(int index) const;
  int coordinateToMetatileIndex(int x, int y) const;

  const MetatileStructureSet* metatileStructureSet_;
  const EditableMetatileBehaviors* metatileBehaviors_;
  EditableMetatileWidthMaps* widthMaps_;
  EditableMetatileHeightMaps* heightMaps_;
  LevelEditorToolManager* toolManager_;
  const VRAMCache* vramCache_;
  
  MetatileGraphicCollection metatilesVisualBG_;
  MetatileGraphicCollection metatilesVisualFG_;
  MetatileGraphicCollection metatilesEffect_;
  MetatileGraphicCollection metatilesVerticalSolidity_;
  MetatileGraphicCollection metatilesHorizontalSolidity_;
  
  // external properties
  bool bgLayerEnabled_;
  bool fgLayerEnabled_;
  bool effectLayerEnabled_;
  bool verticalSolidityLayerEnabled_;
  bool horizontalSolidityLayerEnabled_;
  bool gridLayerEnabled_;
  
  // internal properties
//  bool pickedMetatileBoxEnabled_;
  bool highlightedMetatileBoxEnabled_;
  int highlightedMetatileIndex_;
  
  GridGraphicSceneLayer gridLayer_;
  
};


};


#endif
