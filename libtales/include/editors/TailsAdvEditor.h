#ifndef TAILSADVEDITOR_H
#define TAILSADVEDITOR_H


#include "structs/Tbyte.h"
#include "gamegear/LoadedROM.h"
#include "gamegear/WritableROM.h"
#include "gamedata/TailsAdvData.h"
#include "editors/EditorMetadata.h"
#include "editors/LevelEditor.h"
#include "editors/LevelVRAMEditor.h"
#include "editors/MetatileBehaviorEditor.h"
#include "editors/LengthMapEditor.h"
#include "editors/PaletteEditor.h"
#include "editors/MetatileStructureEditor.h"
#include "editors/GraphicsEditor.h"
#include "editors/PowerUpEditor.h"
#include "editors/MusicEditor.h"
#include "editors/PaletteCycleEditor.h"
#include "editors/EnhancementsEditor.h"
#include "editors/TileMapEditor.h"
#include "structs/SaveHelper.h"
#include "structs/LoadHelper.h"
#include "structs/DataChunkID.h"
#include <string>

namespace Tales {


class TailsAdvEditor {
public:
  /**
   * Default constructor.
   */
//  TailsAdvEditor();
  
  /**
   * Constructor.
   * @param filename Name (including path) of the ROM file to open.
   */
  TailsAdvEditor(const std::string& romFileName);
  
  void save(std::string& data);
  
  int load(const Tbyte* data);
  
  void saveToFile(const std::string& filename);
  
  void loadFromFile(const std::string& filename);
  
  void exportToFile(const std::string& filename);
  
  int versionNum();
  
  EditorMetadata& metadata();
  
  LevelEditor& levelEditor();
  
  LevelVRAMEditor& vramEditor();
  
  MetatileBehaviorEditor& metatileBehaviorEditor();
  
  LengthMapEditor& lengthMapEditor();
  
  PaletteEditor& paletteEditor();
  
  MetatileStructureEditor& metatileStructureEditor();
  
  GraphicsEditor& graphicsEditor();
  
  PowerUpEditor& powerUpEditor();
  
  MusicEditor& musicEditor();
  
  PaletteCycleEditor& paletteCycleEditor();
  
  EnhancementsEditor& enhancementsEditor();
  
  TileMapEditor& tileMapEditor();
  
protected:

  const static int versionNum_ = 4;

  LoadedROM rom_;
  
  TailsAdvData data_;
  
  EditorMetadata metadata_;
  
  LevelEditor levelEditor_;
  
  LevelVRAMEditor vramEditor_;
  
  MetatileBehaviorEditor metatileBehaviorEditor_;
  
  LengthMapEditor lengthMapEditor_;
  
  PaletteEditor paletteEditor_;
  
  MetatileStructureEditor metatileStructureEditor_;
  
  GraphicsEditor graphicsEditor_;
  
  PowerUpEditor powerUpEditor_;
  
  MusicEditor musicEditor_;
  
  PaletteCycleEditor paletteCycleEditor_;
  
  EnhancementsEditor enhancementsEditor_;
  
  TileMapEditor tileMapEditor_;
  
};


};


#endif
