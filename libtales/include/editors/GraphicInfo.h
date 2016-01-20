#ifndef GRAPHICINFO_H
#define GRAPHICINFO_H


#include "editors/GraphicCategory.h"
#include <string>

namespace Tales {


/**
 * Container for information about a graphic.
 */
class GraphicInfo {
public:
  /**
   * Default constructor.
   */
  GraphicInfo();
  
  /**
   * Constructor from data.
   */
  GraphicInfo(std::string name__,
              GraphicCategories::GraphicCategory graphicCategory__);
              
  const std::string& name() const;
  
  GraphicCategories::GraphicCategory graphicCategory() const;
protected:
  
  std::string name_;
  
  GraphicCategories::GraphicCategory graphicCategory_;
  
};


};


#endif
