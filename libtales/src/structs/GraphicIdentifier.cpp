#include "structs/GraphicIdentifier.h"

namespace Tales {


GraphicIdentifier::GraphicIdentifier()
  : graphicType_(uncompressed),
    graphicIndex_(0) { };

GraphicIdentifier::GraphicIdentifier(
                  GraphicType graphicType__,
                  int graphicIndex__)
  : graphicType_(graphicType__),
    graphicIndex_(graphicIndex__) { };

GraphicIdentifier::GraphicType GraphicIdentifier::graphicType() const {
  return graphicType_;
}

int GraphicIdentifier::graphicIndex() const {
  return graphicIndex_;
}

void GraphicIdentifier::setGraphicType(GraphicType graphicType__) {
  graphicType_ = graphicType__;
}

void GraphicIdentifier::setGraphicIndex(int graphicIndex__) {
  graphicIndex_ = graphicIndex__;
}


};
