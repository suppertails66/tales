#ifndef GRAPHICTOINFO_H
#define GRAPHICTOINFO_H


#include "editors/GraphicInfo.h"
#include <string>

namespace Tales {


class GraphicToInfo {
public:
  const static int numCompressedGraphicInfos = 81;
  
  const static int numUncompressedGraphicInfos = 299;
  
  static GraphicInfo compressedGraphicInfo(int index);
  
  static std::string nameOfCompressedGraphic(int index);
  
  static GraphicCategories::GraphicCategory
      categoryOfCompressedGraphic(int index);
  
  static GraphicInfo uncompressedGraphicInfo(int index);
  
  static std::string nameOfUncompressedGraphic(int index);
  
  static GraphicCategories::GraphicCategory
      categoryOfUncompressedGraphic(int index);
protected:

  const static GraphicInfo compressedGraphicInfos[];

  const static GraphicInfo uncompressedGraphicInfos[];
};


};


#endif
