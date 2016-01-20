#ifndef OBJECTSTATEINFO_H
#define OBJECTSTATEINFO_H


namespace Tales {


struct ObjectStateInfo {
  enum FacingDirection {
    none,
    left,
    right
  };

  const int stateNum;
  const char* stateName;
  const int previewMappingIndex;
  const FacingDirection facingDirection;
};


};


#endif
