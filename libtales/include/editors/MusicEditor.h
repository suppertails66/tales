#ifndef MUSICEDITOR_H
#define MUSICEDITOR_H


#include "editors/BaseEditor.h"
#include "gamedata/EditableMusicAssignments.h"
#include "gamedata/EditableRadioMusic.h"

namespace Tales {


class MusicEditor : public BaseEditor {
public:
  MusicEditor(EditableMusicAssignments& musicAssignments__,
              EditableRadioMusic& radioMusic__);
  
  virtual void refresh();
  
  int numAreaTracks();
  int numRadioTracks();
  
  int areaTrack(int index);
  int radioTrack(int index);
  
  void setAreaTrack(int index, int value);
  void setRadioTrack(int index, int value);
protected:
  EditableMusicAssignments& musicAssignments_;
  EditableRadioMusic& radioMusic_;
  
};


};


#endif
