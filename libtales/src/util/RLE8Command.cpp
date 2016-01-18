#include "util/RLE8Command.h"

namespace Luncheon {


RLE8Command::~RLE8Command() { };
  
RLE8Command::RLE8Command()
  : commandType_(RLE8CommandTypes::dummy),
    quantity_(0) { };
  
RLE8CommandTypes::RLE8CommandType RLE8Command::commandType() {
  return commandType_;
}

void RLE8Command::setCommandType(
                      RLE8CommandTypes::RLE8CommandType
                      commandType__) {
  commandType_ = commandType__;
}
                      
int RLE8Command::quantity() {
  return quantity_;
}

void RLE8Command::setQuantity(int quantity__) {
  quantity_ = quantity__;
}

RLE8ValueCollection& RLE8Command::values() {
  return values_;
}


}; 
