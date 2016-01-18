#ifndef OBJECTTOGRAPHICS_H
#define OBJECTTOGRAPHICS_H


#include "gamedata/ObjectTypeID.h"
#include "editors/ObjectGraphicInfo.h"

namespace Tales {


class ObjectToGraphics {
public:
  static ObjectGraphicInfo objectToGraphics(
    ObjectTypeIDs::ObjectTypeID objectTypeID);
protected:
  const static ObjectGraphicInfo
    objectToGraphics_[ObjectTypeIDs::objectTypeIDLimit];
};


};


#endif
