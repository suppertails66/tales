#ifndef GRAPHICDEPENDENCYGROUPENTRY_H
#define GRAPHICDEPENDENCYGROUPENTRY_H


#include "structs/Tbyte.h"
#include "structs/Taddress.h"
#include <vector>
#include <string>

namespace Tales {


typedef std::vector<Taddress> GraphicPointerAddressCollection;

/**
 * An entry in a list of items representing a set of graphics that must be
 * exported to the same bank.
 * Contains the original source address of the graphic and a list of addresses.
 * Each address points to a 16-bit banked address that points in turn to the
 * graphic. These addresses must be altered if the referenced graphic is moved.
 * @see GraphicDependencyGroup
 */
class GraphicDependencyGroupEntry {
public:
  /**
   * Default constructor.
   */
  GraphicDependencyGroupEntry();
  
  /**
   * Constructor from known values.
   * @param graphicAddress__ Address of the graphic.
   */
  GraphicDependencyGroupEntry(Taddress graphicAddress__);
  
  /**
   * Getter.
   */
  Taddress graphicAddress();
  
  /**
   * Setter.
   */
  void setGraphicAddress(Taddress graphicAddress__);
  
  /**
   * Accessor.
   */
  GraphicPointerAddressCollection& pointerAddresses();
  
  void save(std::string& data);
  
  int load(const Tbyte* data);
  
protected:
  
  Taddress graphicAddress_;
  
  GraphicPointerAddressCollection pointerAddresses_;
  
};


};


#endif
