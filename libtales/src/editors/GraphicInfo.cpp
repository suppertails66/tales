#include "editors/GraphicInfo.h"

namespace Tales {


GraphicInfo::GraphicInfo()
  : graphicCategory_(GraphicCategories::enemy) { };

GraphicInfo::GraphicInfo(
            std::string name__,
            GraphicCategories::GraphicCategory graphicCategory__)
  : name_(name__),
    graphicCategory_(graphicCategory__) { };
            
const std::string& GraphicInfo::name() const {
  return name_;
}

GraphicCategories::GraphicCategory GraphicInfo::graphicCategory() const {
  return graphicCategory_;
}


}; 
