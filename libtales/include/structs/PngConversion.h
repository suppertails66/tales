#ifndef PNGCONVERSION_H
#define PNGCONVERSION_H


#include "structs/TwoDByteArray.h"
#include <string>

#ifdef TALES_ENABLE_LIBPNG
  #include "png.h"
#endif

namespace Tales {


class PngConversion {
public:
  static bool canConvertPng();
  
  static bool twoDArrayToIndexedPngGG(const std::string& filename,
                                      TwoDByteArray& dst);
  
  static bool indexedPngToTwoDArrayGG(TwoDByteArray& dst,
                                    const std::string& filename);
protected:

#ifdef TALES_ENABLE_LIBPNG
  const static int pngBytesToCheck_ = 4;

  static bool pngalloc(png_structp& png_ptr,
                       png_infop& info_ptr,
                       const std::string& filename);
                       
  static bool pngfree(png_structp& png_ptr,
                      png_infop& info_ptr);
#endif


};


};


#endif
