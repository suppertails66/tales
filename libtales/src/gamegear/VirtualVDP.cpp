#include "gamegear/VirtualVDP.h"
//#include "exception/BadVDPCommandException.h"
#include "gamegear/GGTile.h"
#include "util/ByteConversion.h"
#include <cstring>

namespace Tales {


VirtualVDP::VirtualVDP()
	: vram_(0),
	  cram_(0),
	  addressRegister_(0),
		codeRegister_(commandCodeWriteVRAM) {

	// Initialize VRAM and CRAM
	vram_ = new Tbyte[vramSize];
	cram_ = new Tbyte[cramSize];
	std::memset(vram_, 0, vramSize);
	std::memset(cram_, 0, cramSize);
}

VirtualVDP::~VirtualVDP() {
	delete vram_;
	delete cram_;
}

/*void VirtualVDP::sendControlPortWord(int command) {
	// Top 2 bits of command = code register value
	int codeRegCommand = ((command & 0xC000) >> 14);
	int address = (command & 0x3FFF);

	switch (codeRegCommand) {
	case commandCodeRead:
		codeRegister_ = codeRegCommand;
		addressRegister_ = address;
		break;
	case commandCodeWriteVRAM:
		codeRegister_ = codeRegCommand;
		addressRegister_ = address;
		break;
	case commandCodeWriteRegister:
		codeRegister_ = codeRegCommand;
		addressRegister_ = address;
		// actual register changes not handled
		break;
	case commandCodeWriteCRAM:
		codeRegister_ = codeRegCommand;
		addressRegister_ = address;
		break;
	default:
//		throw BadVDPCommandException();
		break;
	}
}


void VirtualVDP::sendDataPortWord(int value) {

	switch (codeRegister_) {
	case commandCodeRead:
		// not handled
		break;
	case commandCodeWriteVRAM:
		// Write the value to the current VRAM address
		Luncheon::ByteConversion::toBytes(value,
										  vram_ + addressRegister_,
										  vdpWordSize,
										  Luncheon::EndiannessTypes::little,
										  Luncheon::SignednessTypes::nosign);
		// Update the address register
		addressRegister_ += vdpWordSize;
		break;
	case commandCodeWriteRegister:
		// not handled
		break;
	case commandCodeWriteCRAM:
		// Write the value to the current CRAM address
		Luncheon::ByteConversion::toBytes(value,
										  cram_ + addressRegister_,
										  vdpWordSize,
										  Luncheon::EndiannessTypes::little,
										  Luncheon::SignednessTypes::nosign);
		// Update the address register
		addressRegister_ += vdpWordSize;
		break;
	default:
//		throw BadVDPCommandException();
		break;
	}
} */

const Tbyte* VirtualVDP::vramRead(int address) const {
	return (vram_ + address);
}

void VirtualVDP::vramWrite(int address, const Tbyte* src, int srclen) {
	std::memcpy(vram_ + address, src, srclen);
}

const Tbyte* VirtualVDP::tileRead(int tileNum) const {
	return (vram_ + (tileNum * GGTile::dataSize));
}

const Tbyte* VirtualVDP::cramRead(int address) const {
	return (cram_ + address);
}

void VirtualVDP::cramWrite(int address, const Tbyte* src, int srclen) {
	std::memcpy(cram_ + address, src, srclen);
}

GGColor VirtualVDP::getColor(int paletteNum, int colorNum) const {

	// Find the starting address of the chosen palette
	int baseAddress = getPaletteStartingAddress(paletteNum);

	// Get the color at the specified location
	GGColor result;
	result.setNativeColor(Luncheon::ByteConversion::fromBytes(
								cram_ + baseAddress + (colorNum * vdpWordSize),
								vdpWordSize,
								Luncheon::EndiannessTypes::little,
								Luncheon::SignednessTypes::nosign));

	return result;
}

void VirtualVDP::setColor(int paletteNum, int colorNum, const GGColor& color) {
	int baseAddress = getPaletteStartingAddress(paletteNum);

	// Write the specified color to CRAM
	Luncheon::ByteConversion::toBytes(color.nativeColor(),
										cram_ + baseAddress + (colorNum * vdpWordSize),
										vdpWordSize,
										Luncheon::EndiannessTypes::little,
										Luncheon::SignednessTypes::nosign);

}

int VirtualVDP::getPaletteStartingAddress(int paletteNum) const {
	// Find the starting address of the chosen palette
	switch (paletteNum) {
	case 0:
		return palette0Address;
		break;
	case 1:
		return palette1Address;
		break;
	default:
	  return -1;
//		throw BadVDPCommandException();
		break;
	}
}


};
