#include "gamedata/TailsAdvRLECompressor.h"
#include <cstring>
#include <iostream>

namespace Tales {


int TailsAdvRLECompressor::decompress(Tbyte* dst,
                                       const Tbyte* src, 
										                   int dstlen) {
//	std::cout << std::hex << (unsigned int)(unsigned char)(src[0]) << std::endl;
//	std::cout << (unsigned int)(unsigned char)(src[1]) << std::endl;
//	std::cout << (unsigned int)(unsigned char)(src[2]) << std::endl;

	int putpos = 0;
	int getpos = 0;

	bool done = false;

	while (!done) {
		switch ((unsigned char)(src[getpos])) {
		// 0xFF: encoded run
		case encodedRunToken:
		{
			int count = (unsigned char)(src[getpos + 2]);

			// Count of 0 = end of data
			if (count == 0) {
			  // Keep accurate count
			  getpos += encodedRunSize;
				done = true;
				break;
			}

			// Prevent overruns
			if (putpos + count >= dstlen) {
				count = (dstlen - putpos);
			}

			int value = (unsigned char)(src[getpos + 1]);

			std::memset(dst + putpos, value, count);
			putpos += count;

			// Advance past encoded run
			getpos += encodedRunSize;
			break;
		}
		// anything other than 0xFF: literal value
		default:
			dst[putpos++] = src[getpos++];
			break;
		}

		// Stop if maximum length reached
		if (putpos >= dstlen) {
			break;
		}
	}
	
	return getpos;
}

int TailsAdvRLECompressor::compress(
                     Tbyte* dst,
                     const Tbyte* src,
                     int srclen) {
  int putpos = 0;
  int getpos = srclen - 1;
  
  int trailingNullCount = 0;
  
  // Count the number of trailing null bytes in the source data
  // to determine if we need an explicit terminator.
  while ((getpos >= 0)
         && (src[getpos] == 0)) {
    ++trailingNullCount;
    --getpos;
  }
  
  // An explicit terminator is only used when it saves space
  // (i.e. when the number of null bytes at the end of the data
  // is greater than the encoded run size)
/*  bool needsTerminator = false;
  if (trailingNullCount > encodedRunSize) {
    needsTerminator = true;
    
    // Truncate input to portion needed for compression
    srclen -= trailingNullCount;
  } */
  bool needsTerminator = true;
  
  // Compress the data
  getpos = 0;
  int compressedSize = 0;
  
  while (getpos < srclen) {
    // Get next byte in sequence
    Tbyte nextByte = src[getpos];
    
    // Check for repeated sequence of bytes
    int checkpos = getpos + 1;
    int count = 1;  // Include initial byte in count
    while ((checkpos < srclen)
           && (count < maximumRunLength) // Don't exceed max encoding length
           && (src[checkpos] == nextByte)) {
      ++count;
      ++checkpos;
    }
    
    // If repeat count is greater than run length size, or byte to encode is
    // 0xFF (cannot be encoded absolutely due to use as encoded run indicator),
    // use encoded run
    if ((nextByte == encodedRunToken)
        || (count > encodedRunSize)) {
      // Encode the run
      encodeRun(dst + putpos,
                nextByte,
                count);
      
      // Advance putpos
      putpos += encodedRunSize;
      
      // Add to compression size count
      compressedSize += encodedRunSize;
    }
    // If repeat count is less than run length size, use absolute run
    else {
      // Copy data from src to dst
      std::memcpy(dst + putpos, src + getpos, count);
      
      // Advance putpos
      putpos += count;
      
      // Add to compression size count
      compressedSize += count;
    }
    
    // Advance getpos
    getpos += count;
    
  }
  
  // Add an explicit terminator if needed
  if (needsTerminator) {
    // Terminator is an encoded run with length 0
    encodeRun(dst + putpos,
              encodedRunToken,    // we can use any value here -- it's ignored
              endOfDataLengthToken);
    
    putpos += encodedRunSize;
  }
  
  // Return number of bytes in compressed data
  return compressedSize;
}

int TailsAdvRLECompressor::safeCompressionSize(int inputSize) {
  // In the worst case scenario, the size of the input will double when
  // compressed.
  // This worst case occurs when the data consists of the pattern
  //
  // FF [x] FF [x] FF [x] ...
  //
  // where [x] is any byte. This sequence compresses to
  //
  // FF FF 01 [x] FF FF 01 [x] FF FF 01 [x] ...
  return inputSize * 2;
}

void TailsAdvRLECompressor::encodeRun(
                      Tbyte* dst,
                      Tbyte byteToEncode,
                      int repeatCount) {
  // Write encoded run token
  dst[0] = encodedRunToken;
  
  // Write encoded byte
  dst[1] = byteToEncode;
  
  // Write count
  dst[2] = repeatCount;
}


};
