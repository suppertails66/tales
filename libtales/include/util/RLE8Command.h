#ifndef RLE8COMMAND_H
#define RLE8COMMAND_H


#include "util/RLE8CommandType.h"
#include "util/RLE8ValueCollection.h"

namespace Luncheon {


class RLE8Command {
public:
  virtual ~RLE8Command();
  
  RLE8Command();
  
  RLE8CommandTypes::RLE8CommandType commandType();
  void setCommandType(RLE8CommandTypes::RLE8CommandType
                        commandType__);
                        
  int quantity();
  void setQuantity(int quantity__);
  
  RLE8ValueCollection& values();
  
  
protected:
  
  RLE8CommandTypes::RLE8CommandType commandType_;
  
  int quantity_;
  
  RLE8ValueCollection values_;
  
};


};


#endif 
