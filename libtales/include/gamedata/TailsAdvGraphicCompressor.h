#ifndef TAILSADVGRAPHICCOMPRESSOR_H
#define TAILSADVGRAPHICCOMPRESSOR_H


#include "gamegear/LoadedROM.h"
#include "gamegear/VirtualVDP.h"
#include "gamegear/GGTile.h"
#include "gamegear/GGTileSet.h"
#include "gamedata/TailsAdvAddresses.h"
#include "gamegear/GGTileSet.h"
#include <cstdlib>

namespace Tales {


/**
 * Functions for decompressing Tails Adventures format compressed graphics.
 */
class TailsAdvGraphicCompressor {
public:
  /**
   * Size in bytes of the substitution table.
   */
  const static int substitutionTableSize = 0x100;

	/**
	 * Enum of options for whether to substitute values written to VDP.
	 * @see decompress()
	 */
	enum TableSubstitutionOption {
	  noTableSubstitution,
	  tableSubstitution
	};
	
	/**
	 * Constructor.
	 * Loads the substitution table from the given direct ROM address.
	 * @param rom LoadedROM to read from.
	 * @param substitutionTableAddress Direct (non-banked) address of the
	 * substitution table. This should always be 0x100,  but can be overriden
	 * if needed.
	 */
/*	TailsAdvGraphicCompressor(LoadedROM& rom,
	                          int substitutionTableAddress
	                            = TailsAdvAddresses
	                                ::GraphicsDecSubstitutionTable); */

  /**
   * Decompresses graphics from LoadedROM into VirtualVDP using a map header.
   * @param vdp VirtualVDP to store decompressed graphics.
   * @param rom LoadedROM to get compressed data from.
   * @param headerAddress Direct (unbanked) address of the header to load from.
   */
/*	static void loadFromMapGraphicsHeader(
		VirtualVDP& vdp,
		LoadedROM& rom,
		int headerAddress); */

  /**
   * Decompresses a graphic from raw bytes to a GGTileSet.
   * @param dst GGTileSet to hold decompressed graphics. Will be resized
   * to fit the decompressed data.
   * @param src Source byte array.
   * @param substitutionOption Table substitution option.
   * @param substitutionTable Substitution table, or NULL if substitutionOption
   * disabled.
   * @return Number of bytes of data written.
   */
	static int decompress(
	          GGTileSet& dst,
						const Tbyte* src,
						TableSubstitutionOption substitutionOption,
						const Tbyte* substitutionTable = NULL);
						
  static int compress(
            std::string& dst,
            const GGTileSet& src,
						TableSubstitutionOption substitutionOption,
						const Tbyte* substitutionTable = NULL);
            
	
  /**
   * Decompresses graphics from LoadedROM into VirtualVDP.
   * This is primarily intended to be called by loadFromMapGraphicsHeader(),
   * but can also be called manually if non-level graphics need to be loaded.
   * @param vdp VirtualVDP to store decompressed graphics.
   * @param rom LoadedROM to get compressed data from. Must have banks
   * configured so bankedGraphicAddress points to the correct location
   * on a banked read.
   * @param bankedGraphicAddress The banked (not direct) address of the
   * compressed graphics data in the LoadedROM. The LoadedROM's banks
   * must be set up so that this address points to the correct bank.
   * @vdpWriteAddress The base address at which to start writing data into the
   * VirtualVDP. No data will be written to lower addresses.
   * @param substitutionOption Table substitution option.
   * @param substitutionTable Substitution table, or NULL if substitutionOption
   * disabled.
   * @return Number of bytes of data written at the vdpWriteAddress.
   * @see loadFromMapGraphicsHeader()
   */
/*	static int decompress(
	          VirtualVDP& vdp,
						LoadedROM& rom,
						int bankedGraphicAddress,
						int vdpWriteAddress,
						TableSubstitutionOption substitutionOption,
						const Tbyte* substitutionTable); */
						
  /**
   * Decompresses without substitution.
   * @see decompress()
   */
/*	static int decompress(
	          VirtualVDP& vdp,
						LoadedROM& rom,
						int bankedGraphicAddress,
						int vdpWriteAddress); */

protected:
  /**
   * Direct (non-banked) address of the substitution table in ROM.
   */
  const static int substitutionTableAddress = 0x100;

  /**
   * The number of bytes in a decompression buffer.
   * The buffer contains 32 bytes of uncompressed, interleaved,
   * 4 bits per pixel VRAM data, corresponding to a full 8x8 tile of 64 pixels.
   */
	const static int decompressionBufferSize = 0x20;

  /**
   * Decompression command: copy secondary buffer to primary.
   */
	const static int decompressionCommandSecondaryBufferCopy = 0x0;

