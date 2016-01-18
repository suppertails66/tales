#include "gamedata/MappingToGraphicEntry.h"

namespace Tales {


MappingToGraphicEntry::MappingToGraphicEntry()
  : mappingIndex_(0),
    graphicType_(GraphicIdentifier::uncompressed),
    graphicIndex_(0),
    tileOffset_(0) { };

MappingToGraphicEntry::MappingToGraphicEntry(
                      int mappingIndex__,
                      GraphicIdentifier::GraphicType graphicType__,
                      int graphicIndex__,
                      int tileOffset__)
  : mappingIndex_(mappingIndex__),
    graphicType_(graphicType__),
    graphicIndex_(graphicIndex__),
    tileOffset_(tileOffset__) { };

int MappingToGraphicEntry::mappingIndex() const {
  return mappingIndex_;
}

GraphicIdentifier::GraphicType MappingToGraphicEntry::graphicType() const {
  return graphicType_;
}

int MappingToGraphicEntry::graphicIndex() const {
  return graphicIndex_;
}

int MappingToGraphicEntry::tileOffset() const {
  return tileOffset_;
}


};
