#ifndef POWERUPEDITOR_H
#define POWERUPEDITOR_H


#include "editors/BaseEditor.h"
#include "gamedata/EditablePowerUpData.h"
#include "gamedata/EditableEmeraldHealthRefills.h"

namespace Tales {


class PowerUpEditor : public BaseEditor {
public:
  PowerUpEditor(EditablePowerUpData& powerUpData__,
                EditableEmeraldHealthRefills& emeraldHealthRefills__);
  
  virtual void refresh();
  
  EditablePowerUpData& powerUpData();
  EditableEmeraldHealthRefills& emeraldHealthRefills();
protected:
  EditablePowerUpData& powerUpData_;
  EditableEmeraldHealthRefills& emeraldHealthRefills_;
  
};


};


#endif
