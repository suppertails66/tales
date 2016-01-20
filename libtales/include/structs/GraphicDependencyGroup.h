#ifndef GRAPHICDEPENDENCYGROUP_H
#define GRAPHICDEPENDENCYGROUP_H


#include "structs/Tbyte.h"
#include "structs/Taddress.h"
#include "structs/GraphicDependencyGroupEntry.h"
#include <vector>
#include <string>

namespace Tales {


typedef std::vector<Taddress>
    BankPointerAddressCollection;
    
typedef std::vector<GraphicDependencyGroupEntry>
    GraphicDependencyGroupEntryCollection;

/**
 * Container for GraphicDependencyGroupEntries.
 * Keeps track of addresses containing a single-byte bank number that must
 * be altered if the dependent graphics are moved.
 * @see GraphicDependencyGroupEntry
 */
class GraphicDependencyGroup {
public:
  /**
   * Default constructor.
   */
  GraphicDependencyGroup();
  
  /**
   * Accessor.
   */
  BankPointerAddressCollection& bankPointerAddresses();
  
  /**
   * Accessor.
   */
  GraphicDependencyGroupEntryCollection& entries();
  
  void save(std::string& data);
  
  int load(const Tbyte* data);
protected:

  BankPointerAddressCollection bankPointerAddresses_;
  
  GraphicDependencyGroupEntryCollection entries_;
  
};


};


#endif 
