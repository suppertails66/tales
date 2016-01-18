#ifndef TAILSADVRLECOMPRESSOR_H
#define TAILSADVRLECOMPRESSOR_H


#include "structs/Tbyte.h"

namespace Tales {


/**
 * Functions for decompressing Tails Adventures format RLE compression.
 */
class TailsAdvRLECompressor {
public:
  /**
   * Token indicating a run-length-encoded sequence.
   */
	const static int encodedRunToken = 0xFF;
	
  /**
   * Special length indicating end of data.
   * When used as the length parameter of an encoded run, this indicates the
   * remaining data is all null bytes and decompression should cease.
   * Note that this terminator is optional, and will only be used if it
   * saves space (i.e. the uncompressed data ends in 4 or more null bytes).
   */
	const static int endOfDataLengthToken = 0x00;

  /**
   * Decompresses a block of Tails Adventures format RLE compressed data.
   * @param dst Destination for decompressed data. Size must be greater than
   * or equal to dstlen.
   * @param src Source of data to decompress.
   * @param dstlen Maximum number of bytes to write to dst.
   * @return The size of the compressed data that was read.
   */
	static int decompress(Tbyte* dst,
	                       const Tbyte* src,
	                       int dstlen);

  /**
   * Compresses a block of data to Tails Adventures format RLE.
   * @param dst Destination for compressed data. To ensure there is enough
   * room for the compressed data in the worst case, allocate the number of
   * bytes given by safeCompressionSize() for the size of the input data.
   * @param src Source of data to compress.
   * @param srclen The number of bytes in the source data.
   * @return The size of the compressed data in bytes.
   * @see safeCompressionSize()
   */
	static int compress(Tbyte* dst,
	                     const Tbyte* src,
	                     int srclen);

  /**
   * Returns the number of bytes needed to store some compressed data.
   * Use this function to safely allocate the destination buffer for
   * calls to compress().
   * @param inputSize The number of bytes of input to be compressed.
   * @see compress()
   */
  static int safeCompressionSize(int inputSize);
protected:

  /**
   * Number of bytes in an encoded run.
   */
  const static int encodedRunSize = 3;
  
  /**
   * Maximum number of bytes that can be represented by an encoded run.
   */
  const static int maximumRunLength = 0xFF;
  
  /**
   * Encodes a run.
   * @param dst Destination position. Must be at least (encodedRunSize) bytes
   * long.
   * @param byteToEncode The byte to be repeated.
   * @param repeatCount The number of recurrences of the byte.
   */
  static void encodeRun(Tbyte* dst,
                        Tbyte byteToEncode,
                        int repeatCount);

};


};


#endif
