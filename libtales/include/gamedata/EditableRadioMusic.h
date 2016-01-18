#ifndef EDITABLERADIOMUSIC_H
#define EDITABLERADIOMUSIC_H


#include "structs/Tbyte.h"
#include "structs/Taddress.h"
#include "structs/Tmap.h"
#include "gamegear/LoadedROM.h"
#include "gamegear/WritableROM.h"
#include "structs/SaveHelper.h"
#include "structs/LoadHelper.h"
#include <string>
#include <vector>

namespace Tales {


class EditableRadioMusic {
public:
  typedef std::vector<int> RadioMusicIDCollection;

  /**
   * Default constructor.
   */
  EditableRadioMusic();
  
  /**
   * Constructor from ROM.
   * @param rom ROM to load from.
   * @param address__ Address of the radio table.
   * @param numEntries__ Number of entries in the radio table.
   */
  EditableRadioMusic(LoadedROM& rom,
                     Taddress address__,
                     int numEntries);
                     
  int numMusicEntries() const;
                     
  int& musicEntry(int index);
  
  void save(std::string& data);
  
  int load(const Tbyte* data);
  
  void exportToROM(WritableROM& rom);
  
protected:

  Taddress address_;

  RadioMusicIDCollection musicEntries_;
  
};


};


#endif
