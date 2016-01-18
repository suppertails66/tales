#include "gamedata/ObjectGraphicMapping.h"

namespace Tales {


ObjectGraphicMapping::ObjectGraphicMapping()
  : objectTypeID_(ObjectTypeIDs::null),
    validity_(mappingInvalid),
    graphicType_(GraphicIdentifier::uncompressed),
    graphicIndex_(0),
    numSpritestates_(0) { };

ObjectGraphicMapping::ObjectGraphicMapping(
                     ObjectTypeIDs::ObjectTypeID objectTypeID__,
                     MappingValidity validity__,
                     GraphicIdentifier::GraphicType graphicType__,
                     int graphicIndex__,
                     int numSpritestates__)
  : objectTypeID_(objectTypeID__),
    validity_(validity__),
    graphicType_(graphicType__),
    graphicIndex_(graphicIndex__),
    numSpritestates_(numSpritestates__) { };
    
ObjectTypeIDs::ObjectTypeID ObjectGraphicMapping::objectTypeID() const {
  return objectTypeID_;
}

ObjectGraphicMapping::MappingValidity ObjectGraphicMapping::validity() const {
  return validity_;
}

GraphicIdentifier::GraphicType ObjectGraphicMapping::graphicType() const {
  return graphicType_;
}

int ObjectGraphicMapping::graphicIndex() const {
  return graphicIndex_;
}

int ObjectGraphicMapping::numSpritestates() const {
  return numSpritestates_;
}


};
