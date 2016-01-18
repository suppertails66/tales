#include "gamedata/TailsAdvROMLoader.h"
#include "util/StreamOps.h"
#include "exception/FileNotFoundException.h"
#include "exception/InvalidFileException.h"
//#include "util/md5sum.h"
#include <cstring>
#include <cstdio>
#include <iostream>
#include <fstream>
 
using namespace Luncheon;
 
namespace Tales {


const char* TailsAdvROMLoader::expectedCleanRomMD5Base64(
  "qL2xvu0Ij/g8clxa9rheHw");

bool TailsAdvROMLoader::checkROM(
                 const std::string& romPath,
                 bool throwIfFileInvalid) {
  
  // Open the input file and get its size
  std::ifstream ifs(romPath,
                    std::ios_base::binary);
  std::streampos romSize = StreamOps::getStreamSize(ifs);
  
  // Throw FileNotFoundException if file doesn't exist or is empty
  if (romSize <= 0) {
    throw FileNotFoundException(TALES_SRCANDLINE,
                            "TailsAdvROMLoader::loadROM("
                            "const std::string&, bool)",
                            romPath);
  }
  
  // Close ifstream in preparation for MD5 sum using file pointer
  ifs.close();
  
  // C-string to store our result
/*  char md5Hash[32];
  std::memset(md5Hash, 0, sizeof(md5Hash));
  // Open C-style file pointer
	FILE* fd;
	fd = fopen(romPath.c_str(), "r");
	if (fd == NULL) {
    throw FileNotFoundException(TALES_SRCANDLINE,
                            "TailsAdvROMLoader::loadROM("
                            "const std::string&, bool)",
                            romPath);
	}
	// Compute MD5 sum of file
	md5sum(fd, 0, md5Hash);
	// Close file pointer
	fclose(fd);
	
	// If hash does not match expected value and throwIfFileInvalid
	// is true, throw InvalidFileException
	if (std::strcmp(expectedCleanRomMD5Base64,
	                md5Hash) != 0) {
    if (throwIfFileInvalid) {
      throw InvalidFileException(TALES_SRCANDLINE,
                            "TailsAdvROMLoader::loadROM("
                            "const std::string&, bool)",
                             romPath);
    }
  } */
  
  return true;
}


};
