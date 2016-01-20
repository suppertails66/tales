#ifndef LEVELEDITORTOOL_H
#define LEVELEDITORTOOL_H


namespace Tales {


class LevelEditorTools {
public:
  enum LevelEditorTool {
    none,
    metatilePaint,
    metatileAreaClone,
    objectEditor,
    spawnEditor
  };
  
  enum MetatileAreaCloneState {
    waitingForSelectionClick,
    waitingForSelectionRelease,
    readyToClone
  };
  
  enum ObjectEditorState {
    objectEditorNothingSelected,
    objectEditorSingleSelected,
    objectEditorSelectingMultiple,
    objectEditorMultipleSelected,
    objectEditorDraggingSingle,
    objectEditorDraggingMultiple
  };
  
  enum SpawnEditorState {
    spawnEditorNothingSelected,
    spawnEditorSingleSelected,
    spawnEditorDraggingSingle
  };
protected:
  
};


};


#endif
