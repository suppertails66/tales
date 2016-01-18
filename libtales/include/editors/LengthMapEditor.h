#ifndef LENGTHMAPEDITOR_H
#define LENGTHMAPEDITOR_H


#include "editors/BaseEditor.h"
#include "editors/LengthMapLayeredGraphicScene.h"
#include "gamedata/EditableMetatileWidthMaps.h"
#include "gamedata/EditableMetatileHeightMaps.h"
#include "gamedata/EditableSlopeSpeedValues.h"
#include "structs/InputEventData.h"
#include "structs/Graphic.h"

namespace Tales {


class LengthMapEditor : public BaseEditor {
public:
  LengthMapEditor(EditableMetatileWidthMaps&
                    metatileWidthMaps__,
                  EditableMetatileHeightMaps&
                    metatileHeightMaps__,
                  EditableSlopeSpeedValues&
                    slopeSpeedValues__);
  
  virtual ~LengthMapEditor();
  
  virtual void refresh();
  
  void editorEnterMouse();
  void editorExitMouse();
  void editorMoveMouse(InputEventData eventData);
  void editorPressMouse(InputEventData eventData);
  void editorReleaseMouse(InputEventData eventData);
  void editorDoubleClickMouse(InputEventData eventData);
  
  void setLengthMap(int index,
                    LengthMapLayeredGraphicScene::MapType mapType__);
  
  void drawEditorGraphic(Graphic& dst);
  
  void setEditDialogCallback(
    bool (*editDialogCallback__)(int, LengthMapValue*, void*),
    void* editDialogCallbackParam__);
    
  void setCurrentMetatileToForward();
  void setCurrentMetatileToBackward();
  
  void setGridEnabled(bool gridEnabled__);
  
  int numWidthMaps();
  int numHeightMaps();
  
  int previewWidth();
  int previewHeight();
  
  int numSlopeSpeedValues();
  int slopeSpeedValue(int index);
  void setSlopeSpeedValue(int index, int value);
protected:

  EditableMetatileWidthMaps*
    metatileWidthMaps_;
  EditableMetatileHeightMaps*
    metatileHeightMaps_;
  EditableSlopeSpeedValues*
    slopeSpeedValues_;
    
  LengthMapLayeredGraphicScene previewScene_;
  
  bool (*editDialogCallback_)(int, LengthMapValue*, void*);
  void* editDialogCallbackParam_;
  
};


};


#endif 
