#include "gamedata/ObjectStates.h"
#include <iostream>

namespace Tales {


int ObjectStates::numObjects() {
  return numObjects_;
}

int ObjectStates::numStatesPerObject(int objectNum) {
  return numStatesPerObject_[objectNum];
}
  
ObjectStates::ObjectSpawnParameterType ObjectStates
    ::objectSpawnParameterType(int objectNum) {
  switch (static_cast<ObjectTypeIDs::ObjectTypeID>(objectNum)) {
  case ObjectTypeIDs::warp:
    return spawnParameterWarp;
    break;
  case ObjectTypeIDs::electricField:
  case ObjectTypeIDs::electricFieldSwitch:
    return spawnParameterManual;
    break;
  case ObjectTypeIDs::waterMissileLauncher:
    return spawnParameterMissileLauncher;
    break;
  case ObjectTypeIDs::waterMine:
    return spawnParameterEnemyMine;
    break;
  default:
    return spawnParameterStandard;
    break;
  }
}
  
ObjectStateInfo ObjectStates::objectStateInfo(int objectNum, int stateIndex) {
  return objectStates(objectNum)[stateIndex - 1];
}
  
ObjectStateInfo ObjectStates
    ::findObjectStateInfo(int objectNum, int stateNum) {
  for (int i = 0; i < numStatesPerObject(objectNum); i++) {
    if (objectStates(objectNum)[i].stateNum == stateNum) {
      return objectStates(objectNum)[i];
    }
  }
  
  ObjectStateInfo result = { -1, "", -1, ObjectStateInfo::none };
  return result;
}
  
const ObjectStateInfo* ObjectStates::objectStates(int objectNum) {
  switch (objectNum) {
  case 0x00: return obj03States; break;
  case 0x01: return obj03States; break;
  case 0x02: return obj03States; break;
  case 0x03: return obj03States; break;
  case 0x04: return obj04States; break;
  case 0x05: return obj05States; break;
  case 0x06: return obj06States; break;
  case 0x07: return obj07States; break;
  case 0x08: return obj08States; break;
  case 0x09: return obj09States; break;
  case 0x0A: return obj0AStates; break;
  case 0x0B: return obj0BStates; break;
  case 0x0C: return obj0CStates; break;
  case 0x0D: return obj0DStates; break;
  case 0x0E: return obj0EStates; break;
  case 0x0F: return obj0FStates; break;
  case 0x10: return obj10States; break;
  case 0x11: return obj11States; break;
  case 0x12: return obj12States; break;
  case 0x13: return obj13States; break;
  case 0x14: return obj14States; break;
  case 0x15: return obj15States; break;
  case 0x16: return obj16States; break;
  case 0x17: return obj17States; break;
  case 0x18: return obj18States; break;
  case 0x19: return obj19States; break;
  case 0x1A: return obj1AStates; break;
  case 0x1B: return obj1BStates; break;
  case 0x1C: return obj1CStates; break;
  case 0x1D: return obj1DStates; break;
  case 0x1E: return obj1EStates; break;
  case 0x1F: return obj1FStates; break;
  case 0x20: return obj20States; break;
  case 0x21: return obj21States; break;
  case 0x22: return obj22States; break;
  case 0x23: return obj23States; break;
  case 0x24: return obj24States; break;
  case 0x25: return obj25States; break;
  case 0x26: return obj26States; break;
  case 0x27: return obj27States; break;
  case 0x28: return obj28States; break;
  case 0x29: return obj29States; break;
  case 0x2A: return obj2AStates; break;
  case 0x2B: return obj2BStates; break;
  case 0x2C: return obj2CStates; break;
  case 0x2D: return obj2DStates; break;
  case 0x2E: return obj2EStates; break;
  case 0x2F: return obj2FStates; break;
  case 0x30: return obj30States; break;
  case 0x31: return obj31States; break;
  case 0x32: return obj32States; break;
  case 0x33: return obj33States; break;
  case 0x34: return obj34States; break;
  case 0x35: return obj35States; break;
  case 0x36: return obj36States; break;
  case 0x37: return obj37States; break;
  case 0x38: return obj38States; break;
  case 0x39: return obj39States; break;
  case 0x3A: return obj3AStates; break;
  case 0x3B: return obj3BStates; break;
  case 0x3C: return obj3CStates; break;
  case 0x3D: return obj3DStates; break;
  case 0x3E: return obj3EStates; break;
  case 0x3F: return obj3FStates; break;
  case 0x40: return obj40States; break;
  case 0x41: return obj41States; break;
  case 0x42: return obj42States; break;
  case 0x43: return obj43States; break;
  case 0x44: return obj44States; break;
  case 0x45: return obj45States; break;
  case 0x46: return obj46States; break;
  case 0x47: return obj47States; break;
  case 0x48: return obj48States; break;
  case 0x49: return obj49States; break;
  case 0x4A: return obj4AStates; break;
  case 0x4B: return obj4BStates; break;
  case 0x4C: return obj4CStates; break;
  case 0x4D: return obj4DStates; break;
  case 0x4E: return obj4EStates; break;
  case 0x4F: return obj4FStates; break;
  case 0x50: return obj50States; break;
  case 0x51: return obj51States; break;
  case 0x52: return obj52States; break;
  case 0x53: return obj53States; break;
  case 0x54: return obj54States; break;
  case 0x55: return obj55States; break;
  case 0x56: return obj56States; break;
  case 0x57: return obj57States; break;
  case 0x58: return obj58States; break;
  case 0x59: return obj59States; break;
  case 0x5A: return obj5AStates; break;
  case 0x5B: return obj5BStates; break;
  case 0x5C: return obj5CStates; break;
  case 0x5D: return obj5DStates; break;
  case 0x5E: return obj5EStates; break;
  case 0x5F: return obj5FStates; break;
  case 0x60: return obj60States; break;
  case 0x61: return obj61States; break;
  case 0x62: return obj62States; break;
  case 0x63: return obj63States; break;
  case 0x64: return obj64States; break;
  case 0x65: return obj65States; break;
  case 0x66: return obj66States; break;
  case 0x67: return obj67States; break;
  case 0x68: return obj68States; break;
  case 0x69: return obj69States; break;
  case 0x6A: return obj6AStates; break;
  case 0x6B: return obj6BStates; break;
  case 0x6C: return obj6CStates; break;
  default:
    return obj03States;
    break;
  }
}
  
const int ObjectStates::numStatesPerObject_[numObjects_] =
  {
    // 0
    -1,
    -1,
    -1,
    1,
    4,
    3,
    2,
    1,
    1,
    1,
    // 0x0A
    2,
    7,
    4,
    0xF,
    0xF,
    0xF,
    // 0x10
    2,
    2,
    3,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    // 0x1A
    2,
    4,
    4,
    4,
    4,
    4,
    // 0x20
    4,
    4,
    4,
    3,
    4,
    4,
    4,
    2,
    2,
    7,
    // 0x2A
    7,
    7,
    7,
    7,
    7,
    0x20,
    // 0x30
    7,
    0xD,
    1,
    8,
    7,
    7,
    6,
    3,
    4,
    5,
    // 0x3A
    4,
    6,
    4,
    5,
    9,
    0xB,
    // 0x40
    4,
    3,
    4,
    2,
    5,
    4,
    3,
    8,
    3,
    3,
    // 0x4A
    3,
    1,
    2,
    1,
    4,
    9,
    // 0x50
    1,
    1,
    1,
    1,
    1,
    0xF,
    0xF,
    4,
    3,
    3,
    // 0x5A
    3,
    6,
    6,
    5,
    5,
    5,
    // 0x60
    0x11,
    0x15,
    0x1B,
    0xB,
    3,
    8,
    0xF,
    0xC,
    3,
    3,
    // 0x6A
    7,
    7,
    4
  };

  
const ObjectStateInfo ObjectStates::obj03States[1] =
  {
    { 1, "Normal", 154, ObjectStateInfo::none }
  };


const ObjectStateInfo ObjectStates::obj04States[4] =
  {
    { 1, "Flying in", 186, ObjectStateInfo::none },
    { 2, "Display", 186, ObjectStateInfo::none },
    { 3, "Flying out", 186, ObjectStateInfo::none },
    { 4, "Despawn?", 186, ObjectStateInfo::none }
  };

const ObjectStateInfo ObjectStates::obj05States[3] =
  {
    { 1, "Bouncing", 187, ObjectStateInfo::none },
    { 2, "Collect?", 187, ObjectStateInfo::none },
    { 3, "Stationary", 187, ObjectStateInfo::none }
  }; 
  
const ObjectStateInfo ObjectStates::obj06States[2] =
  {
    { 1, "Normal", 191, ObjectStateInfo::none },
    { 2, "Despawn?", 191, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj07States[2] =
  {
    { 1, "Normal", 191, ObjectStateInfo::none },
    { 2, "Despawn?", 191, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj08States[1] =
  {
    { 1, "Normal", 193, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj09States[1] =
  {
    { 1, "Normal", 193, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj0AStates[2] =
  {
    { 1, "Normal", 197, ObjectStateInfo::none },
    { 2, "Normal?", 197, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj0BStates[7] =
  {
    { 1, "Return to dock cutscene", 207, ObjectStateInfo::none },
    { 2, "Leave dock cutscene", 200, ObjectStateInfo::none },
    { 3, "?", 200, ObjectStateInfo::none },
    { 4, "?", 200, ObjectStateInfo::none },
    { 5, "Lake Rocky -> Coco Island cutscene", -1, ObjectStateInfo::none },
    { 6, "Battle Fortress 1 -> 2 cutscene", -1, ObjectStateInfo::none },
    { 7, "?", 200, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj0CStates[4] =
  {
    { 1, "Arm", 210, ObjectStateInfo::none },
    { 2, "Claw", 211, ObjectStateInfo::none },
    { 3, "Arm reset?", 210, ObjectStateInfo::none },
    { 4, "Claw reset?", 211, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj0DStates[0xF] =
  {
    { 1, "Small?", 212, ObjectStateInfo::none },
    { 2, "Regular?", 213, ObjectStateInfo::none },
    { 3, "Large?", 214, ObjectStateInfo::none },
    { 4, "?", 214, ObjectStateInfo::none },
    { 5, "?", 214, ObjectStateInfo::none },
    { 6, "?", 214, ObjectStateInfo::none },
    { 7, "?", 214, ObjectStateInfo::none },
    { 8, "?", 214, ObjectStateInfo::none },
    { 9, "?", 214, ObjectStateInfo::none },
    { 0xA, "?", 214, ObjectStateInfo::none },
    { 0xB, "?", 214, ObjectStateInfo::none },
    { 0xC, "?", 214, ObjectStateInfo::none },
    { 0xD, "?", 214, ObjectStateInfo::none },
    { 0xE, "?", 214, ObjectStateInfo::none },
    { 0xF, "?", 214, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj0EStates[0xF] =
  {
    { 1, "Small?", 212, ObjectStateInfo::none },
    { 2, "Regular?", 213, ObjectStateInfo::none },
    { 3, "Large?", 214, ObjectStateInfo::none },
    { 4, "?", 214, ObjectStateInfo::none },
    { 5, "?", 214, ObjectStateInfo::none },
    { 6, "?", 214, ObjectStateInfo::none },
    { 7, "?", 214, ObjectStateInfo::none },
    { 8, "?", 214, ObjectStateInfo::none },
    { 9, "?", 214, ObjectStateInfo::none },
    { 0xA, "?", 214, ObjectStateInfo::none },
    { 0xB, "?", 214, ObjectStateInfo::none },
    { 0xC, "?", 214, ObjectStateInfo::none },
    { 0xD, "?", 214, ObjectStateInfo::none },
    { 0xE, "?", 214, ObjectStateInfo::none },
    { 0xF, "?", 214, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj0FStates[0xF] =
  {
    { 1, "Small?", 212, ObjectStateInfo::none },
    { 2, "Regular?", 213, ObjectStateInfo::none },
    { 3, "Large?", 214, ObjectStateInfo::none },
    { 4, "?", 214, ObjectStateInfo::none },
    { 5, "?", 214, ObjectStateInfo::none },
    { 6, "?", 214, ObjectStateInfo::none },
    { 7, "?", 214, ObjectStateInfo::none },
    { 8, "?", 214, ObjectStateInfo::none },
    { 9, "?", 214, ObjectStateInfo::none },
    { 0xA, "?", 214, ObjectStateInfo::none },
    { 0xB, "?", 214, ObjectStateInfo::none },
    { 0xC, "?", 214, ObjectStateInfo::none },
    { 0xD, "?", 214, ObjectStateInfo::none },
    { 0xE, "?", 214, ObjectStateInfo::none },
    { 0xF, "?", 214, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj10States[2] =
  {
    { 1, "Normal", 216, ObjectStateInfo::none },
    { 2, "Detonating", 216, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj11States[2] =
  {
    { 1, "Normal", 216, ObjectStateInfo::none },
    { 2, "Detonating", 216, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj12States[3] =
  {
    { 1, "Normal", 216, ObjectStateInfo::none },
    { 2, "Detonating", 216, ObjectStateInfo::none },
    { 3, "? Possibly invalid?", 216, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj13States[2] =
  {
    { 1, "Normal", 216, ObjectStateInfo::none },
    { 2, "Detonating", 216, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj14States[2] =
  {
    { 1, "Normal", 218, ObjectStateInfo::none },
    { 2, "Detonating", 222, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj15States[2] =
  {
    { 1, "Normal", 216, ObjectStateInfo::none },
    { 2, "Detonating", 216, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj16States[2] =
  {
    { 1, "Swing right", 225, ObjectStateInfo::none },
    { 2, "Swing left", 223, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj17States[2] =
  {
    { 1, "Swing right", 225, ObjectStateInfo::none },
    { 2, "Swing left", 223, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj18States[2] =
  {
    { 1, "Swing right", 225, ObjectStateInfo::none },
    { 2, "Swing left", 223, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj19States[2] =
  {
    { 1, "Swing right", 225, ObjectStateInfo::none },
    { 2, "Swing left", 223, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj1AStates[2] =
  {
    { 1, "Swing right", 225, ObjectStateInfo::none },
    { 2, "Swing left", 223, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj1BStates[4] =
  {
    { 1, "Normal", 229, ObjectStateInfo::none },
    { 2, "Swerve up", 229, ObjectStateInfo::none },
    { 3, "Swerve down", 229, ObjectStateInfo::none },
    { 4, "Detonating", 229, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj1CStates[4] =
  {
    { 1, "Normal", 229, ObjectStateInfo::none },
    { 2, "Swerve up", 229, ObjectStateInfo::none },
    { 3, "Swerve down", 229, ObjectStateInfo::none },
    { 4, "Detonating", 229, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj1DStates[4] =
  {
    { 1, "Normal", 229, ObjectStateInfo::none },
    { 2, "Swerve up", 229, ObjectStateInfo::none },
    { 3, "Swerve down", 229, ObjectStateInfo::none },
    { 4, "Detonating", 229, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj1EStates[4] =
  {
    { 1, "Normal", 229, ObjectStateInfo::none },
    { 2, "Swerve up", 229, ObjectStateInfo::none },
    { 3, "Swerve down", 229, ObjectStateInfo::none },
    { 4, "Detonating", 229, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj1FStates[4] =
  {
    { 1, "Normal", 229, ObjectStateInfo::none },
    { 2, "Swerve up", 229, ObjectStateInfo::none },
    { 3, "Swerve down", 229, ObjectStateInfo::none },
    { 4, "Detonating", 229, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj20States[4] =
  {
    { 1, "Normal", 229, ObjectStateInfo::none },
    { 2, "Swerve up", 229, ObjectStateInfo::none },
    { 3, "Swerve down", 229, ObjectStateInfo::none },
    { 4, "Detonating", 229, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj21States[4] =
  {
    { 1, "Normal", 229, ObjectStateInfo::none },
    { 2, "Swerve up", 229, ObjectStateInfo::none },
    { 3, "Swerve down", 229, ObjectStateInfo::none },
    { 4, "Detonating", 229, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj22States[4] =
  {
    { 1, "Normal", 229, ObjectStateInfo::none },
    { 2, "Swerve up", 229, ObjectStateInfo::none },
    { 3, "Swerve down", 229, ObjectStateInfo::none },
    { 4, "Detonating", 229, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj23States[3] =
  {
    { 1, "Main logic?", 231, ObjectStateInfo::none },
    { 2, "Bullet", 231, ObjectStateInfo::none },
    { 3, "Detonating", 231, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj24States[4] =
  {
    { 1, "Fire up", 233, ObjectStateInfo::none },
    { 2, "Fire up-right", 234, ObjectStateInfo::none },
    { 3, "Fire up-left", 235, ObjectStateInfo::none },
    { 4, "Detonating", 233, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj25States[4] =
  {
    { 1, "Fire up", 233, ObjectStateInfo::none },
    { 2, "Fire up-right", 234, ObjectStateInfo::none },
    { 3, "Fire up-left", 235, ObjectStateInfo::none },
    { 4, "Detonating", 233, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj26States[4] =
  {
    { 1, "Fire up", 233, ObjectStateInfo::none },
    { 2, "Fire up-right", 234, ObjectStateInfo::none },
    { 3, "Fire up-left", 235, ObjectStateInfo::none },
    { 4, "Detonating", 233, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj27States[2] =
  {
    { 1, "Normal", 236, ObjectStateInfo::none },
    { 2, "Detonating", 236, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj28States[2] =
  {
    { 1, "Normal", 236, ObjectStateInfo::none },
    { 2, "Detonating", 236, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj29States[7] =
  {
    { 1, "Waiting for contact", 237, ObjectStateInfo::none },
    { 2, "Blinking after contact", 237, ObjectStateInfo::none },
    { 3, "Picked up by Tails", 237, ObjectStateInfo::none },
    { 4, "Blinking after Tails pickup", 237, ObjectStateInfo::none },
    { 5, "Falling", 237, ObjectStateInfo::none },
    { 6, "Picked up by Remote Robot", 237, ObjectStateInfo::none },
    { 7, "Falling after Remote Robot pickup", 237, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj2AStates[7] =
  {
    { 1, "Waiting for contact", 237, ObjectStateInfo::none },
    { 2, "Blinking after contact", 237, ObjectStateInfo::none },
    { 3, "Picked up by Tails", 237, ObjectStateInfo::none },
    { 4, "Blinking after Tails pickup", 237, ObjectStateInfo::none },
    { 5, "Falling", 237, ObjectStateInfo::none },
    { 6, "Picked up by Remote Robot", 237, ObjectStateInfo::none },
    { 7, "Falling after Remote Robot pickup", 237, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj2BStates[7] =
  {
    { 1, "Waiting for contact", 237, ObjectStateInfo::none },
    { 2, "Blinking after contact", 237, ObjectStateInfo::none },
    { 3, "Picked up by Tails", 237, ObjectStateInfo::none },
    { 4, "Blinking after Tails pickup", 237, ObjectStateInfo::none },
    { 5, "Falling", 237, ObjectStateInfo::none },
    { 6, "Picked up by Remote Robot", 237, ObjectStateInfo::none },
    { 7, "Falling after Remote Robot pickup", 237, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj2CStates[7] =
  {
    { 1, "Waiting for contact", 237, ObjectStateInfo::none },
    { 2, "Blinking after contact", 237, ObjectStateInfo::none },
    { 3, "Picked up by Tails", 237, ObjectStateInfo::none },
    { 4, "Blinking after Tails pickup", 237, ObjectStateInfo::none },
    { 5, "Falling", 237, ObjectStateInfo::none },
    { 6, "Picked up by Remote Robot", 237, ObjectStateInfo::none },
    { 7, "Falling after Remote Robot pickup", 237, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj2DStates[7] =
  {
    { 1, "Waiting for contact", 237, ObjectStateInfo::none },
    { 2, "Blinking after contact", 237, ObjectStateInfo::none },
    { 3, "Picked up by Tails", 237, ObjectStateInfo::none },
    { 4, "Blinking after Tails pickup", 237, ObjectStateInfo::none },
    { 5, "Falling", 237, ObjectStateInfo::none },
    { 6, "Picked up by Remote Robot", 237, ObjectStateInfo::none },
    { 7, "Falling after Remote Robot pickup", 237, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj2EStates[7] =
  {
    { 1, "Waiting for contact", 237, ObjectStateInfo::none },
    { 2, "Blinking after contact", 237, ObjectStateInfo::none },
    { 3, "Picked up by Tails", 237, ObjectStateInfo::none },
    { 4, "Blinking after Tails pickup", 237, ObjectStateInfo::none },
    { 5, "Falling", 237, ObjectStateInfo::none },
    { 6, "Picked up by Remote Robot", 237, ObjectStateInfo::none },
    { 7, "Falling after Remote Robot pickup", 237, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj2FStates[0x20] =
  {
    { 1, "Regular Bomb (wrong name)", 237, ObjectStateInfo::none },
    { 2, "Large Bomb", 237, ObjectStateInfo::none },
    { 3, "Remote Bomb", 237, ObjectStateInfo::none },
    { 4, "Napalm Bomb", 237, ObjectStateInfo::none },
    { 5, "Triple Bomb", 237, ObjectStateInfo::none },
    { 6, "Wrench", 237, ObjectStateInfo::none },
    { 7, "Helmet", 237, ObjectStateInfo::none },
    { 8, "Item Radar", 237, ObjectStateInfo::none },
    { 9, "Radio", 237, ObjectStateInfo::none },
    { 0xA, "Hammer", 237, ObjectStateInfo::none },
    { 0xB, "Teleport Device", 237, ObjectStateInfo::none },
    { 0xC, "Night Vision", 237, ObjectStateInfo::none },
    { 0xD, "Speed Boots", 237, ObjectStateInfo::none },
    { 0xE, "Super Glove", 237, ObjectStateInfo::none },
    { 0xF, "Fang", 237, ObjectStateInfo::none },
    { 0x10, "Knuckles", 237, ObjectStateInfo::none },
    { 0x11, "Sonic", 237, ObjectStateInfo::none },
    { 0x12, "Proton Torpedo", 237, ObjectStateInfo::none },
    { 0x13, "Vulcan Gun", 237, ObjectStateInfo::none },
    { 0x14, "Extra Speed", 237, ObjectStateInfo::none },
    { 0x15, "Extra Armor", 237, ObjectStateInfo::none },
    { 0x16, "Anti-Air Missile", 237, ObjectStateInfo::none },
    { 0x17, "Spark", 237, ObjectStateInfo::none },
    { 0x18, "Mine", 237, ObjectStateInfo::none },
    { 0x19, "Rocket Booster", 237, ObjectStateInfo::none },
    { 0x1A, "Remote Robot", 237, ObjectStateInfo::none },
    { 0x20, "Blue Chaos Emerald", 237, ObjectStateInfo::none },
    { 0x21, "Green Chaos Emerald", 237, ObjectStateInfo::none },
    { 0x22, "Purple Chaos Emerald", 237, ObjectStateInfo::none },
    { 0x23, "Red Chaos Emerald", 237, ObjectStateInfo::none },
    { 0x24, "White Chaos Emerald", 237, ObjectStateInfo::none },
    { 0x25, "Yellow Chaos Emerald", 237, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj30States[7] =
  {
    { 1, "Start flying left?", 240, ObjectStateInfo::left },
    { 2, "Fly and attack left", 240, ObjectStateInfo::left },
    { 3, "Fly and attack right", 240, ObjectStateInfo::right },
    { 4, "Flames left", 243, ObjectStateInfo::none },
    { 5, "Flames right", 243, ObjectStateInfo::none },
    { 6, "Bullet left", 241, ObjectStateInfo::none },
    { 7, "Bullet right", 241, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj31States[0xD] =
  {
    { 1, "Stationary left idle", 246, ObjectStateInfo::left },
    { 2, "Stationary right idle", 246, ObjectStateInfo::right },
    { 3, "Walk left", 246, ObjectStateInfo::left },
    { 4, "Walk right", 246, ObjectStateInfo::right },
    { 5, "?", 246, ObjectStateInfo::none },
    { 6, "Stationary left firing", 246, ObjectStateInfo::left },
    { 7, "Stationary right firing", 246, ObjectStateInfo::right },
    { 8, "Firing left / retreating right?", 246, ObjectStateInfo::left },
    { 9, "Firing right / retreating left?", 246, ObjectStateInfo::right },
    { 0xA, "Bullet left", 248, ObjectStateInfo::none },
    { 0xB, "Bullet right", 248, ObjectStateInfo::none },
    { 0xC, "Moving left after firing left", 246, ObjectStateInfo::left },
    { 0xD, "Moving right after firing right", 246, ObjectStateInfo::right }
  }; 

const ObjectStateInfo ObjectStates::obj32States[1] =
  {
    { 1, "Normal", 249, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj33States[8] =
  {
    { 1, "Idle", 252, ObjectStateInfo::none },
    { 2, "Moving left", 250, ObjectStateInfo::left },
    { 3, "Moving right", 250, ObjectStateInfo::right },
    { 4, "Dropping bomb", 252, ObjectStateInfo::none },
    { 5, "Retreating to original position?", 250, ObjectStateInfo::none },
    { 6, "Idling after retreat", 252, ObjectStateInfo::none },
    { 7, "Bomb", 253, ObjectStateInfo::none },
    { 8, "? Invalid?", 252, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj34States[7] =
  {
    { 1, "Idle left", 254, ObjectStateInfo::left },
    { 2, "Idle right", 254, ObjectStateInfo::right },
    { 3, "Fire, then turn left", 254, ObjectStateInfo::left },
    { 4, "Fire, then turn right", 254, ObjectStateInfo::right },
    { 5, "Being rotated by Wrench item", 255, ObjectStateInfo::none },
    { 6, "Bullet right", 256, ObjectStateInfo::none },
    { 7, "Bullet left", 256, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj35States[7] =
  {
    { 1, "Idle left", 254, ObjectStateInfo::left },
    { 2, "Idle right", 254, ObjectStateInfo::right },
    { 3, "Fire, then turn left", 254, ObjectStateInfo::left },
    { 4, "Fire, then turn right", 254, ObjectStateInfo::right },
    { 5, "Being rotated by Wrench item", 255, ObjectStateInfo::none },
    { 6, "Bullet right", 256, ObjectStateInfo::none },
    { 7, "Bullet left", 256, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj36States[6] =
  {
    { 1, "Idle left", 258, ObjectStateInfo::left },
    { 2, "Idle right", 258, ObjectStateInfo::right },
    { 3, "Fire, then turn left", 257, ObjectStateInfo::left },
    { 4, "Fire, then turn right", 257, ObjectStateInfo::right },
    { 5, "Bullet left", 259, ObjectStateInfo::none },
    { 6, "Bullet right", 259, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj37States[3] =
  {
    { 1, "Idle", 260, ObjectStateInfo::none },
    { 2, "Attacking", 261, ObjectStateInfo::none },
    { 3, "Pausing after attack", 260, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj38States[4] =
  {
    { 1, "Idle", 262, ObjectStateInfo::none },
    { 2, "Attack left?", 264, ObjectStateInfo::none },
    { 3, "Attack right?", 264, ObjectStateInfo::none },
    { 4, "Attack left?", 264, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj39States[5] =
  {
    { 1, "Advancing left", 266, ObjectStateInfo::left },
    { 2, "Throwing bomb left", 271, ObjectStateInfo::left },
    { 3, "Retreating", 266, ObjectStateInfo::right },
    { 4, "Bomb", 269, ObjectStateInfo::none },
    { 5, "Waiting after retreat", 267, ObjectStateInfo::left }
  }; 

const ObjectStateInfo ObjectStates::obj3AStates[4] =
  {
    { 1, "Initialize to left-facing flamethrower", 277,
      ObjectStateInfo::left },
    { 2, "Initialize to right-facing flamethrower", 277,
      ObjectStateInfo::right },
    { 3, "Initialize to right-facing flamethrower", 277,
      ObjectStateInfo::right },
    { 0x81, "Initialize to jump mode", 278, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj3BStates[6] =
  {
    { 1, "Idle left", 282, ObjectStateInfo::left },
    { 2, "Idle right", 282, ObjectStateInfo::right },
    { 3, "Firing mode straight", 282, ObjectStateInfo::none },
    { 4, "Firing mode up", 283, ObjectStateInfo::none },
    { 5, "Bullet straight", 285, ObjectStateInfo::none },
    { 6, "Bullet up", 285, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj3CStates[4] =
  {
    { 1, "Idle", 287, ObjectStateInfo::none },
    { 2, "Jump trigger?", 286, ObjectStateInfo::none },
    { 3, "Jumping left", 288, ObjectStateInfo::left },
    { 4, "Jumping right", 288, ObjectStateInfo::right }
  }; 

const ObjectStateInfo ObjectStates::obj3DStates[5] =
  {
    { 1, "Moving left", 289, ObjectStateInfo::left },
    { 2, "Shoot and flee right", 289, ObjectStateInfo::right },
    { 3, "Moving right", 289, ObjectStateInfo::right },
    { 4, "Shoot and flee left", 289, ObjectStateInfo::left },
    { 5, "Bullet", 291, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj3EStates[9] =
  {
    { 1, "Idle (left)", 293, ObjectStateInfo::left },
    { 2, "Throwing rocks", 292, ObjectStateInfo::none },
    { 3, "Thrown rock?", 294, ObjectStateInfo::none },
    { 4, "Start rock explosion?", 295, ObjectStateInfo::none },
    { 5, "Thrown rock long?", 294, ObjectStateInfo::none },
    { 6, "Thrown rock high?", 294, ObjectStateInfo::none },
    { 7, "Pause after throwing rocks", 293, ObjectStateInfo::none },
    { 8, "Rock explosion", 294, ObjectStateInfo::none },
    { 0x81, "Idle (right)", 293, ObjectStateInfo::right }
  }; 

const ObjectStateInfo ObjectStates::obj3FStates[0xB] =
  {
    { 1, "Start attack run to left?", 296, ObjectStateInfo::left },
    { 2, "Attack run left", 296, ObjectStateInfo::left },
    { 3, "Start attack run right?", 296, ObjectStateInfo::right },
    { 4, "Attack run right", 296, ObjectStateInfo::right },
    { 5, "Bullet horizontal", 304, ObjectStateInfo::left },
    { 6, "Start turnaround right?", 300, ObjectStateInfo::right },
    { 7, "Turnaround right", 300, ObjectStateInfo::right },
    { 8, "Fly away upper-right", 303, ObjectStateInfo::right },
    { 9, "Fly away right", 303, ObjectStateInfo::right },
    { 0xA, "Bullet diagonal", 304, ObjectStateInfo::left },
    { 0xB, "? Go to state 1?", 296, ObjectStateInfo::left }
  }; 

const ObjectStateInfo ObjectStates::obj40States[4] =
  {
    { 1, "Idle", 307, ObjectStateInfo::none },
    { 2, "Start attack", 309, ObjectStateInfo::none },
    { 3, "Fly away", 309, ObjectStateInfo::none },
    { 4, "Bomb", 311, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj41States[3] =
  {
    { 1, "Mine dropper mode", 312, ObjectStateInfo::none },
    { 2, "Dropped mine", 312, ObjectStateInfo::none },
    { 3, "Passive mine", 312, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj42States[4] =
  {
    { 1, "Idle?", 313, ObjectStateInfo::none },
    { 2, "Idle after firing", 313, ObjectStateInfo::none },
    { 3, "Fire right", 313, ObjectStateInfo::none },
    { 4, "Fire left", 313, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj43States[2] =
  {
    { 1, "Idle", 317, ObjectStateInfo::none },
    { 2, "Run around", 318, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj44States[5] =
  {
    { 1, "Idle", 320, ObjectStateInfo::none },
    { 2, "Spawn bomb left", 320, ObjectStateInfo::left },
    { 3, "Spawn bomb right", 320, ObjectStateInfo::right },
    { 4, "?", 320, ObjectStateInfo::none },
    { 5, "Bomb active?", 320, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj45States[4] =
  {
    { 1, "Idle", 322, ObjectStateInfo::none },
    { 2, "Bird launched", 322, ObjectStateInfo::none },
    { 3, "Bird missile", 322, ObjectStateInfo::none },
    { 4, "Exploding into passageway", 322, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj46States[3] =
  {
    { 1, "Idle", 324, ObjectStateInfo::none },
    { 2, "Conveyor duck", 324, ObjectStateInfo::none },
    { 3, "Conveyor duck falling?", 324, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj47States[8] =
  {
    { 1, "Idle", 330, ObjectStateInfo::none },
    { 2, "Bees currently spawned?", 330, ObjectStateInfo::none },
    { 3, "Spawn bees", 330, ObjectStateInfo::none },
    { 4, "Newly spawned bee?", 329, ObjectStateInfo::none },
    { 5, "Bee", 329, ObjectStateInfo::none },
    { 6, "?", 329, ObjectStateInfo::none },
    { 7, "Newly spawned queen bee?", 327, ObjectStateInfo::none },
    { 8, "Queen bee", 327, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj48States[3] =
  {
    { 1, "Idle", 333, ObjectStateInfo::none },
    { 2, "Active short?", 333, ObjectStateInfo::none },
    { 3, "Active long?", 333, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj49States[3] =
  {
    { 1, "Inactive", 334, ObjectStateInfo::none },
    { 2, "Active", 334, ObjectStateInfo::none },
    { 3, "Laser", 335, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj4AStates[3] =
  {
    { 1, "Horizontal", 337, ObjectStateInfo::none },
    { 2, "Vertical", 336, ObjectStateInfo::none },
    { 3, "?", 337, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj4BStates[1] =
  {
    { 1, "Normal", 338, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj4CStates[2] =
  {
    { 1, "Not activated", 342, ObjectStateInfo::none },
    { 2, "Activated", 342, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj4DStates[1] =
  {
    { 1, "Normal", 344, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj4EStates[4] =
  {
    { 1, "Idle", 345, ObjectStateInfo::none },
    { 2, "Being pushed", 345, ObjectStateInfo::none },
    { 3, "Falling", 345, ObjectStateInfo::none },
    { 4, "? Power glove?", 345, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj4FStates[9] =
  {
    { 1, "Up", 347, ObjectStateInfo::none },
    { 2, "Down", 347, ObjectStateInfo::none },
    { 3, "Left", 347, ObjectStateInfo::none },
    { 4, "Right", 347, ObjectStateInfo::none },
    { 5, "?", 347, ObjectStateInfo::none },
    { 6, "?", 347, ObjectStateInfo::none },
    { 7, "Down-right", 347, ObjectStateInfo::none },
    { 8, "Up-right", 347, ObjectStateInfo::none },
    { 9, "Fast up?", 347, ObjectStateInfo::none },
  }; 

const ObjectStateInfo ObjectStates::obj50States[1] =
  {
    { 1, "Normal", 349, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj51States[1] =
  {
    { 1, "Normal", 376, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj52States[1] =
  {
    { 1, "Normal", 378, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj53States[1] =
  {
    { 1, "Normal", 374, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj54States[1] =
  {
    { 1, "Normal", 371, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj55States[0xF] =
  {
    { 1, "At Tails' House (land)", 386, ObjectStateInfo::none },
    { 2, "At Area 1 (Poloy Forest)", 386, ObjectStateInfo::none },
    { 3, "At Area 2 (Caron Forest)", 386, ObjectStateInfo::none },
    { 4, "At Area 3 (Volcanic Tunnel)", 386, ObjectStateInfo::none },
    { 5, "At Area 4 (Polly Mt 1)", 386, ObjectStateInfo::none },
    { 6, "At Area 5 (Polly Mt 2)", 386, ObjectStateInfo::none },
    { 7, "At Area 6 (Lake Rocky)", 383, ObjectStateInfo::none },
    { 8, "At Area 7 (Lake Crystal)", 383, ObjectStateInfo::none },
    { 9, "At Area 8 (Green Island)", 386, ObjectStateInfo::none },
    { 0xA, "At Area 9 (Cavern Island)", 386, ObjectStateInfo::none },
    { 0xB, "At Area 10 (Coco Island)", 386, ObjectStateInfo::none },
    { 0xC, "At Area 11 (Battle Fortress 1)", 386, ObjectStateInfo::none },
    { 0xD, "At Area 12 (Battle Fortress 2)", 386, ObjectStateInfo::none },
    { 0xE, "At Tails' House (water)", 383, ObjectStateInfo::none },
    { 0xF, "Ending", 364, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj56States[0xF] =
  {
    { 1, "At Tails' House (land)", 386, ObjectStateInfo::none },
    { 2, "At Area 1 (Poloy Forest)", 386, ObjectStateInfo::none },
    { 3, "At Area 2 (Caron Forest)", 386, ObjectStateInfo::none },
    { 4, "At Area 3 (Volcanic Tunnel)", 386, ObjectStateInfo::none },
    { 5, "At Area 4 (Polly Mt 1)", 386, ObjectStateInfo::none },
    { 6, "At Area 5 (Polly Mt 2)", 386, ObjectStateInfo::none },
    { 7, "At Area 6 (Lake Rocky)", 383, ObjectStateInfo::none },
    { 8, "At Area 7 (Lake Crystal)", 383, ObjectStateInfo::none },
    { 9, "At Area 8 (Green Island)", 386, ObjectStateInfo::none },
    { 0xA, "At Area 9 (Cavern Island)", 386, ObjectStateInfo::none },
    { 0xB, "At Area 10 (Coco Island)", 386, ObjectStateInfo::none },
    { 0xC, "At Area 11 (Battle Fortress 1)", 386, ObjectStateInfo::none },
    { 0xD, "At Area 12 (Battle Fortress 2)", 386, ObjectStateInfo::none },
    { 0xE, "At Tails' House (water)", 383, ObjectStateInfo::none },
    { 0xF, "Ending", 364, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj57States[4] =
  {
    { 1, "Battle Fortress mode", 366, ObjectStateInfo::none },
    { 2, "Coco Island mode", 367, ObjectStateInfo::none },
    { 3, "Coco Island -> Battle Fortress transformation", 367,
      ObjectStateInfo::none },
    { 4, "Battle Fortress after transformation", 366, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj58States[3] =
  {
    { 1, "Flashing", 363, ObjectStateInfo::none },
    { 2, "Not flashing", 362, ObjectStateInfo::none },
    { 3, "?", 362, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj59States[3] =
  {
    { 1, "Intro battleship", 382, ObjectStateInfo::none },
    { 2, "Intro flames", 369, ObjectStateInfo::none },
    { 3, "? Polly Mt 1 boss escape cutscene?", 380, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj5AStates[3] =
  {
    { 1, "Intro battleship", 382, ObjectStateInfo::none },
    { 2, "Intro flames", 369, ObjectStateInfo::none },
    { 3, "? Polly Mt 1 boss escape cutscene?", 380, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj5BStates[6] =
  {
    { 1, "Idle", 389, ObjectStateInfo::none },
    { 2, "?", 389, ObjectStateInfo::none },
    { 3, "Log?", 389, ObjectStateInfo::none },
    { 4, "Spawn log?", 389, ObjectStateInfo::none },
    { 5, "Log roller?", 387, ObjectStateInfo::none },
    { 6, "Spawn log roller?", 387, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj5CStates[6] =
  {
    { 1, "Idle", 389, ObjectStateInfo::none },
    { 2, "?", 389, ObjectStateInfo::none },
    { 3, "Log?", 389, ObjectStateInfo::none },
    { 4, "Spawn log?", 389, ObjectStateInfo::none },
    { 5, "Log roller?", 387, ObjectStateInfo::none },
    { 6, "Spawn log roller?", 387, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj5DStates[5] =
  {
    { 1, "Idle", 391, ObjectStateInfo::none },
    { 2, "Being pushed", 391, ObjectStateInfo::none },
    { 3, "Falling", 391, ObjectStateInfo::none },
    { 4, "? Power glove?", 391, ObjectStateInfo::none },
    { 5, "Bounced on", 392, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj5EStates[5] =
  {
    { 1, "Vertical, short distance", 393, ObjectStateInfo::none },
    { 2, "Vertical, long distance", 393, ObjectStateInfo::none },
    { 3, "Horizontal, medium distance", 393, ObjectStateInfo::none },
    { 4, "? Go to state 1?", 393, ObjectStateInfo::none },
    { 5, "Horizontal, short distance", 393, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj5FStates[5] =
  {
    { 1, "Vertical, short distance", 393, ObjectStateInfo::none },
    { 2, "Vertical, long distance", 393, ObjectStateInfo::none },
    { 3, "Horizontal, medium distance", 393, ObjectStateInfo::none },
    { 4, "? Go to state 1?", 393, ObjectStateInfo::none },
    { 5, "Horizontal, short distance", 393, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj60States[0x11] =
  {
    { 1, "Initial state?", 394, ObjectStateInfo::none },
    { 2, "Pause after retreating", 394, ObjectStateInfo::none },
    { 3, "Music trigger?", 394, ObjectStateInfo::none },
    { 4, "Walk around", 394, ObjectStateInfo::none },
    { 5, "Turn head and move to back of arena", 394, ObjectStateInfo::none },
    { 6, "Shoot 3 flames", 394, ObjectStateInfo::none },
    { 7, "Flame", 407, ObjectStateInfo::none },
    { 8, "Diagonal down-left flame, steep angle", 407, ObjectStateInfo::none },
    { 9, "Diagonal down-left flame, shallow angle", 407,
      ObjectStateInfo::none },
    { 0xA, "Left flame", 407, ObjectStateInfo::none },
    { 0xB, "Diagonal up-left flame, shallow angle", 407,
      ObjectStateInfo::none },
    { 0xC, "Start crouch attack", 405, ObjectStateInfo::none },
    { 0xD, "Spray flame while crouched", 394, ObjectStateInfo::none },
    { 0xE, "Start jump", 394, ObjectStateInfo::none },
    { 0xF, "In air during jump", 394, ObjectStateInfo::none },
    { 0x10, "Death sequence", 399, ObjectStateInfo::none },
    { 0x11, "Intro cutscene", 394, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj61States[0x15] =
  {
    { 1, "Arm vertex 1?", 418, ObjectStateInfo::none },
    { 2, "Arm vertex 2?", 418, ObjectStateInfo::none },
    { 3, "Claw", 423, ObjectStateInfo::none },
    { 4, "Logic: Main body idle, armored", 410, ObjectStateInfo::none },
    { 5, "?", 410, ObjectStateInfo::none },
    { 6, "Left leg", 420, ObjectStateInfo::none },
    { 7, "Right leg", 419, ObjectStateInfo::none },
    { 8, "?", 410, ObjectStateInfo::none },
    { 9, "Logic: Move left, armored", 410, ObjectStateInfo::none },
    { 0xA, "Logic: Move right, armored", 410, ObjectStateInfo::none },
    { 0xB, "?", 410, ObjectStateInfo::none },
    { 0xC, "Logic: Arm swipe, armored", 410, ObjectStateInfo::none },
    { 0xD, "Logic: Arm sweep, unarmored", 414, ObjectStateInfo::none },
    { 0xE, "Logic: Bomb drop, unarmored", 414, ObjectStateInfo::none },
    { 0xF, "Logic: Armor destruction sequence", 415, ObjectStateInfo::none },
    { 0x10, "Logic: Main body idle, unarmored", 414, ObjectStateInfo::none },
    { 0x11, "Logic: Move left, unarmored", 414, ObjectStateInfo::none },
    { 0x12, "Logic: Move right, unarmored", 414, ObjectStateInfo::none },
    { 0x13, "Logic: Arm jab, unarmored", 414, ObjectStateInfo::none },
    { 0x14, "Duck bomb?", 421, ObjectStateInfo::none },
    { 0x15, "Logic: death sequence", 415, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj62States[0x1B] =
  {
    { 1, "?", 425, ObjectStateInfo::none },
    { 2, "?", 425, ObjectStateInfo::none },
    { 3, "Head", 425, ObjectStateInfo::none },
    { 4, "Exploding head", 425, ObjectStateInfo::none },
    { 5, "Logic: Idle, armored", 425, ObjectStateInfo::none },
    { 6, "?", 425, ObjectStateInfo::none },
    { 7, "Logic: Bullet spray, armored", 425, ObjectStateInfo::none },
    { 8, "Bullet 1", 436, ObjectStateInfo::none },
    { 9, "Bullet 2", 436, ObjectStateInfo::none },
    { 0xA, "Bullet 3", 436, ObjectStateInfo::none },
    { 0xB, "Bullet 4", 436, ObjectStateInfo::none },
    { 0xC, "Bullet 5?", 436, ObjectStateInfo::none },
    { 0xD, "Logic: Switch to unarmored?", 429, ObjectStateInfo::none },
    { 0xE, "? Go to state 0x13?", 429, ObjectStateInfo::none },
    { 0xF, "? Go to state 0x13?", 429, ObjectStateInfo::none },
    { 0x10, "Homing bullet", 435, ObjectStateInfo::none },
    { 0x11, "Bullet smoke puff", 433, ObjectStateInfo::none },
    { 0x12, "Death sequence", 430, ObjectStateInfo::none },
    { 0x13, "Logic: Backward bullet spray, unarmored", 429,
      ObjectStateInfo::none },
    { 0x14, "Backward bullet 1", 436, ObjectStateInfo::none },
    { 0x15, "Backward bullet 2", 436, ObjectStateInfo::none },
    { 0x16, "Backward bullet 3", 436, ObjectStateInfo::none },
    { 0x17, "Backward bullet 4", 436, ObjectStateInfo::none },
    { 0x18, "Forward bullet 1", 436, ObjectStateInfo::none },
    { 0x19, "Forward bullet 2", 436, ObjectStateInfo::none },
    { 0x1A, "Forward bullet 3", 436, ObjectStateInfo::none },
    { 0x1B, "Forward bullet 4", 436, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj63States[0xB] =
  {
    { 1, "Spawn?", 440, ObjectStateInfo::none },
    { 2, "Logic: Idle", 440, ObjectStateInfo::none },
    { 3, "Death sequence", 440, ObjectStateInfo::none },
    { 4, "Control tower duck head?", 442, ObjectStateInfo::none },
    { 5, "Thrower duck logic?", 440, ObjectStateInfo::none },
    { 6, "Control tower head facing backward?", 439, ObjectStateInfo::none },
    { 7, "Thrower duck logic?", 440, ObjectStateInfo::none },
    { 8, "Thrower duck logic?", 440, ObjectStateInfo::none },
    { 9, "Thrower duck logic?", 440, ObjectStateInfo::none },
    { 0xA, "Control tower duck logic?", 442, ObjectStateInfo::none },
    { 0xB, "Control tower duck logic?", 442, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj64States[3] =
  {
    { 1, "Logic: Boss duck activates trapdoor", 452, ObjectStateInfo::none },
    { 2, "Logic: Boss duck idles", 444, ObjectStateInfo::none },
    { 3, "Death sequence", 447, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj65States[8] =
  {
    { 1, "Intro", 460, ObjectStateInfo::none },
    { 2, "Idle while waiting for battle start", 457, ObjectStateInfo::none },
    { 3, "Pause while turning at top?", 456, ObjectStateInfo::none },
    { 4, "Swoop upward for taunt and dive", 459, ObjectStateInfo::none },
    { 5, "Pause while turning at bottom?", 455, ObjectStateInfo::none },
    { 6, "Dive", 455, ObjectStateInfo::none },
    { 7, "Taunt", 460, ObjectStateInfo::none },
    { 8, "Battle finished sequence", 457, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj66States[0xF] =
  {
    { 1, "Intro", 471, ObjectStateInfo::none },
    { 2, "Intro takeoff", 474, ObjectStateInfo::none },
    { 3, "Fly around 1", 475, ObjectStateInfo::none },
    { 4, "Fly around 2", 475, ObjectStateInfo::none },
    { 5, "Fly around 3", 475, ObjectStateInfo::none },
    { 6, "Fly around 4", 475, ObjectStateInfo::none },
    { 7, "Start flame attack 1", 476, ObjectStateInfo::none },
    { 8, "Start flame attack 2", 476, ObjectStateInfo::none },
    { 9, "Start energy ball attack?", 476, ObjectStateInfo::none },
    { 0xA, "Energy ball attack", 476, ObjectStateInfo::none },
    { 0xB, "?", 470, ObjectStateInfo::none },
    { 0xC, "Energy ball", 470, ObjectStateInfo::none },
    { 0xD, "Flame", 467, ObjectStateInfo::none },
    { 0xE, "Fireball", 465, ObjectStateInfo::none },
    { 0xF, "Death sequence", 464, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj67States[0xC] =
  {
    { 1, "Waiting for battle to start", 477, ObjectStateInfo::none },
    { 2, "Start loading graphics and do intro", 483, ObjectStateInfo::none },
    { 3, "Walk and attack, phase 1", 479, ObjectStateInfo::none },
    { 4, "Tails grab attack 1", 481, ObjectStateInfo::none },
    { 5, "?", 481, ObjectStateInfo::none },
    { 6, "Grab attack hand 1?", 485, ObjectStateInfo::none },
    { 7, "Duck and shoot bombs horizontally", 488, ObjectStateInfo::none },
    { 8, "Walk and attack, phase 2", 479, ObjectStateInfo::none },
    { 9, "Tails grab attack 2", 481, ObjectStateInfo::none },
    { 0xA, "Grab attack hand 2?", 485, ObjectStateInfo::none },
    { 0xB, "Duck and throw bombs upward", 488, ObjectStateInfo::none },
    { 0xC, "Death and ending sequence", 489, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj68States[3] =
  {
    { 1, "Intro back-and-forth flight", 492, ObjectStateInfo::none },
    { 2, "Intro tree flight", 491, ObjectStateInfo::none },
    { 3, "Credits", 494, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj69States[3] =
  {
    { 1, "Intro back-and-forth flight", 492, ObjectStateInfo::none },
    { 2, "Intro tree flight", 491, ObjectStateInfo::none },
    { 3, "Credits", 494, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj6AStates[7] =
  {
    { 1, "Small", 497, ObjectStateInfo::none },
    { 2, "Small explosion", 497, ObjectStateInfo::none },
    { 3, "Medium", 498, ObjectStateInfo::none },
    { 4, "Large", 499, ObjectStateInfo::none },
    { 5, "Large explosion", 499, ObjectStateInfo::none },
    { 6, "Complete", 500, ObjectStateInfo::none },
    { 7, "Complete explosion", 501, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj6BStates[7] =
  {
    { 1, "Small", 497, ObjectStateInfo::none },
    { 2, "Small explosion", 497, ObjectStateInfo::none },
    { 3, "Medium", 498, ObjectStateInfo::none },
    { 4, "Large", 499, ObjectStateInfo::none },
    { 5, "Large explosion", 499, ObjectStateInfo::none },
    { 6, "Complete", 500, ObjectStateInfo::none },
    { 7, "Complete explosion", 501, ObjectStateInfo::none }
  }; 

const ObjectStateInfo ObjectStates::obj6CStates[4] =
  {
    { 1, "Spawn?", 438, ObjectStateInfo::none },
    { 2, "Preparing for throw?", 438, ObjectStateInfo::none },
    { 3, "Out of water", 438, ObjectStateInfo::none },
    { 4, "In water", 438, ObjectStateInfo::none }
  }; 



};
