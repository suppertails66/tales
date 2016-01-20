#ifndef MAPPINGTOGRAPHICENTRY_H
#define MAPPINGTOGRAPHICENTRY_H


#include "structs/GraphicIdentifier.h"

namespace Tales {


class MappingToGraphicEntry {
public:
  /**
   * Default constructor.
   */
  MappingToGraphicEntry();
  
  /**
   * Constructor from known values.
   * @param mappingIndex Mapping index.
   * @param graphicType Indicates graphic type (compressed or uncompressed).
   * @param graphicIndex Index of the graphic within its respective type.
   * @param offset Offset in tiles of the mapping from the start of the
   * graphic. 1 means that a 1 should be added to all tile indices in the
   * mapping, -1 means -1 should be added, etc.
   */
  MappingToGraphicEntry(int mappingIndex__,
                        GraphicIdentifier::GraphicType graphicType__,
                        int graphicIndex__,
                        int tileOffset__);
                     
  /**
   * Getter.
   */
  int mappingIndex() const;
                     
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
  int tileOffset() const;
  
protected:

  int mappingIndex_;
  
  GraphicIdentifier::GraphicType graphicType_;
  
  int graphicIndex_;
  
  int tileOffset_;

  
  
};


};


#endif
