#ifndef OBJECTGRAPHICINFO_H
#define OBJECTGRAPHICINFO_H


#include "editors/GraphicCompressionType.h"

namespace Tales {


struct ObjectGraphicInfo {
  GraphicCompressionTypes::GraphicCompressionType graphicCompressionType;
  int leftGraphicID;
  int rightGraphicID;
  int offset;
};


};


#endif
