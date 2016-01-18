#include "structs/LevelWidth.h"
#include "exception/TGenericException.h"
#include "util/StringConversion.h"
#include <string>

using namespace Luncheon;

namespace Tales {


int LevelWidths::widthToInt(LevelWidths::LevelWidth width) {
  
  switch (width) {
  case width16:
    return 16;
    break;
  case width32:
    return 32;
    break;
  case width48:
    return 48;
    break;
  case width64:
    return 64;
    break;
  case width80:
    return 80;
    break;
  case width96:
    return 96;
    break;
  case width128:
    return 128;
    break;
  case width256:
    return 256;
    break;
  default:
    throw TGenericException(TALES_SRCANDLINE,
                           "LevelWidths::widthToInt("
                           "LevelWidth)",
                           std::string("Invalid width enum value: ")
                            + StringConversion::toString((int)(width)));
    break;
  }
  
  return 0;
}

LevelWidths::LevelWidth LevelWidths::intToWidth(int width) {
  switch (width) {
  case 16:
    return width16;
    break;
  case 32:
    return width32;
    break;
  case 48:
    return width48;
    break;
  case 64:
    return width64;
    break;
  case 80:
    return width80;
    break;
  case 96:
    return width96;
    break;
  case 128:
    return width128;
    break;
  case 256:
    return width256;
    break;
  default:
    throw TGenericException(TALES_SRCANDLINE,
                           "LevelWidths::intToWidth("
                           "int)",
                           std::string("Invalid width value: ")
                            + StringConversion::toString(width));
    break;
  }
}


} 
