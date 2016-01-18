#ifndef OBJECTGRAPHICMAPPING_H
#define OBJECTGRAPHICMAPPING_H


#include "structs/GraphicIdentifier.h"
#include "gamedata/ObjectTypeID.h"

namespace Tales {


class ObjectGraphicMapping {
public:
  enum MappingValidity {
    mappingInvalid,
    mappingValid
  };

  /**
   * Default constructor.
   */
  ObjectGraphicMapping();
  
  /**
   * Constructor from known values.
   */
  ObjectGraphicMapping(ObjectTypeIDs::ObjectTypeID objectTypeID__,
                       MappingValidity validity__,
                       GraphicIdentifier::GraphicType graphicType__,
                       int graphicIndex__,
                       int numSpritestates__);
                       
  /**
   * Getter.
   */
  ObjectTypeIDs::ObjectTypeID objectTypeID() const;
                     
  /**
   * Getter.
   */
  MappingValidity validity() const;
                       
  /**
   * Getter.
   */
  GraphicIdentifier::GraphicType graphicType() const;
                       
  /**
   * Getter.
   */
  int graphicIndex() const;
                       
  /**
   * Getter.
   */
  int numSpritestates() const;
  
protected:

  ObjectTypeIDs::ObjectTypeID objectTypeID_;

  MappingValidity validity_;
  
  GraphicIdentifier::GraphicType graphicType_;
  
  int graphicIndex_;
  
  int numSpritestates_;
  
};


};


#endif
