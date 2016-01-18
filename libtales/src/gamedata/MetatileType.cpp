#include "gamedata/MetatileBehavior.h"

namespace Tales {


std::string MetatileTypes
    ::nameOfType(MetatileTypes::MetatileType metatileType) {
  switch (metatileType) {
  case nullType:
    return "Null tile";
    break;
  case climbable1:
    return "Climbable 1";
    break;
  case climbable2:
    return "Climbable 2";
    break;
  case nonclimbable:
    return "Nonclimbable";
    break;
  case damaging:
    return "Damaging";
    break;
  case instadeath:
    return "Instadeath";
    break;
  case water:
    return "Water";
    break;
  case gust:
    return "Wind gust";
    break;
  case conveyorLeft:
    return "Always-left conveyor";
    break;
  case crumbling:
    return "Conveyor reverser";
    break;
  case crumblingStart:
    return "Crumbling";
    break;
  case bombable:
    return "Destructible";
    break;
  case conveyorRight:
    return "Standard conveyor";
    break;
  case typeD:
    return "Type 0x0D";
    break;
  case napalm:
    return "Destructible with napalm";
    break;
  case downOnly:
    return "One-way down tile";
    break;
  case type10:
    return "Type 0x10";
    break;
  case bigGust:
    return "Big upward gust";
    break;
  case type12:
    return "Type 0x12";
    break;
  default:
    return "***ERROR TYPE***";
    break;
  }
}


}; 
