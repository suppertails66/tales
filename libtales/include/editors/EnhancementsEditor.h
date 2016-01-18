#ifndef ENHANCEMENTSEDITOR_H
#define ENHANCEMENTSEDITOR_H


#include "editors/BaseEditor.h"
#include "editors/EditorMetadata.h"

namespace Tales {


class EnhancementsEditor : BaseEditor {
public:
  EnhancementsEditor(EditorMetadata& metadata__);
  
  HackSettings& hackSettings();
  
  virtual void refresh();
protected:
  EditorMetadata& metadata_;
};


};


#endif