  /**
   * Decompression command: copy uncompressed data.
   */
	const static int decompressionCommandUncompressed = 0x1;

  /**
   * Decompression command: do zero-optimized decompression.
   */
	const static int decompressionCommandZeroOptimized = 0x2;

  /**
   * Decompression command: do zero-optimized XOR decompression.
   */
	const static int decompressionCommandZeroOptimizedXOR = 0x3;
	
	const static int graphicHeaderSize = 6;
	
	/**
	 * The substitution table.
	 * This is used to substitute data on specially flagged VDP writes.
	 */
//	Tbyte substitutionTable[substitutionTableSize];

	static void decompressSecondaryBufferCopy(
		Tbyte* decompressionBuffer,
		Tbyte* secondaryDecompressionBuffer,
		const Tbyte* src,
		int& dataGetpos);

	static void decompressUncompressed(
		Tbyte* decompressionBuffer,
		Tbyte* secondaryDecompressionBuffer,
		const Tbyte* src,
		int& dataGetpos);

	static void decompressZeroOptimized(
		Tbyte* decompressionBuffer,
		Tbyte* secondaryDecompressionBuffer,
		const Tbyte* src,
		int& dataGetpos);

	static void decompressZeroOptimizedXOR(
		Tbyte* decompressionBuffer,
		Tbyte* secondaryDecompressionBuffer,
		const Tbyte* src,
		int& dataGetpos);

  /**
   * Attempt to compress one tile of data at src using secondary buffer copy.
   * If all bytes in the buffer match the source, then this compression is
   * possible. Success or failure is indicated by the return value.
   * Due to the way this game implements this, it will only return true
   * if the source data is all null bytes.
   * @param src Source data. Must consist of (decompressionBufferSize) bytes of
   * uncompressed, interleaved pixel data.
   * @param secondaryBuffer Secondary buffer to compare src to. If all values
   * of src match the secondary buffer, then this form of compression is
   * possible.
   * @return True if this compression is possible.
   */
	static bool compressSecondaryBufferCopy(
		const Tbyte* src,
		Tbyte* secondaryBuffer);
		
	static int compressUncompressed(
	  std::string& dst,
		const Tbyte* src);
		
	static int compressZeroOptimized(
	  std::string& dst,
		const Tbyte* src);
		
	static int compressZeroOptimizedXOR(
	  std::string& dst,
		const Tbyte* src);

  /**
   * Decompression function: copies secondary buffer to primary.
   * @param decompressionBuffer The primary decompression buffer.
   * @param secondaryDecompressionBuffer The secondary decompression buffer.
   * @param rom The LoadedROM to fetch data from.
   * @param dataGetpos The data input position for the LoadedROM. This will be
   * updated by this function to point to the new get position after the
   * function returns.
   */
/*	static void decompressSecondaryBufferCopy(
		Tbyte* decompressionBuffer,
		Tbyte* secondaryDecompressionBuffer,
		const LoadedROM& rom,
		int& dataGetpos); */

  /**
   * Decompression function: copies uncompressed data from ROM.
   * @param decompressionBuffer The primary decompression buffer.
   * @param secondaryDecompressionBuffer The secondary decompression buffer.
   * @param rom The LoadedROM to fetch data from.
   * @param dataGetpos The data input position for the LoadedROM. This will be
   * updated by this function to point to the new get position after the
   * function returns.
   */
/*	static void decompressUncompressed(
		Tbyte* decompressionBuffer,
		Tbyte* secondaryDecompressionBuffer,
		const LoadedROM& rom,
		int& dataGetpos); */

  /**
   * Decompression function: performs zero-optimized decompression.
   * @param decompressionBuffer The primary decompression buffer.
   * @param secondaryDecompressionBuffer The secondary decompression buffer.
   * @param rom The LoadedROM to fetch data from.
   * @param dataGetpos The data input position for the LoadedROM. This will be
   * updated by this function to point to the new get position after the
   * function returns.
   */
/*	static void decompressZeroOptimized(
		Tbyte* decompressionBuffer,
		Tbyte* secondaryDecompressionBuffer,
		const LoadedROM& rom,
		int& dataGetpos); */

  /**
   * Decompression function: performs zero-optimized XOR decompression.
   * @param decompressionBuffer The primary decompression buffer.
   * @param secondaryDecompressionBuffer The secondary decompression buffer.
   * @param rom The LoadedROM to fetch data from.
   * @param dataGetpos The data input position for the LoadedROM. This will be
   * updated by this function to point to the new get position after the
   * function returns.
   */
/*	static void decompressZeroOptimizedXOR(
		Tbyte* decompressionBuffer,
		Tbyte* secondaryDecompressionBuffer,
		const LoadedROM& rom,
		int& dataGetpos); */

};


};


#endif
