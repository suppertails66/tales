#include "util/FileManip.h"

namespace Luncheon {


unsigned int FileManip::fileExists(const std::string& filename) {
  std::ifstream ifs(filename,
                    std::ios_base::binary);
                    
  if ((int)(getFileSize(ifs)) <= 0) {
    return false;
  }
  
  return true;
}

unsigned int FileManip::getFileSize(std::ifstream& ifs) {
  std::ifstream::pos_type pos = ifs.tellg();
  ifs.seekg(0, std::ios_base::end);
  std::ifstream::pos_type size = ifs.tellg();
  ifs.seekg(pos);
  
  return size;
}


};
