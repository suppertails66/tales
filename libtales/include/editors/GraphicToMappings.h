#ifndef GRAPHICTOMAPPINGS_H
#define GRAPHICTOMAPPINGS_H


#include "editors/GraphicToMappingEntry.h"

namespace Tales {


class GraphicToMappings {
public:
  enum CompressionType {
    uncompressed,
    compressed
  };

  static int numMappingsForGraphic(CompressionType compressionType,
                                   int index);
  
  static GraphicToMappingEntry graphicMapping(
                                   CompressionType compressionType,
                                   int graphicIndex,
                                   int mappingIndex);
protected:
  static GraphicToMappingEntry compressedGraphicMapping(int graphicIndex,
                                                        int mappingIndex);

  const static int cmpgrp000size = 8;
  const static int cmpgrp001size = 2;
  const static int cmpgrp002size = 2;
  const static int cmpgrp003size = 7;
  const static int cmpgrp004size = 3;
  const static int cmpgrp005size = 4;
  const static int cmpgrp006size = 3;
  const static int cmpgrp007size = 3;
  const static int cmpgrp008size = 2;
  const static int cmpgrp009size = 2;
  const static int cmpgrp00Asize = 2;
  const static int cmpgrp00Bsize = 4;
  const static int cmpgrp00Csize = 6;
  const static int cmpgrp00Dsize = 3;
  const static int cmpgrp00Esize = 3;
  const static int cmpgrp00Fsize = 4;
  const static int cmpgrp010size = 5;
  const static int cmpgrp011size = 1;
  const static int cmpgrp012size = 1;
  const static int cmpgrp013size = 6;
  const static int cmpgrp014size = 2;
  const static int cmpgrp015size = 4;
  const static int cmpgrp016size = 2;
  const static int cmpgrp017size = 3;
  const static int cmpgrp018size = 2;
  const static int cmpgrp019size = 2;
  const static int cmpgrp01Asize = 4;
  const static int cmpgrp01Bsize = 2;
  const static int cmpgrp01Csize = 2;
  const static int cmpgrp01Dsize = 4;
  const static int cmpgrp01Esize = 1;
  const static int cmpgrp01Fsize = 10;
  const static int cmpgrp020size = 5;
//  const static int cmpgrp021size = 0;
  const static int cmpgrp022size = 25;
  const static int cmpgrp023size = 2;
  const static int cmpgrp024size = 2;
  const static int cmpgrp025size = 1;
  const static int cmpgrp026size = 4;
  const static int cmpgrp027size = 11;
  const static int cmpgrp028size = 8;
  const static int cmpgrp029size = 1;
  const static int cmpgrp02Asize = 16;
  const static int cmpgrp02Bsize = 10;
  const static int cmpgrp02Csize = 10;
  const static int cmpgrp02Dsize = 4;
  const static int cmpgrp02Esize = 8;
  const static int cmpgrp02Fsize = 4;
  const static int cmpgrp030size = 3;
  const static int cmpgrp031size = 5;
  const static int cmpgrp032size = 5;
  const static int cmpgrp033size = 8;
  const static int cmpgrp034size = 7;
  const static int cmpgrp035size = 5;
  const static int cmpgrp036size = 14;
  const static int cmpgrp037size = 2;
  const static int cmpgrp038size = 2;
//  const static int cmpgrp039size = 0;
//  const static int cmpgrp03Asize = 0;
  const static int cmpgrp03Bsize = 1;
  const static int cmpgrp03Csize = 1;
  const static int cmpgrp03Dsize = 1;
  const static int cmpgrp03Esize = 1;
  // 3F-50 have no mappings
  
