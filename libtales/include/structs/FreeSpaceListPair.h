#ifndef FREESPACELISTPAIR_H
#define FREESPACELISTPAIR_H


namespace Tales {


/**
 * (address, length) pairs to be used in a FreeSpaceList.
 */
class FreeSpaceListPair {
public:
  /**
   * Default constructor.
   * Address and length are both initialized to zero.
   */
  FreeSpaceListPair();
  
  /**
   * Constructor.
   * @param address__ The address of the free space.
   * @param length__ The length in bytes of the free space.
   */
  FreeSpaceListPair(int address__, int length__);
  
  /**
   * Getter for the address of the free space.
   */
  int address() const;
  
  /**
   * Getter for the length in bytes of the free space.
   */
  int length() const;
  
  /**
   * Setter for the address of the free space.
   * @param address__ The new address of the free space.
   */
  void setAddress(int address__);
  
  /**
   * Setter for the length in bytes of the free space.
   * @param length__ The new length in bytes of the free space.
   */
  void setLength(int length__);
  
protected:

  /**
   * The address of the free space.
   */
  int address_;
  
  /**
   * The length in bytes of the free space.
   */
  int length_;

};


};


#endif
