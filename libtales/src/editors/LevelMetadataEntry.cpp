#include "editors/LevelMetadataEntry.h"
#include "exception/InvalidLoadDataException.h"

namespace Tales {


LevelMetadataEntry::LevelMetadataEntry() { };
  
void LevelMetadataEntry::save(std::string& data) {
  SaveHelper saver(data,
                   DataChunkIDs::levelMetadataEntry,
                   0);
                   
  
                   
  saver.finalize();
}

int LevelMetadataEntry::load(const Tbyte* data) {
  int byteCount = 0;

  LoadHelper loader(data,
                    byteCount);
                    
  if (loader.version() > 0) {
    throw InvalidLoadDataException(TALES_SRCANDLINE,
                                   "LevelMetadataEntry::load(const Tbyte*)");
  }
                    
  return byteCount;
}


}; 
