#ifndef PNGCONVERSION_H
#define PNGCONVERSION_H


#include "structs/TwoDByteArray.h"
#include "gamegear/GGPalette.h"
#include <string>

#ifdef TALES_ENABLE_LIBPNG
  #include "png.h"
#endif

namespace Tales {


class PngConversion {
public:
  static bool canConvertPng();
  
  static bool twoDArrayToIndexedPngGG(const std::string& filename,
                                      TwoDByteArray& src,
                                      GGPalette palette,
                                      bool transparency = true);
  
  static bool indexedPngToTwoDArrayGG(TwoDByteArray& dst,
                                    const std::string& filename);
protected:

#ifdef TALES_ENABLE_LIBPNG
  const static int pngBytesToCheck_ = 4;
  
  const static int pngBitDepth_ = 8;

  static bool pngralloc(png_structp& png_ptr,
                       png_infop& info_ptr,
                       const std::string& filename);
                       
  static bool pngrfree(png_structp& png_ptr,
                      png_infop& info_ptr);

  static bool pngwalloc(png_structp& png_ptr,
                       png_infop& info_ptr);

  static bool pngwfree(png_structp& png_ptr,
                       png_infop& info_ptr);

  static bool pngwrite(png_structp& png_ptr,
                       png_infop& info_ptr,
                       const std::string& filename);
#endif


};


};


#endif
