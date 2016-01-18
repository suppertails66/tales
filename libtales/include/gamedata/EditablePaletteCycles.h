#ifndef EDITABLEPALETTECYCLES_H
#define EDITABLEPALETTECYCLES_H


#include "structs/Tbyte.h"
#include "structs/Taddress.h"
#include "structs/Tmap.h"
#include "gamegear/LoadedROM.h"
#include "gamegear/WritableROM.h"
#include "gamedata/PaletteCycle.h"
#include "structs/SaveHelper.h"
#include "structs/LoadHelper.h"
#include <string>

namespace Tales {


class EditablePaletteCycles {
public:
  /**
   * Default constructor.
   */
  EditablePaletteCycles();
  
  /**
   * Constructor from ROM.
   * @param rom ROM to load from.
   */
  EditablePaletteCycles(LoadedROM& rom);
  
  /**
   * Saves to a string.
   * @param data String to save to.
   */
  void save(std::string& data);
  
  /**
   * Reads from a raw byte array.
   * @param data Byte array to read from.
   * @return Number of bytes read.
   */
  int load(const Tbyte* data);
  
  /**
   * Exports data to ROM.
   * @param rom WritableROM to write to.
   */
  void exportToROM(WritableROM& rom);
  
  PaletteCycle& torchPaletteCycle();
  PaletteCycle& lakeRockyMainPaletteCycle();
  PaletteCycle& lakeRockyTopPaletteCycle1();
  PaletteCycle& lakeRockyTopPaletteCycle2();
  PaletteCycle& lakeRockyBottomPaletteCycle1();
  PaletteCycle& lakeRockyBottomPaletteCycle2();
  PaletteCycle& lakeRockyBottomPaletteCycle3();
  PaletteCycle& cavernIslandPaletteCycle();
  PaletteCycle& poloyForestPaletteCycle();
  PaletteCycle& worldMapPaletteCycle();
  
protected:

  void importPoloyForestPaletteCycle(LoadedROM& rom);

  void exportPoloyForestPaletteCycle(WritableROM& rom);

  const static int TorchPaletteCycleBaseIndex = 12;
  const static int TorchPaletteCycleNumColors = 4;
  const static int TorchPaletteCycleNumStates = 4;

  const static int LakeRockyMainPaletteCycleIndex = 5;
  const static int LakeRockyMainPaletteCycleNumColors = 11;
  const static int LakeRockyMainPaletteCycleNumStates = 24;

  const static int LakeRockyTopPaletteCycle1Index = 10;
  const static int LakeRockyTopPaletteCycle1NumColors = 2;
  const static int LakeRockyTopPaletteCycle1NumStates = 2;

  const static int LakeRockyTopPaletteCycle2Index = 13;
  const static int LakeRockyTopPaletteCycle2NumColors = 2;
  const static int LakeRockyTopPaletteCycle2NumStates = 2;

  const static int LakeRockyBottomPaletteCycle1Index = 13;
  const static int LakeRockyBottomPaletteCycle1NumColors = 1;
  const static int LakeRockyBottomPaletteCycle1NumStates = 28;

  const static int LakeRockyBottomPaletteCycle2Index = 14;
  const static int LakeRockyBottomPaletteCycle2NumColors = 1;
  const static int LakeRockyBottomPaletteCycle2NumStates = 26;

  const static int LakeRockyBottomPaletteCycle3Index = 15;
  const static int LakeRockyBottomPaletteCycle3NumColors = 1;
  const static int LakeRockyBottomPaletteCycle3NumStates = 2;

  const static int CavernIslandPaletteCycleIndex = 12;
  const static int CavernIslandPaletteCycleNumColors = 4;
  const static int CavernIslandPaletteCycleNumStates = 2;
  
  // Poloy Forest's palette cycle is the only one to use colors in
  // non-sequential indices, and uses its own unique format to do so.
  // Thus it has to be handled manually.
  const static int PoloyForestPaletteCycleNumStates = 3;
  const static int PoloyForestPaletteCycleFirstColorIndex = 0;
  const static int PoloyForestPaletteCycleSecondColorIndex = 14;
  const static int PoloyForestPaletteCycleThirdColorIndex = 15;

  const static int WorldMapPaletteCycleIndex = 13;
  const static int WorldMapPaletteCycleNumColors = 3;
  const static int WorldMapPaletteCycleNumStates = 2;
  
  // Coco Island's palette effects seem to be programmed rather than using
  // a semi-standard data format like the others, so they're not (currently)
  // represented here.
  
  PaletteCycle torchPaletteCycle_;
  PaletteCycle lakeRockyMainPaletteCycle_;
  PaletteCycle lakeRockyTopPaletteCycle1_;
  PaletteCycle lakeRockyTopPaletteCycle2_;
  PaletteCycle lakeRockyBottomPaletteCycle1_;
  PaletteCycle lakeRockyBottomPaletteCycle2_;
  PaletteCycle lakeRockyBottomPaletteCycle3_;
  PaletteCycle cavernIslandPaletteCycle_;
  PaletteCycle poloyForestPaletteCycle_;
  PaletteCycle worldMapPaletteCycle_;
  
};


};


#endif
