#ifndef OBJECTGRAPHICSHEADER_H
#define OBJECTGRAPHICSHEADER_H


#include "gamedata/ObjectGraphicSubheader.h"
#include "structs/IndexToAddressMap.h"
#include <vector>

namespace Tales {


typedef std::vector<ObjectGraphicSubheader> ObjectGraphicSubheaderCollection;

class ObjectGraphicsHeader {
public:
  /**
   * Default constructor.
   */
  ObjectGraphicsHeader();
  
  /**
   * Writes to a string.
   * @param data String to write to.
   */
  void save(std::string& data);
  
  /**
   * Reads from a byte array.
   * @param data Byte array to read from.
   * @return Number of bytes read.
   */
  int load(const Tbyte* data);
  
  /**
   * Writes to a byte array.
   * @param data Byte array to write to. Size must be at least (dataSize)
   * bytes.
   * @param indexToAddress Mapping of object graphic indices to their
   * corresponding addresses.
   * @return Number of bytes written.
   */
  int exportToData(Tbyte* data,
                   const IndexToAddressMap& objectIndexToAddress);
  
  /**
   * Returns number of contained subheaders.
   * @return Number of contained subheaders.
   */
  int size() const;
  
  /**
   * Returns raw size in bytes when exported.
   * @return Raw size in bytes when exported.
   */
  int rawSize() const;
  
  /**
   * Copies the given ObjectGraphicSubheader and appends it to the header.
   * @param subheader Subheader to add.
   */
  void push_back(const ObjectGraphicSubheader& subheader);
  
  /**
   * Inserts the given subheader at the given index.
   * @param subheader Subheader to add.
   * @param index Index number of the subheader to remove.
   */
  void insert(int index,
              const ObjectGraphicSubheader& subheader);
  
  /**
   * Erases the subheader at the given index.
   * @param index Index number of the subheader to remove.
   */
  void erase(int index);
  
  /**
   * Returns reference to contained subheader at the given index.
   * @return Reference to contained subheader at the given index.
   */
  ObjectGraphicSubheader& subheader(int index);
  
  /**
   * Returns const reference to contained subheader at the given index.
   * @return Const reference to contained subheader at the given index.
   */
  const ObjectGraphicSubheader& subheader(int index) const;
   
protected:
  /**
   * End of header token.
   */
  const static Tbyte endOfHeaderToken = 0xFF;

  /**
   * Collection of contained subheaders.
   */
  ObjectGraphicSubheaderCollection objectGraphicSubheaders_;
};


};


#endif
