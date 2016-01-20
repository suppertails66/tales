#ifndef SUBMAPS_H
#define SUBMAPS_H


#include "gamedata/PrimaryMaps.h"

namespace Tales {


/**
 * Container for submap data.
 */
class SubMaps {
public:

  /**
   * Number of elements of subMapCounts.
   */
  const static int subMapCountsSize
    = PrimaryMaps::primaryMapTableSize;

  /**
   * Number of elements of subMapLevelObjectTableCounts.
   */
  const static int subMapLevelObjectTableCountsSize
    = 0x16;

  /**
   * Number of elements of subMapFixedGraphicTableCounts.
   */
  const static int subMapFixedGraphicTableCountsSize
    = 0x0D;

  /**
  * Table giving count of number of submaps for each primary map number.
  */
	const static int subMapCounts[];

  /**
  * Table giving count of maps per area for fixed graphic tables.
  */
	const static int subMapFixedGraphicTableCounts[];

  /**
  * Table giving count of maps per area for level object lists.
  */
	const static int subMapLevelObjectTableCounts[];

protected:

};


};


#endif 
