#include "editors/PowerUpEditor.h"

namespace Tales {


PowerUpEditor::PowerUpEditor(EditablePowerUpData& powerUpData__,
                EditableEmeraldHealthRefills& emeraldHealthRefills__)
  : BaseEditor(),
    powerUpData_(powerUpData__),
    emeraldHealthRefills_(emeraldHealthRefills__) { };
  
void PowerUpEditor::refresh() {
  
}
  
EditablePowerUpData& PowerUpEditor::powerUpData() {
  return powerUpData_;
}

EditableEmeraldHealthRefills& PowerUpEditor::emeraldHealthRefills() {
  return emeraldHealthRefills_;
}


};