  const static GraphicToMappingEntry cmpgrp000maps[cmpgrp000size];
  const static GraphicToMappingEntry cmpgrp001maps[cmpgrp001size];
  const static GraphicToMappingEntry cmpgrp002maps[cmpgrp002size];
  const static GraphicToMappingEntry cmpgrp003maps[cmpgrp003size];
  const static GraphicToMappingEntry cmpgrp004maps[cmpgrp004size];
  const static GraphicToMappingEntry cmpgrp005maps[cmpgrp005size];
  const static GraphicToMappingEntry cmpgrp006maps[cmpgrp006size];
  const static GraphicToMappingEntry cmpgrp007maps[cmpgrp007size];
  const static GraphicToMappingEntry cmpgrp008maps[cmpgrp008size];
  const static GraphicToMappingEntry cmpgrp009maps[cmpgrp009size];
  const static GraphicToMappingEntry cmpgrp00Amaps[cmpgrp00Asize];
  const static GraphicToMappingEntry cmpgrp00Bmaps[cmpgrp00Bsize];
  const static GraphicToMappingEntry cmpgrp00Cmaps[cmpgrp00Csize];
  const static GraphicToMappingEntry cmpgrp00Dmaps[cmpgrp00Dsize];
  const static GraphicToMappingEntry cmpgrp00Emaps[cmpgrp00Esize];
  const static GraphicToMappingEntry cmpgrp00Fmaps[cmpgrp00Fsize];
  const static GraphicToMappingEntry cmpgrp010maps[cmpgrp010size];
  const static GraphicToMappingEntry cmpgrp011maps[cmpgrp011size];
  const static GraphicToMappingEntry cmpgrp012maps[cmpgrp012size];
  const static GraphicToMappingEntry cmpgrp013maps[cmpgrp013size];
  const static GraphicToMappingEntry cmpgrp014maps[cmpgrp014size];
  const static GraphicToMappingEntry cmpgrp015maps[cmpgrp015size];
  const static GraphicToMappingEntry cmpgrp016maps[cmpgrp016size];
  const static GraphicToMappingEntry cmpgrp017maps[cmpgrp017size];
  const static GraphicToMappingEntry cmpgrp018maps[cmpgrp018size];
  const static GraphicToMappingEntry cmpgrp019maps[cmpgrp019size];
  const static GraphicToMappingEntry cmpgrp01Amaps[cmpgrp01Asize];
  const static GraphicToMappingEntry cmpgrp01Bmaps[cmpgrp01Bsize];
  const static GraphicToMappingEntry cmpgrp01Cmaps[cmpgrp01Csize];
  const static GraphicToMappingEntry cmpgrp01Dmaps[cmpgrp01Dsize];
  const static GraphicToMappingEntry cmpgrp01Emaps[cmpgrp01Esize];
  const static GraphicToMappingEntry cmpgrp01Fmaps[cmpgrp01Fsize];
  const static GraphicToMappingEntry cmpgrp020maps[cmpgrp020size];
//  const static GraphicToMappingEntry cmpgrp021maps[cmpgrp021size];
  const static GraphicToMappingEntry cmpgrp022maps[cmpgrp022size];
  const static GraphicToMappingEntry cmpgrp023maps[cmpgrp023size];
  const static GraphicToMappingEntry cmpgrp024maps[cmpgrp024size];
  const static GraphicToMappingEntry cmpgrp025maps[cmpgrp025size];
  const static GraphicToMappingEntry cmpgrp026maps[cmpgrp026size];
  const static GraphicToMappingEntry cmpgrp027maps[cmpgrp027size];
  const static GraphicToMappingEntry cmpgrp028maps[cmpgrp028size];
  const static GraphicToMappingEntry cmpgrp029maps[cmpgrp029size];
  const static GraphicToMappingEntry cmpgrp02Amaps[cmpgrp02Asize];
  const static GraphicToMappingEntry cmpgrp02Bmaps[cmpgrp02Bsize];
  const static GraphicToMappingEntry cmpgrp02Cmaps[cmpgrp02Csize];
  const static GraphicToMappingEntry cmpgrp02Dmaps[cmpgrp02Dsize];
  const static GraphicToMappingEntry cmpgrp02Emaps[cmpgrp02Esize];
  const static GraphicToMappingEntry cmpgrp02Fmaps[cmpgrp02Fsize];
  const static GraphicToMappingEntry cmpgrp030maps[cmpgrp030size];
  const static GraphicToMappingEntry cmpgrp031maps[cmpgrp031size];
  const static GraphicToMappingEntry cmpgrp032maps[cmpgrp032size];
  const static GraphicToMappingEntry cmpgrp033maps[cmpgrp033size];
  const static GraphicToMappingEntry cmpgrp034maps[cmpgrp034size];
  const static GraphicToMappingEntry cmpgrp035maps[cmpgrp035size];
  const static GraphicToMappingEntry cmpgrp036maps[cmpgrp036size];
  const static GraphicToMappingEntry cmpgrp037maps[cmpgrp037size];
  const static GraphicToMappingEntry cmpgrp038maps[cmpgrp038size];
//  const static GraphicToMappingEntry cmpgrp039maps[cmpgrp039size];
//  const static GraphicToMappingEntry cmpgrp03Amaps[cmpgrp03Asize];
  const static GraphicToMappingEntry cmpgrp03Bmaps[cmpgrp03Bsize];
  const static GraphicToMappingEntry cmpgrp03Cmaps[cmpgrp03Csize];
  const static GraphicToMappingEntry cmpgrp03Dmaps[cmpgrp03Dsize];
  const static GraphicToMappingEntry cmpgrp03Emaps[cmpgrp03Esize];
};


};


#endif
