#ifndef TAILSADVEDITABLE_H
#define TAILSADVEDITABLE_H


#include "structs/Tbyte.h"
#include "gamegear/WritableROM.h"
#include <string>

namespace Tales {


/**
 * Abstract base class for a piece of editable data in Tails Adventures.
 * All editable data (maps, music assignments, and so on) must derive from
 * this and implement the read(), write() and export() member functions.
 */
class TailsAdvEditable {
public:
  
  /**  
   * Appends a loadable representation of edited state to the given string.
   * @param data A string to which the representation of the altered state
   * should be appended.
   * @see load()
   */
  virtual void save(std::string& data) =0;
  
  /**  
   * Loads edited state from a block of data written using save().
   * @param data A block of raw data corresponding to a previous call to
   * save().
   * @see save()
   */
  virtual int load(const Tbyte* data) =0;
  
  /**  
   * Writes the contained data to a WritableROM.
   * @param rom WritableROM to write data to.
   */
  virtual void exportToROM(WritableROM& rom) =0;
  
  /**
   * Virtual destructor for use by derived classes.
   */
  virtual ~TailsAdvEditable();
  
protected:
  
};


};


#endif 
