#ifndef HACKSETTINGS_H
#define HACKSETTINGS_H


#include "structs/Tbyte.h"
#include "gamegear/WritableROM.h"
#include <string>

namespace Tales {


class HackSettings {
public:
  enum DoubleJumpFixOption {
    doubleJumpFixOff,
    doubleJumpFixOn
  };
  
  enum MaxHeightFixOption {
    maxHeightFixOff,
    maxHeightFixOn
  };
  
  enum BombJumpFixOption {
    bombJumpFixOff,
    bombJumpFixOn
  };
  
  enum InventoryHackOption {
    inventoryHackOff,
    inventoryHackOnBasic,
    inventoryHackOnFull,
    inventoryHackOnHotswapOnly,
  };
  
  enum FlightHackOption {
    flightHackOff,
    flightHackOnLimited,
    flightHackOnDisabled,
  };
  
  enum NoGameOverHackOption {
    noGameOverHackOff,
    noGameOverHackOn
  };
  
  enum SaveHackOption {
    saveHackOff,
    manualSaveHackOn,
    autoSaveHackOn,
  };
  
  enum StartOnLevelHackOption {
    startOnLevelHackOff,
    startOnLevelHackOn
  };
  
  const static int startOnLevelHackAreaBase = 0x01;
  const static int startOnLevelHackAreaLimit = 0x0D;
  
  HackSettings();
  
  void save(std::string& data);
  
  int load(const Tbyte* data);
  
  void exportToROM(WritableROM& rom);
  
  DoubleJumpFixOption doubleJumpFixOption();
  void setDoubleJumpFixOption(
      DoubleJumpFixOption doubleJumpFixOption__);
  
  MaxHeightFixOption maxHeightFixOption();
  void setMaxHeightFixOption(
      MaxHeightFixOption maxHeightFixOption__);
  
  BombJumpFixOption bombJumpFixOption();
  void setBombJumpFixOption(
      BombJumpFixOption bombJumpFixOption__);
  
  InventoryHackOption inventoryHackOption();
  void setInventoryHackOption(
      InventoryHackOption inventoryHackOption__);
  
  FlightHackOption flightHackOption();
  void setFlightHackOption(
      FlightHackOption flightHackOption__);
  
  NoGameOverHackOption noGameOverHackOption();
  void setNoGameOverHackOption(
      NoGameOverHackOption noGameOverHackOption__);
  
  SaveHackOption saveHackOption();
  void setSaveHackOption(
      SaveHackOption saveHackOption__);
  
  StartOnLevelHackOption startOnLevelHackOption();
  void setStartOnLevelHackOption(
      StartOnLevelHackOption startOnLevelHackOption__);
  
  int startOnLevelHackArea();
  void setStartOnLevelHackArea(int startOnLevelHackArea__);
  
  int startOnLevelHackMap();
  void setStartOnLevelHackMap(int startOnLevelHackMap__);
  
  int startOnLevelHackSpawn();
  void setStartOnLevelHackSpawn(int startOnLevelHackSpawn__);
  
protected:
  const static int versionNum_ = 3;

  DoubleJumpFixOption doubleJumpFixOption_;
  
  MaxHeightFixOption maxHeightFixOption_;
  
  BombJumpFixOption bombJumpFixOption_;
  
  InventoryHackOption inventoryHackOption_;
  
  FlightHackOption flightHackOption_;
  
  NoGameOverHackOption noGameOverHackOption_;
  
  SaveHackOption saveHackOption_;
  
  StartOnLevelHackOption startOnLevelHackOption_;
  int startOnLevelHackArea_;
  int startOnLevelHackMap_;
  int startOnLevelHackSpawn_;
  
};


};


#endif
