#ifndef AREAMETADATAENTRY_H
#define AREAMETADATAENTRY_H


#include "structs/Tbyte.h"
#include "structs/SaveHelper.h"
#include "structs/LoadHelper.h"
#include <string>

namespace Tales {


/**
 * Editor metadata for an area (group of maps, e.g. Poloy Forest).
 */
class AreaMetadataEntry {
public:
  AreaMetadataEntry();
  
  AreaMetadataEntry(const std::string& name__);
  
  void save(std::string& data);
  
  int load(const Tbyte* data);
  
  std::string name() const;
  
  void setName(const std::string& name__);
protected:
  
  int leafIndex() const;
  
  bool hasVRAMIndices() const;
  
  void setLeafIndex(int leafIndex__);
  
  /**
   * Name of the area.
   */
  std::string name_;
  
  /**
   * True if area has editable VRAM graphics indices, false otherwise.
   */
  bool hasVRAMIndices_;
  
  /**
   * Index of the "wind blowing"/leaf effect in the area's VRAM.
   */
  int leafIndex_;
  
};


};


#endif
