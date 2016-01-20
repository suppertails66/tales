#ifndef OBJECTSTATES_H
#define OBJECTSTATES_H


#include "gamedata/ObjectStateInfo.h"
#include "gamedata/ObjectTypeID.h"

namespace Tales {


class ObjectStates {
public:
  enum ObjectSpawnParameterType {
    spawnParameterStandard,
    spawnParameterWarp,
    spawnParameterManual,
    spawnParameterMissileLauncher,
    spawnParameterEnemyMine
  };

  static int numObjects();

  static int numStatesPerObject(int objectNum);
  
  static ObjectSpawnParameterType objectSpawnParameterType(int objectNum);
  
  static ObjectStateInfo objectStateInfo(int objectNum, int stateIndex);
  
  static ObjectStateInfo findObjectStateInfo(int objectNum, int stateNum);
  
  static const ObjectStateInfo* objectStates(int objectNum);
  
protected:
  const static int numObjects_ = 0x6D;
  
  const static int numStatesPerObject_[numObjects_];
  
  const static ObjectStateInfo obj03States[1];
  const static ObjectStateInfo obj04States[4];
  const static ObjectStateInfo obj05States[3];
  const static ObjectStateInfo obj06States[2];
  const static ObjectStateInfo obj07States[2];
  const static ObjectStateInfo obj08States[1];
  const static ObjectStateInfo obj09States[1];
  const static ObjectStateInfo obj0AStates[2];
  const static ObjectStateInfo obj0BStates[7];
  const static ObjectStateInfo obj0CStates[4];
  const static ObjectStateInfo obj0DStates[0xF];
  const static ObjectStateInfo obj0EStates[0xF];
  const static ObjectStateInfo obj0FStates[0xF];
  const static ObjectStateInfo obj10States[2];
  const static ObjectStateInfo obj11States[2];
  const static ObjectStateInfo obj12States[3];
  const static ObjectStateInfo obj13States[2];
  const static ObjectStateInfo obj14States[2];
  const static ObjectStateInfo obj15States[2];
  const static ObjectStateInfo obj16States[2];
  const static ObjectStateInfo obj17States[2];
  const static ObjectStateInfo obj18States[2];
  const static ObjectStateInfo obj19States[2];
  const static ObjectStateInfo obj1AStates[2];
  const static ObjectStateInfo obj1BStates[4];
  const static ObjectStateInfo obj1CStates[4];
  const static ObjectStateInfo obj1DStates[4];
  const static ObjectStateInfo obj1EStates[4];
  const static ObjectStateInfo obj1FStates[4];
  const static ObjectStateInfo obj20States[4];
  const static ObjectStateInfo obj21States[4];
  const static ObjectStateInfo obj22States[4];
  const static ObjectStateInfo obj23States[3];
  const static ObjectStateInfo obj24States[4];
  const static ObjectStateInfo obj25States[4];
  const static ObjectStateInfo obj26States[4];
  const static ObjectStateInfo obj27States[2];
  const static ObjectStateInfo obj28States[2];
  const static ObjectStateInfo obj29States[7];
  const static ObjectStateInfo obj2AStates[7];
  const static ObjectStateInfo obj2BStates[7];
  const static ObjectStateInfo obj2CStates[7];
  const static ObjectStateInfo obj2DStates[7];
  const static ObjectStateInfo obj2EStates[7];
  const static ObjectStateInfo obj2FStates[0x20];
  const static ObjectStateInfo obj30States[7];
  const static ObjectStateInfo obj31States[0xD];
  const static ObjectStateInfo obj32States[1];
  const static ObjectStateInfo obj33States[8];
  const static ObjectStateInfo obj34States[7];
  const static ObjectStateInfo obj35States[7];
  const static ObjectStateInfo obj36States[6];
  const static ObjectStateInfo obj37States[3];
  const static ObjectStateInfo obj38States[4];
  const static ObjectStateInfo obj39States[5];
  const static ObjectStateInfo obj3AStates[4];
  const static ObjectStateInfo obj3BStates[6];
  const static ObjectStateInfo obj3CStates[4];
  const static ObjectStateInfo obj3DStates[5];
  const static ObjectStateInfo obj3EStates[9];
  const static ObjectStateInfo obj3FStates[0xB];
  const static ObjectStateInfo obj40States[4];
  const static ObjectStateInfo obj41States[3];
  const static ObjectStateInfo obj42States[4];
  const static ObjectStateInfo obj43States[2];
  const static ObjectStateInfo obj44States[5];
  const static ObjectStateInfo obj45States[4];
  const static ObjectStateInfo obj46States[3];
  const static ObjectStateInfo obj47States[8];
  const static ObjectStateInfo obj48States[3];
  const static ObjectStateInfo obj49States[3];
  const static ObjectStateInfo obj4AStates[3];
  const static ObjectStateInfo obj4BStates[1];
  const static ObjectStateInfo obj4CStates[2];
  const static ObjectStateInfo obj4DStates[1];
  const static ObjectStateInfo obj4EStates[4];
  const static ObjectStateInfo obj4FStates[9];
  const static ObjectStateInfo obj50States[1];
  const static ObjectStateInfo obj51States[1];
  const static ObjectStateInfo obj52States[1];
  const static ObjectStateInfo obj53States[1];
  const static ObjectStateInfo obj54States[1];
  const static ObjectStateInfo obj55States[0xF];
  const static ObjectStateInfo obj56States[0xF];
  const static ObjectStateInfo obj57States[4];
  const static ObjectStateInfo obj58States[3];
  const static ObjectStateInfo obj59States[3];
  const static ObjectStateInfo obj5AStates[3];
  const static ObjectStateInfo obj5BStates[6];
  const static ObjectStateInfo obj5CStates[6];
  const static ObjectStateInfo obj5DStates[5];
  const static ObjectStateInfo obj5EStates[5];
  const static ObjectStateInfo obj5FStates[5];
  const static ObjectStateInfo obj60States[0x11];
  const static ObjectStateInfo obj61States[0x15];
  const static ObjectStateInfo obj62States[0x1B];
  const static ObjectStateInfo obj63States[0xB];
  const static ObjectStateInfo obj64States[3];
  const static ObjectStateInfo obj65States[8];
  const static ObjectStateInfo obj66States[0xF];
  const static ObjectStateInfo obj67States[0xC];
  const static ObjectStateInfo obj68States[3];
  const static ObjectStateInfo obj69States[3];
  const static ObjectStateInfo obj6AStates[7];
  const static ObjectStateInfo obj6BStates[7];
  const static ObjectStateInfo obj6CStates[4];
  
};


};


#endif
