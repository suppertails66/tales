#include "editors/ObjectToGraphics.h"

namespace Tales {


ObjectGraphicInfo ObjectToGraphics::objectToGraphics(
    ObjectTypeIDs::ObjectTypeID objectTypeID) {
  return objectToGraphics_[objectTypeID];
}
  
const ObjectGraphicInfo
  ObjectToGraphics::objectToGraphics_[ObjectTypeIDs::objectTypeIDLimit] =
  {
    // 0x00
    { GraphicCompressionTypes::uncompressed, 0, 0, 0 },
    { GraphicCompressionTypes::uncompressed, 0, 0, 0 },
    { GraphicCompressionTypes::uncompressed, 0, 0, 0 },
    { GraphicCompressionTypes::uncompressed, 0, 0, 0 },
    { GraphicCompressionTypes::uncompressed, 0, 0, 0 },
    { GraphicCompressionTypes::compressed, 0, 0, -18 },
    { GraphicCompressionTypes::compressed, 0, 0, -18 },
    { GraphicCompressionTypes::compressed, 59, 59, 0 },
    { GraphicCompressionTypes::compressed, 0, 0, 68 },
    { GraphicCompressionTypes::compressed, 26, 26, 0 },
    // 0x0A
    { GraphicCompressionTypes::compressed, 36, 36, 0 },
    { GraphicCompressionTypes::compressed, 0, 0, 0 },
    { GraphicCompressionTypes::compressed, 55, 55, 0 },
    { GraphicCompressionTypes::compressed, 0, 0, 20 },
    { GraphicCompressionTypes::compressed, 0, 0, 20 },
    { GraphicCompressionTypes::compressed, 0, 0, 20 },
    // 0x10
    { GraphicCompressionTypes::uncompressed, 0, 0, 0 },
    { GraphicCompressionTypes::uncompressed, 0, 0, 0 },
    { GraphicCompressionTypes::uncompressed, 0, 0, 0 },
    { GraphicCompressionTypes::uncompressed, 0, 0, 0 },
    { GraphicCompressionTypes::uncompressed, 0, 0, 0 },
    { GraphicCompressionTypes::uncompressed, 0, 0, 0 },
    { GraphicCompressionTypes::uncompressed, 0, 0, 0 },
    { GraphicCompressionTypes::uncompressed, 0, 0, 0 },
    { GraphicCompressionTypes::uncompressed, 0, 0, 0 },
    { GraphicCompressionTypes::uncompressed, 0, 0, 0 },
    // 0x1A
    { GraphicCompressionTypes::uncompressed, 0, 0, 0 },
    { GraphicCompressionTypes::uncompressed, 0, 0, 0 },
    { GraphicCompressionTypes::uncompressed, 0, 0, 0 },
    { GraphicCompressionTypes::uncompressed, 0, 0, 0 },
    { GraphicCompressionTypes::uncompressed, 0, 0, 0 },
    { GraphicCompressionTypes::uncompressed, 0, 0, 0 },
    // 0x20
    { GraphicCompressionTypes::uncompressed, 0, 0, 0 },
    { GraphicCompressionTypes::uncompressed, 0, 0, 0 },
    { GraphicCompressionTypes::uncompressed, 0, 0, 0 },
    { GraphicCompressionTypes::uncompressed, 0, 0, 0 },
    { GraphicCompressionTypes::uncompressed, 0, 0, 0 },
    { GraphicCompressionTypes::uncompressed, 0, 0, 0 },
    { GraphicCompressionTypes::uncompressed, 0, 0, 0 },
    { GraphicCompressionTypes::uncompressed, 0, 0, 0 },
    { GraphicCompressionTypes::uncompressed, 0, 0, 0 },
    { GraphicCompressionTypes::uncompressed, 0, 0, 0 },
    // 0x2A
    { GraphicCompressionTypes::uncompressed, 0, 0, 0 },
    { GraphicCompressionTypes::uncompressed, 0, 0, 0 },
    { GraphicCompressionTypes::uncompressed, 0, 0, 0 },
    { GraphicCompressionTypes::uncompressed, 0, 0, 0 },
    { GraphicCompressionTypes::uncompressed, 0, 0, 0 },
    { GraphicCompressionTypes::uncompressed, 0, 0, 0 },
    // 0x30
    { GraphicCompressionTypes::compressed, 3, 3, 0 },
    { GraphicCompressionTypes::compressed, 4, 4, 0 },
    { GraphicCompressionTypes::compressed, 37, 37, 0 },
    { GraphicCompressionTypes::compressed, 5, 5, 0 },
    { GraphicCompressionTypes::compressed, 6, 6, 0 },
    { GraphicCompressionTypes::compressed, 6, 6, 0 },
    { GraphicCompressionTypes::compressed, 7, 7, 0 },
    { GraphicCompressionTypes::compressed, 8, 8, 0 },
    { GraphicCompressionTypes::compressed, 11, 11, 0 },
    { GraphicCompressionTypes::compressed, 12, 12, 0 },
    // 0x3A
    { GraphicCompressionTypes::compressed, 31, 31, 0 },
    { GraphicCompressionTypes::compressed, 21, 21, 0 },
    { GraphicCompressionTypes::compressed, 13, 13, 0 },
    { GraphicCompressionTypes::compressed, 14, 14, 0 },
    { GraphicCompressionTypes::compressed, 15, 15, 0 },
    { GraphicCompressionTypes::compressed, 39, 40, 0 },
    // 0x40
    { GraphicCompressionTypes::compressed, 16, 16, 0 },
    { GraphicCompressionTypes::compressed, 17, 17, 0 },
    { GraphicCompressionTypes::compressed, 18, 18, 0 },
    { GraphicCompressionTypes::compressed, 19, 19, 0 },
    { GraphicCompressionTypes::compressed, 24, 24, 0 },
    { GraphicCompressionTypes::compressed, 20, 20, 0 },
    { GraphicCompressionTypes::compressed, 25, 25, 0 },
    { GraphicCompressionTypes::compressed, 32, 32, 0 },
    { GraphicCompressionTypes::compressed, 23, 23, 0 },
    { GraphicCompressionTypes::compressed, 27, 27, 0 },
    // 0x4A
    { GraphicCompressionTypes::compressed, 28, 28, 0 },
    { GraphicCompressionTypes::compressed, 29, 29, 0 },
    { GraphicCompressionTypes::compressed, 30, 30, 0 },
    { GraphicCompressionTypes::compressed, 35, 35, 0 },
    { GraphicCompressionTypes::compressed, 22, 22, 0 },
    { GraphicCompressionTypes::compressed, 9, 9, 0 },
    // 0x50
    { GraphicCompressionTypes::uncompressed, 0, 0, 0 },
    { GraphicCompressionTypes::uncompressed, 0, 0, 0 },
    { GraphicCompressionTypes::uncompressed, 0, 0, 0 },
    { GraphicCompressionTypes::uncompressed, 0, 0, 0 },
    { GraphicCompressionTypes::uncompressed, 0, 0, 0 },
    { GraphicCompressionTypes::uncompressed, 0, 0, 0 },
    { GraphicCompressionTypes::uncompressed, 0, 0, 0 },
    { GraphicCompressionTypes::uncompressed, 0, 0, 0 },
    { GraphicCompressionTypes::uncompressed, 0, 0, 0 },
    { GraphicCompressionTypes::uncompressed, 0, 0, 0 },
    // 0x5A
    { GraphicCompressionTypes::uncompressed, 0, 0, 0 },
    { GraphicCompressionTypes::uncompressed, 0, 0, 0 },
    { GraphicCompressionTypes::compressed, 38, 38, 0 },
    { GraphicCompressionTypes::compressed, 10, 10, 0 },
    { GraphicCompressionTypes::compressed, 41, 41, 0 },
    { GraphicCompressionTypes::compressed, 41, 41, 0 },
    // 0x60
    { GraphicCompressionTypes::compressed, 42, 42, 0 },
    { GraphicCompressionTypes::compressed, 51, 51, 0 },
    { GraphicCompressionTypes::compressed, 51, 51, 0 },
    { GraphicCompressionTypes::compressed, 53, 53, 0 },
    { GraphicCompressionTypes::compressed, 43, 43, 0 },
    { GraphicCompressionTypes::compressed, 44, 44, 0 },
    { GraphicCompressionTypes::compressed, 54, 54, 0 },
    { GraphicCompressionTypes::uncompressed, 0, 0, 0 },
    { GraphicCompressionTypes::uncompressed, 0, 0, 0 },
    { GraphicCompressionTypes::compressed, 47, 47, 0 },
    // 0x6A
    { GraphicCompressionTypes::compressed, 47, 47, 0 },
    { GraphicCompressionTypes::compressed, 49, 49, 0 },
    { GraphicCompressionTypes::compressed, 53, 53, 0 }
  };


};
