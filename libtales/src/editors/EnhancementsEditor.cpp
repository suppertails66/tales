#include "editors/EnhancementsEditor.h"

namespace Tales {


EnhancementsEditor::EnhancementsEditor(EditorMetadata& metadata__)
  : metadata_(metadata__) { };
  
HackSettings& EnhancementsEditor::hackSettings() {
  return metadata_.hackSettings();
}
  
void EnhancementsEditor::refresh() {
  
}


};
