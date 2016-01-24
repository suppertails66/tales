#ifndef TILEMAPEDITORTOOL_H
#define TILEMAPEDITORTOOL_H


namespace Tales {


class TileMapEditorTools {
public:
  enum TileMapEditorTool {
    regular,
    pencil,
    areaClone
  };
  
  enum AreaCloneState {
    areaCloneWaitingForSelect,
    areaCloneSelecting,
    areaCloneCloning
  };
protected:
  
};


};


#endif
