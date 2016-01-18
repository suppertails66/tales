#ifndef LENGTHMAPLAYEREDGRAPHICSCENE_H
#define LENGTHMAPLAYEREDGRAPHICSCENE_H


#include "structs/LayeredGraphicScene.h"
#include "editors/GridGraphicSceneLayer.h"
#include "structs/InputEventData.h"
#include "gamedata/MetatileLengthMap.h"

namespace Tales {


class LengthMapLayeredGraphicScene : public LayeredGraphicScene {
public:
  enum MapType {
    mapTypeWidth,
    mapTypeHeight
  };

  LengthMapLayeredGraphicScene();
  
  virtual ~LengthMapLayeredGraphicScene();
  
  virtual void render(Graphic& dst,
                      Box srcbox,
                      double scale);
  
  virtual void enterMouse();
  virtual void exitMouse();
  virtual void moveMouse(InputEventData eventData);
  virtual void pressMouse(InputEventData eventData);
  virtual void releaseMouse(InputEventData eventData);
  virtual void doubleClickMouse(InputEventData eventData);
  
  void setLengthMap(MetatileLengthMap& lengthMap__,
                    MapType mapType__);
  
  void setGridLayerEnabled(bool gridLayerEnabled__);
  
  void setEditDialogCallback(
    bool (*editDialogCallback__)(int, LengthMapValue*, void*),
    void* editDialogCallbackParam__);
    
  void setCurrentMetatileToForward();
  void setCurrentMetatileToBackward();
protected:
  void alterMagnitude(int realX, int realY, bool preAltered = false);
  
  void doDialogEdit(int realX, int realY);
  
  int realCoordToLocal(int coord);

  double scale_;

  Graphic previewBuffer_;

  MetatileLengthMap* lengthMap_;
  MapType mapType_;
  
  bool gridLayerEnabled_;
  
//  bool highlightedMetatileBoxEnabled_;
//  int highlightedMetatileIndex_;
  
  GridGraphicSceneLayer gridLayer_;
  
  bool (*editDialogCallback_)(int, LengthMapValue*, void*);
  void* editDialogCallbackParam_;
};


};


#endif 
