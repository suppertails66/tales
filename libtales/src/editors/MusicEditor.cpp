#include "editors/MusicEditor.h"

namespace Tales {


MusicEditor::MusicEditor(EditableMusicAssignments& musicAssignments__,
              EditableRadioMusic& radioMusic__)
  : BaseEditor(),
    musicAssignments_(musicAssignments__),
    radioMusic_(radioMusic__) { };
  
void MusicEditor::refresh() {
  
}
  
int MusicEditor::numAreaTracks() {
  return musicAssignments_.numUsedEntries;
}

int MusicEditor::numRadioTracks() {
  return radioMusic_.numMusicEntries();
}

int MusicEditor::areaTrack(int index) {
  return musicAssignments_.musicAssignment(index);
}

int MusicEditor::radioTrack(int index) {
  return radioMusic_.musicEntry(index);
}

void MusicEditor::setAreaTrack(int index, int value) {
  musicAssignments_.musicAssignment(index) = value;
}

void MusicEditor::setRadioTrack(int index, int value) {
  radioMusic_.musicEntry(index) = value;
}


};
