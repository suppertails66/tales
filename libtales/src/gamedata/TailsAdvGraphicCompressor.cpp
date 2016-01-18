#include "gamedata/TailsAdvGraphicCompressor.h"
#include "util/ByteConversion.h"
#include "util/ByteSizes.h"
#include "structs/Tbyte.h"
#include "exception/TGenericException.h"
#include "util/StringConversion.h"
#include <string>
#include <vector>
#include <cstring>
#include <iostream>

using namespace Luncheon;
	
namespace Tales {


/*TailsAdvGraphicCompressor::TailsAdvGraphicCompressor(
                          LoadedROM& rom,
                          int substitutionTableAddress) {
  // Copy the substitution table
  std::memcpy(substitutionTable,
              rom.directRead(substitutionTableAddress),
              substitutionTableSize);
} */

/*void TailsAdvGraphicCompressor::loadFromMapGraphicsHeader(
						VirtualVDP& vdp,
						LoadedROM& rom,
						int headerAddress) {

	// Load header values
	
	int levelGraphicsBankNum
		= ByteConversion::fromBytes(
			rom.directRead(headerAddress),
			ByteSizes::uint8Size,
			EndiannessTypes::little,
			SignednessTypes::nosign);
	
	int levelGraphicsVDPCommand
		= ByteConversion::fromBytes(
			rom.directRead(headerAddress + 1),
			ByteSizes::uint16Size,
			EndiannessTypes::little,
			SignednessTypes::nosign);
	
	int mapGraphicsBankedAddress
		= ByteConversion::fromBytes(
			rom.directRead(headerAddress + 3),
			ByteSizes::uint16Size,
			EndiannessTypes::little,
			SignednessTypes::nosign);
	
	int objectGraphicsHeaderBankedAddress
		= ByteConversion::fromBytes(
			rom.directRead(headerAddress + 5),
			ByteSizes::uint16Size,
			EndiannessTypes::little,
			SignednessTypes::nosign);

	// Save current bank
	rom.saveBank(2);

	// Switch to bank containing graphics
	rom.changeBank(2, levelGraphicsBankNum);

//	std::cout << std::hex << levelGraphicsBankNum << " " << mapGraphicsBankedAddress << std::endl;

	// Load the compressed map graphics
	// The VDP write address is the low 14 bits of the VDP command
	decompress(vdp, 
				rom,
				mapGraphicsBankedAddress,
				(levelGraphicsVDPCommand & 0x3FFF));

	// Object graphics not implemented

	// Restore original bank
	rom.restoreBank();

} */

int TailsAdvGraphicCompressor::decompress(
          GGTileSet& dst,
					const Tbyte* src,
					TableSubstitutionOption substitutionOption,
					const Tbyte* substitutionTable) {
							
//	std::cout << "VDP write address: " << vdpWriteAddress << std::endl;
	
	// Number of compression bitpairs (i.e. number of tiles to decompress)
	int numCompressionBitpairs
		= ByteConversion::fromBytes(
			(src + 2),
			ByteSizes::uint16Size,
			EndiannessTypes::little,
			SignednessTypes::nosign);
	
	// Offset from the start of the graphic header to the compression bitpairs
	int compressionBitpairsOffset
		= ByteConversion::fromBytes(
			(src + 4),
			ByteSizes::int16Size,
			EndiannessTypes::little,
			SignednessTypes::sign);
  
	int compressionBitpairsBankedAddress
		= compressionBitpairsOffset;
  
  // Offset to start of data (always 6 bytes from start of header)
	int compressedDataBankedAddress = 6;
	
	// Resize destination GGTileSet to number of tiles to decompress
	dst = GGTileSet(numCompressionBitpairs);
							
//	std::cout << "numBitpairs: " << numCompressionBitpairs << std::endl;
//	std::cout << "Bitpairs offset: " << compressionBitpairsOffset << std::endl;

	// Intermediate storage for decompressed data
	Tbyte decompressionBuffer[decompressionBufferSize];
	Tbyte decompressionSecondaryBuffer[decompressionBufferSize];
	std::memset(decompressionBuffer, 0, decompressionBufferSize);
	std::memset(decompressionSecondaryBuffer, 0, decompressionBufferSize);

	int remainingBitpairs = numCompressionBitpairs;
	int dataGetpos = compressedDataBankedAddress;
	int bitpairGetpos = compressionBitpairsBankedAddress;
//	int vdpPutpos = vdpWriteAddress;
	
	int byteCount = 0;
	int tileNum = 0;

//  std::cout << "bitpairs: " << numCompressionBitpairs << std::endl;

//  int bad = 0;
	while (remainingBitpairs > 0) {
	
	  if (dataGetpos >= compressionBitpairsBankedAddress) {
//	    std::cerr << "bad " << bad << ": " << remainingBitpairs << std::endl;

      // OK, so apparently someone decided to be "clever" by specifying
      // in most map graphic headers that there are 0x100 tiles, but then
      // only including data for the tiles that are actually used (map graphics
      // are written to VRAM 0x2000 -- if they were actually 0x100 tiles long,
      // the last 0x40 tiles would get overwritten by the nametable and SAT).
      // Basically, the game purposely breaks its own data format for no
      // real reason, and we have to deal with it somehow.
      
      // Get the actual number of tiles of data
      int actualNumBitpairs = numCompressionBitpairs - remainingBitpairs;
      
      // If actual number of tiles is not divisible by 4, round up
      // to the nearest multiple of 4.
      // We do this because the compressor will truncate any trailing
      // compression commands that do not fit in a whole byte, potentially
      // corrupting tiles.
      if (actualNumBitpairs % 4) {
        actualNumBitpairs = ((actualNumBitpairs / 4) * 4) + 4;
      }
      
      // Resize the output tile array to the number of tiles needed
      dst.resize(actualNumBitpairs);
      
      // End decompression
	    break;
	    
//	    ++bad;
	  } 

    // Get next byte (next 4 bitpairs)
		Tbyte bitpairByte 
			= src[bitpairGetpos++];
		
		// Check the bitpairs in the byte (max 4)
		for (int i = 0; i < 4; i++) {
			// Get the command (lowest 2 bits)
			int command = (bitpairByte & 0x3);

			// Decompress according to the specified command
			switch (command) {
			case decompressionCommandSecondaryBufferCopy:
				decompressSecondaryBufferCopy(decompressionBuffer,
												decompressionSecondaryBuffer,
												src,
												dataGetpos);
				break;
			case decompressionCommandUncompressed:
				decompressUncompressed(decompressionBuffer,
												decompressionSecondaryBuffer,
												src,
												dataGetpos);
				break;
			case decompressionCommandZeroOptimized:
				decompressZeroOptimized(decompressionBuffer,
												decompressionSecondaryBuffer,
												src,
												dataGetpos);
				break;
			case decompressionCommandZeroOptimizedXOR:
				decompressZeroOptimizedXOR(decompressionBuffer,
												decompressionSecondaryBuffer,
												src,
												dataGetpos);
				break;
			default:
			  // Invalid command: throw
			  throw TGenericException(TALES_SRCANDLINE,
			                         "TailsAdvGraphicDecompressor::decompress("
			                         " VirtualVDP&,LoadedROM&,int,int)",
			                         std::string("Invalid decompression command ")
			                         + StringConversion::toString(command));
				break;
			}

			// Copy decompressed output
			GGTile& tile = dst[tileNum];
			
			// If substitution enabled, replace values using substitution table
			if (substitutionOption == tableSubstitution) {
			  // Buffer to hold substituted data
			  Tbyte substitutionBuffer[decompressionBufferSize];
			  
			  // Substitute table values for read ones
			  for (int i = 0; i < decompressionBufferSize; i++) {
			    // Use the read values as indices into the substitution table,
			    // writing the values in the table instead of the read ones
          substitutionBuffer[i]
            = *(substitutionTable + decompressionBuffer[i]);
			  }
			  
			  // Assign substituted data to tile
        tile.assignFromInterleavedPixels(substitutionBuffer);
			  byteCount += decompressionBufferSize;
        ++tileNum;
			}
			// If substitution not enabled, copy decompressed data directly
			else {
			  // Copy read data to VRAM
//			  vdp.vramWrite(vdpPutpos,
//						  decompressionBuffer,
//						  decompressionBufferSize);
//			  vdpPutpos += decompressionBufferSize;
        tile.assignFromInterleavedPixels(decompressionBuffer);
			  byteCount += decompressionBufferSize;
        ++tileNum;
			}

//			for (int k = 0; k < decompressionBufferSize; k++) {
//				std::cout << " " << (int)((Tbyte)decompressionBuffer[k]);
//			}
//			std::cout << std::endl;

//			std::cout << (int)((Tbyte)decompressionBuffer[0]) << std::endl;

			// Move next bitpair into least significant bits
			bitpairByte >>= 2;
			--remainingBitpairs;

			// Stop when all bitpairs read
			if (remainingBitpairs <= 0) {
				break;
			}
		}

	}

  return byteCount;
}
						
int TailsAdvGraphicCompressor::compress(
          std::string& dst,
          const GGTileSet& src,
					TableSubstitutionOption substitutionOption,
					const Tbyte* substitutionTable) {
  
  // Temporary storage for compressed data
  std::string compressedData;
  
  // Buffer containing last compressed tile (needed for XOR compression)
//  Tbyte lastTileData[decompressionBufferSize];
  
  // An empty buffer (needed for secondaryBufferCopy)
  Tbyte secondaryBuffer[decompressionBufferSize];
  std::memset(secondaryBuffer, 0, decompressionBufferSize);
  
  // Vector to hold compression commands
  std::vector<int> compressionCommands;
  
//  std::cout << "Size: " << src.numTiles() << std::endl;
  
  for (int i = 0; i < src.numTiles(); i++) {
    // Interleave tile pixel data
    Tbyte interleavedData[decompressionBufferSize];
    src[i].toInterleavedPixels(interleavedData);
    
/*    for (int j = 0; j < decompressionBufferSize; j++) {
      std::cout << std::hex << (int)(interleavedData[j]) << " ";
    } */
//    std::cout << std::endl;
//    char c;
//    std::cin >> c;
    
    // Substitute values if requested
    if (substitutionOption == tableSubstitution) {
      for (int j = 0; j < decompressionBufferSize; j++) {
        interleavedData[j] = substitutionTable[interleavedData[j]];
      }
    }
    
    // Compress tile data using each method
    
    // Secondary buffer compression
    bool secondaryBufferCompressionPossible
        = compressSecondaryBufferCopy(interleavedData,
                                      secondaryBuffer);
                                      
    // No compression
    std::string uncompressedCompressed;
    compressUncompressed(uncompressedCompressed,
                         interleavedData);
    
    // Zero-optimized
    std::string zeroOptimizedCompressed;
    compressZeroOptimized(zeroOptimizedCompressed,
                          interleavedData);
    
    // Zero-optimized XOR
    std::string zeroOptimizedXORCompressed;
    compressZeroOptimizedXOR(zeroOptimizedXORCompressed,
                             interleavedData);
                             
/*    if (i == 8) {     
      std::cout << "secondary: "
        << secondaryBufferCompressionPossible << std::endl;
      std::cout << "uncompressed: "
        << uncompressedCompressed.size() << std::endl;
      std::cout << "zero: "
        << zeroOptimizedCompressed.size() << std::endl;
      std::cout << "zero xor: "
        << zeroOptimizedXORCompressed.size() << std::endl;
    } */
                             
/*    std::cout << "secondary: "
      << secondaryBufferCompressionPossible << std::endl;
    std::cout << "uncompressed: "
      << uncompressedCompressed.size() << std::endl;
    std::cout << "zero: "
      << zeroOptimizedCompressed.size() << std::endl;
    std::cout << "zero xor: "
      << zeroOptimizedXORCompressed.size() << std::endl; */
    
    
    // Choose best algorithm for compressing this tile.
    // Secondary buffer compression is always used if possible; otherwise,
    // the most space-efficient of the remaining options is chosen
    
    if (secondaryBufferCompressionPossible) {
//      std::cout << "secondary" << std::endl;
      compressionCommands.push_back(
          (int)decompressionCommandSecondaryBufferCopy);
      // No compressed data to add
    }
    else {
      // Use uncompressed if neither of the other options is better
      if ((uncompressedCompressed.size()
            <= zeroOptimizedCompressed.size())
          && (uncompressedCompressed.size()
            <= zeroOptimizedXORCompressed.size())) {
//        std::cout << "uncompressed" << std::endl;
        compressionCommands.push_back(
            (int)decompressionCommandUncompressed);
        compressedData += std::string((char*)interleavedData,
                                      decompressionBufferSize);
      }
      else {
        // Use whichever zero-optimized encoding is smaller
        if (zeroOptimizedXORCompressed.size()
              < zeroOptimizedCompressed.size()) {
          // Zero-optimized XOR smallest
//          std::cout << "zero-opt xor" << std::endl;
          compressionCommands.push_back(
              (int)decompressionCommandZeroOptimizedXOR);
          compressedData += zeroOptimizedXORCompressed;
        }
        else {
          // Zero-optimized smallest
//          std::cout << "zero-opt" << std::endl;
          compressionCommands.push_back(
              (int)decompressionCommandZeroOptimized);
          compressedData += zeroOptimizedCompressed;
        }
      }
      
    }
    
//    char c;
//    std::cin >> c;
    
    // Copy to lastTileData
//    std::memcpy(lastTileData,
//                interleavedData,
//                decompressionBufferSize);
  }
  
  // Generate header
  
  Tbyte headerBuffer[graphicHeaderSize];
  
//  int unused = 0x0001;
  int unused = 0x0000;
  int numTiles = compressionCommands.size();
  int bitpairOffset = graphicHeaderSize + compressedData.size();
  
  ByteConversion::toBytes(unused,
                          headerBuffer + 0,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  
  ByteConversion::toBytes(numTiles,
                          headerBuffer + 2,
                          ByteSizes::uint16Size,
                          EndiannessTypes::little,
                          SignednessTypes::nosign);
  
  ByteConversion::toBytes(bitpairOffset,
                          headerBuffer + 4,
                          ByteSizes::int16Size,
                          EndiannessTypes::little,
                          SignednessTypes::sign);
                          
  // Append header to dst
  dst += std::string((char*)headerBuffer, graphicHeaderSize);
  
  // Append compressed data to dst
  dst += compressedData;
  
  // Generate compression bitpairs and append to dst
  for (int j = 0; j < compressionCommands.size(); j += 4) {
    
    int limit = 4;
    
    // If less than 4 bitpairs remaining, generate only those
    if ((compressionCommands.size() - j) < 4) {
      // If the number of bitpairs is not divisible by four, the last one
      // to three pairs will simply be discarded
      
      // or not??? e.g. claw grabber graphic
//      break;
      
      limit = compressionCommands.size() - j;
    }
    
    Tbyte output = 0;
    
    // Generate bitpairs
    for (int k = 0; k < limit; k++) {
      Tbyte command = compressionCommands[j + k];
      
      // Place at correct position in byte
      output |= (command << (2 * k));
    }
    
//    std::cout << std::hex << (int)output << " ";
    
    // Append byte to output
//    if (limit > 0) {
//      dst += output;
//    }
    dst += output;
  }
    
//  std::cout << std::endl;
  
  return dst.size();
}

bool TailsAdvGraphicCompressor::compressSecondaryBufferCopy(
                                 const Tbyte* src,
	                               Tbyte* secondaryBuffer) {
  for (int i = 0; i < decompressionBufferSize; i++) {
    if (src[i] != secondaryBuffer[i]) {
      return false;
    }
  }
  
  return true;
}
		
int TailsAdvGraphicCompressor::compressUncompressed(
    std::string& dst,
	  const Tbyte* src) {
	dst += std::string((char*)src, decompressionBufferSize);
	return dst.size();
}
		
int TailsAdvGraphicCompressor::compressZeroOptimized(
    std::string& dst,
	  const Tbyte* src) {
  Tbyte compressionBits[4];
  std::memset(compressionBits, 0, 4);
  
  std::string compressedData;
  
  // Make four passes (one for each byte in compressionBits)
  for (int i = 0;
       i < 4;
       i++) {
    
    // Examine 8 bytes each pass (total 32)
    for (int j = 0;
         j < 8;
         j++) {
        
      int getpos = ((i * 8) + j);
     
      if (src[getpos] == 0) {
        // Value is zero; bit is already set accordingly
      }
      else {
        // Value is literal; set corresponding bit
        compressionBits[i] |= (0x01 << j);
       
        // Add value
        compressedData += src[getpos];
      }
    } 
  }
  
  dst += std::string((char*)compressionBits, 4);
  dst += compressedData;
  
/*  std::cout << dst.size() << std::endl;
  for (int i = 0; i < dst.size(); i++) {
    std::cout << (int)(*((unsigned char*)(dst.c_str() + i))) << " ";
  }
  std::cout << std::endl; */

//  char c;
//  std::cin >> c;
  
  return dst.size();
}
		
int TailsAdvGraphicCompressor::compressZeroOptimizedXOR(
    std::string& dst,
	  const Tbyte* src) {
  // Copy input buffer
  Tbyte buffer[decompressionBufferSize];
  std::memcpy(buffer, src, decompressionBufferSize);
  
	// Positions for each XOR
	int bufPutpos1 = 15;
	int bufPutpos2 = 31;
  
	// Replace every byte from positions 2-15 and 18-31
	// with the one two positions before it, XORed with
	// the unmodified byte
	for (int i = 0; i < 7; i++) {
		// Bytes are copied in pairs, per the original routine
		for (int j = 0; j < 2; j++) {
			buffer[bufPutpos1]
				= (buffer[bufPutpos1 - 2]
					^ buffer[bufPutpos1]);
			--bufPutpos1;
		}
		
		for (int j = 0; j < 2; j++) {
			buffer[bufPutpos2]
				= (buffer[bufPutpos2 - 2]
					^ buffer[bufPutpos2]);
			--bufPutpos2;
		}
	}
  
  // Compress zero-optimized
  return compressZeroOptimized(dst,
                               buffer);
  
}

/*int TailsAdvGraphicCompressor::decompress(
            VirtualVDP& vdp,
						LoadedROM& rom,
						int bankedGraphicAddress,
						int vdpWriteAddress,
						TableSubstitutionOption substitutionOption,
						const Tbyte* substitutionTable) {
							
//	std::cout << "VDP write address: " << vdpWriteAddress << std::endl;
	
	int numCompressionBitpairs
		= ByteConversion::fromBytes(
			rom.bankedRead(bankedGraphicAddress + 2),
			ByteSizes::uint16Size,
			EndiannessTypes::little,
			SignednessTypes::nosign);
	
	int compressionBitpairsOffset
		= ByteConversion::fromBytes(
			rom.bankedRead(bankedGraphicAddress + 4),
			ByteSizes::int16Size,
			EndiannessTypes::little,
			SignednessTypes::sign);

	int compressionBitpairsBankedAddress
		= bankedGraphicAddress + compressionBitpairsOffset;
	int compressedDataBankedAddress = bankedGraphicAddress + 6;
							
//	std::cout << "numBitpairs: " << numCompressionBitpairs << std::endl;
//	std::cout << "Bitpairs offset: " << compressionBitpairsOffset << std::endl;

	// Intermediate storage for decompressed data
	Tbyte decompressionBuffer[decompressionBufferSize];
	Tbyte decompressionSecondaryBuffer[decompressionBufferSize];
	std::memset(decompressionBuffer, 0, decompressionBufferSize);
	std::memset(decompressionSecondaryBuffer, 0, decompressionBufferSize);

	int remainingBitpairs = numCompressionBitpairs;
	int dataGetpos = compressedDataBankedAddress;
	int bitpairGetpos = compressionBitpairsBankedAddress;
	int vdpPutpos = vdpWriteAddress;
	
	int byteCount = 0;

	while (remainingBitpairs > 0) {

		Tbyte bitpairByte 
			= *((const Tbyte*)(rom.bankedRead(bitpairGetpos++)));
		
		// Check the bitpairs in the byte (max 4)
		for (int i = 0; i < 4; i++) {
			// Get the command (lowest 2 bits)
			int command = (bitpairByte & 0x3);

			// Decompress according to the specified command
			switch (command) {
			case decompressionCommandSecondaryBufferCopy:
				decompressSecondaryBufferCopy(decompressionBuffer,
												decompressionSecondaryBuffer,
												rom,
												dataGetpos);
				break;
			case decompressionCommandUncompressed:
				decompressUncompressed(decompressionBuffer,
												decompressionSecondaryBuffer,
												rom,
												dataGetpos);
				break;
			case decompressionCommandZeroOptimized:
				decompressZeroOptimized(decompressionBuffer,
												decompressionSecondaryBuffer,
												rom,
												dataGetpos);
				break;
			case decompressionCommandZeroOptimizedXOR:
				decompressZeroOptimizedXOR(decompressionBuffer,
												decompressionSecondaryBuffer,
												rom,
												dataGetpos);
				break;
			default:
			  // Invalid command: throw
			  throw TGenericException(TALES_SRCANDLINE,
			                         "TailsAdvGraphicDecompressor::decompress("
			                         " VirtualVDP&,LoadedROM&,int,int)",
			                         std::string("Invalid decompression command ")
			                         + StringConversion::toString(command));
				break;
			}

			// Copy decompressed output to VDP
			
			// If substitution enabled, replace values using substitution table
			if (substitutionOption == tableSubstitution) {
			  // Substitute table values for read ones
			  for (int i = 0; i < decompressionBufferSize; i++) {
			    // Use the read values as indices into the substitution table,
			    // writing the values in the table to VRAM instead of the read ones
			    vdp.vramWrite(vdpPutpos++,
			                  substitutionTable + decompressionBuffer[i],
			                  1);
          ++byteCount;
			  }
			}
			// If substitution not enabled, copy decompressed data directly to VRAM
			else {
			  // Copy read data to VRAM
			  vdp.vramWrite(vdpPutpos,
						  decompressionBuffer,
						  decompressionBufferSize);
			  vdpPutpos += decompressionBufferSize;
			  byteCount += decompressionBufferSize;
			}

//			for (int k = 0; k < decompressionBufferSize; k++) {
//				std::cout << " " << (int)((Tbyte)decompressionBuffer[k]);
//			}
//			std::cout << std::endl;

//			std::cout << (int)((Tbyte)decompressionBuffer[0]) << std::endl;

			// Move next bitpair into least significant bits
			bitpairByte >>= 2;
			--remainingBitpairs;

			// Stop when all bitpairs read
			if (remainingBitpairs <= 0) {
				break;
			}
		}

	}

  return byteCount;
}

int TailsAdvGraphicCompressor::decompress(
          VirtualVDP& vdp,
					LoadedROM& rom,
					int bankedGraphicAddress,
					int vdpWriteAddress) {
  // Decompress without substitution
  return decompress(vdp,
             rom,
             bankedGraphicAddress,
             vdpWriteAddress,
             noTableSubstitution,
             NULL);
} */

void TailsAdvGraphicCompressor::decompressSecondaryBufferCopy(
	  Tbyte* decompressionBuffer,
	  Tbyte* secondaryDecompressionBuffer,
	  const Tbyte* src,
	  int& dataGetpos) {
	// Copy secondary buffer to primary
	std::memcpy(decompressionBuffer,
				secondaryDecompressionBuffer,
				decompressionBufferSize);
}

void TailsAdvGraphicCompressor::decompressUncompressed(
	  Tbyte* decompressionBuffer,
	  Tbyte* secondaryDecompressionBuffer,
	  const Tbyte* src,
	  int& dataGetpos) {
	// Fill decompression buffer
	std::memcpy(decompressionBuffer,
				src + dataGetpos,
				decompressionBufferSize);

	dataGetpos += decompressionBufferSize;
}

void TailsAdvGraphicCompressor::decompressZeroOptimized(
	  Tbyte* decompressionBuffer,
	  Tbyte* secondaryDecompressionBuffer,
	  const Tbyte* src,
	  int& dataGetpos) {
	// Load compression bitfield
	Tbyte decompressionBitfield[4];
	std::memcpy(decompressionBitfield,
				src + dataGetpos,
				4);
	dataGetpos += 4;

	int putpos = 0;
	for (int i = 0; i < 4; i++) {
		
		Tbyte bitfield = decompressionBitfield[i];

		// Check each bit in field
		for (int j = 0x01; j <= 0x80; j <<= 1) {
			// Bit set
			if (bitfield & j) {
				// Next byte in stream
				decompressionBuffer[putpos++]
					= *(src + (dataGetpos));
        ++dataGetpos;
			}
			// Bit not set
			else {
				// Zero
				decompressionBuffer[putpos++] = 0;
			}
		}
	}
}

void TailsAdvGraphicCompressor::decompressZeroOptimizedXOR(
	  Tbyte* decompressionBuffer,
	  Tbyte* secondaryDecompressionBuffer,
	  const Tbyte* src,
	  int& dataGetpos) {
	decompressZeroOptimized(decompressionBuffer,
							secondaryDecompressionBuffer,
							src,
							dataGetpos);

	// Positions for each XOR
	int bufPutpos1 = 2;
	int bufPutpos2 = 18;

	// Replace every byte from positions 2-15 and 18-31
	// with the one two positions before it, XORed with
	// the unmodified byte
	for (int i = 0; i < 7; i++) {
		// Bytes are copied in pairs, per the original routine
		for (int j = 0; j < 2; j++) {
			decompressionBuffer[bufPutpos1]
				= (decompressionBuffer[bufPutpos1 - 2]
					^ decompressionBuffer[bufPutpos1]);
			++bufPutpos1;
		}

		for (int j = 0; j < 2; j++) {
			decompressionBuffer[bufPutpos2]
				= (decompressionBuffer[bufPutpos2 - 2]
					^ decompressionBuffer[bufPutpos2]);
			++bufPutpos2;
		}
	}
}

/*void TailsAdvGraphicCompressor::decompressSecondaryBufferCopy(
									Tbyte* decompressionBuffer,
									Tbyte* secondaryDecompressionBuffer,
									const LoadedROM& rom,
									int& dataGetpos) {
	// Copy secondary buffer to primary
	std::memcpy(decompressionBuffer,
				secondaryDecompressionBuffer,
				decompressionBufferSize);
	
}

void TailsAdvGraphicCompressor::decompressUncompressed(
									Tbyte* decompressionBuffer,
									Tbyte* secondaryDecompressionBuffer,
									const LoadedROM& rom,
									int& dataGetpos) {
	// Fill decompression buffer
	std::memcpy(decompressionBuffer,
				rom.bankedRead(dataGetpos),
				decompressionBufferSize);

	dataGetpos += decompressionBufferSize;
}

void TailsAdvGraphicCompressor::decompressZeroOptimized(
									Tbyte* decompressionBuffer,
									Tbyte* secondaryDecompressionBuffer,
									const LoadedROM& rom,
									int& dataGetpos) {
	// Load compression bitfield
	Tbyte decompressionBitfield[4];
	std::memcpy(decompressionBitfield,
				rom.bankedRead(dataGetpos),
				4);
	dataGetpos += 4;

	int putpos = 0;
	for (int i = 0; i < 4; i++) {
		
		Tbyte bitfield = decompressionBitfield[i];

		// Check each bit in field
		for (int j = 0x01; j <= 0x80; j <<= 1) {
			// Bit set
			if (bitfield & j) {
				// Next byte in stream
				decompressionBuffer[putpos++]
					= *(rom.bankedRead(dataGetpos++));
			}
			// Bit not set
			else {
				// Zero
				decompressionBuffer[putpos++] = 0;
			}
		}
	}
}

void TailsAdvGraphicCompressor::decompressZeroOptimizedXOR(
									Tbyte* decompressionBuffer,
									Tbyte* secondaryDecompressionBuffer,
									const LoadedROM& rom,
									int& dataGetpos) {
	decompressZeroOptimized(decompressionBuffer,
							secondaryDecompressionBuffer,
							rom,
							dataGetpos);

	// Positions for each XOR
	int bufPutpos1 = 2;
	int bufPutpos2 = 18;

	// Replace every byte from positions 2-15 and 18-31
	// with the one two positions before it, XORed with
	// the unmodified byte
	for (int i = 0; i < 7; i++) {
		// Bytes are copied in pairs, per the original routine
		for (int j = 0; j < 2; j++) {
			decompressionBuffer[bufPutpos1]
				= (decompressionBuffer[bufPutpos1 - 2]
					^ decompressionBuffer[bufPutpos1]);
			++bufPutpos1;
		}

		for (int j = 0; j < 2; j++) {
			decompressionBuffer[bufPutpos2]
				= (decompressionBuffer[bufPutpos2 - 2]
					^ decompressionBuffer[bufPutpos2]);
			++bufPutpos2;
		}
	}
} */


};
