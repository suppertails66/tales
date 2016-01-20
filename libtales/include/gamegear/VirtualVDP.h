#ifndef VIRTUALVDP_H
#define VIRTUALVDP_H


#include "structs/Tbyte.h"
#include "gamegear/GGColor.h"

namespace Tales {


/**
 * Simulation of certain components of the Game Gear VDP.
 */
class VirtualVDP {
public:

	/**
	* Constructor.
	* Initializes VRAM, CRAM, and registers to default values.
	*/
	VirtualVDP();
	
  /**
	* Destructor.
	*/
	~VirtualVDP();

	/**
	* Size in bytes of a VDP word.
	*/
	const static int vdpWordSize = 0x2;

	/**
	* Size in bytes of VRAM.
	*/
	const static int vramSize = 0x4000;
	
	/**
	* Size in bytes of CRAM.
	*/
	const static int cramSize = 0x40;

	/**
	* Enum of possible values of the code register.
	*/
	enum CodeRegisterCommands {
	  commandCodeRead           = 0x00, /**< Read from RAM. */
	  commandCodeWriteVRAM      = 0x01, /**< Write to VRAM. */
	  commandCodeWriteRegister  = 0x02, /**< Write to a register. */
	  commandCodeWriteCRAM      = 0x03  /**< Write to CRAM. */
	};

	/**
	* Starting location of palette 0 in CRAM.
	*/
	const static int palette0Address = 0x00;
	
	/**
	* Starting location of palette 1 in CRAM.
	*/
	const static int palette1Address = 0x20;

/*	// Low-level VDP operations
	void sendControlPortWord(int command);
	void sendDataPortWord(int value); */

	// Mid-level data manipulation
	
	/**
	* Reads from VRAM at the given address.
	* @param address An address in VRAM.
	* @return A const pointer to the specified VRAM address.
	*/
	const Tbyte* vramRead(int address) const;
	
	/**
	* Writes a block of data to VRAM at the given address.
	* @param address An address in VRAM.
	* @param src The data to be copied to VRAM.
	* @param srclen The length, in bytes, of src.
	*/
	void vramWrite(int address, const Tbyte* src, int srclen);
	
	/**
	 * Returns const pointer to the tile data at the given index.
	 * @param tileNum Number of the tile to retrieve.
	 * @return Const pointer to the tile data at the given index.
	 */
	const Tbyte* tileRead(int tileNum) const;

	/**
	* Reads from CRAM at the given address.
	* @param address An address in CRAM.
	* @return A const pointer to the specified CRAM address.
	*/
	const Tbyte* cramRead(int address) const;
	
	/**
	* Writes a block of data to CRAM at the given address.
	* @param address An address in CRAM.
	* @param src The data to be copied to CRAM.
	* @param srclen The length, in bytes, of src.
	*/
	void cramWrite(int address, const Tbyte* src, int srclen);

	// High-level interface
	
	//getTile(int tileCode);
	
	/**
	* Returns a selected color from a loaded palette.
	* @param paletteNum The palette to look up.
	* @param colorNum The number of the color to look up in the palette.
	* @return A GGColor containing the specified color.
	*/
	GGColor getColor(int paletteNum, int colorNum) const;
	
	//setTile()?
	
	/**
	* Modifies a selected color in a palette.
	* @param paletteNum The palette to modify.
	* @param colorNum The number of the color to modify in the palette.
	* @param color A GGColor containing the new color value.
	*/
	void setColor(int paletteNum, int colorNum, const GGColor& color);

protected:

  /**
	* Array of raw VRAM data.
	*/
	Tbyte* vram_;

  /**
	* Array of raw CRAM data.
	*/
	Tbyte* cram_;

  /**
	* Value of the address register.
	*/
	int addressRegister_;

  /**
	* Value of the code register.
	*/
	int codeRegister_;

  /**
	* Returns the starting address of the given palette.
	* @param paletteNum Number of the palette to look up.
	* @return The starting address of the given palette.
	*/
	int getPaletteStartingAddress(int paletteNum) const;
	
};


};


#endif
