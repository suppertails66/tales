#ifndef BASEEDITOR_H
#define BASEEDITOR_H


namespace Tales {


/**
 * Abstract base for editors.
 */
class BaseEditor {
public:
  /**
   * Default constructor.
   */
  BaseEditor();
  
  /**
   * Virtual destructor.
   */
  virtual ~BaseEditor();
  
  /**
   * Reloads all shared data and ensures the editor is up to date.
   * Used when switching from one editor to another in order to make sure
   * changes are properly reflected.
   */
  virtual void refresh() =0;
protected:
  
};


};


#endif
