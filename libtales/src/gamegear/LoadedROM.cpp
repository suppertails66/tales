#include "gamegear/LoadedROM.h"
#include "exception/FileNotFoundException.h"
#include "exception/PoppedEmptyStackException.h"
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>

namespace Tales {


LoadedROM::LoadedROM(const std::string& filename)
	: loadedFile_(NULL),
	  loadedFileSize_(0),
		slot0BankNum_(0),
		slot1BankNum_(1 * bankSize),
		slot2BankNum_(2 * bankSize) {

	std::ifstream ifs(filename, std::ios_base::binary);

	// Get file size
	ifs.seekg(0, std::ios_base::end);
	loadedFileSize_ = static_cast<int>(ifs.tellg());
	ifs.seekg(0, std::ios_base::beg);

	// Make sure file exists
	if (loadedFileSize_ <= 0) {
		throw FileNotFoundException(TALES_SRCANDLINE,
		                            "TalesEd::TalesEd(const std::string&, bool)",
		                            filename);
	}

	// Load file into memory
	loadedFile_ = new Tbyte[loadedFileSize_];
	ifs.read((char*)loadedFile_, loadedFileSize_);

	loadedFileName_ = filename;
}

LoadedROM::~LoadedROM() {
	delete loadedFile_;
}

LoadedROM::LoadedROM(const LoadedROM& src)
  : loadedFile_(new Tbyte[src.loadedFileSize_]),
	  loadedFileSize_(src.loadedFileSize_),
	  loadedFileName_(src.loadedFileName_),
		slot0BankNum_(src.slot0BankNum_),
		slot1BankNum_(src.slot1BankNum_),
		slot2BankNum_(src.slot2BankNum_),
		bankSlotStack_(src.bankSlotStack_),
		bankNumStack_(src.bankNumStack_) {
  
  // Copy loaded file
  std::memcpy(loadedFile_, src.loadedFile_, src.loadedFileSize_);
  
}

LoadedROM& LoadedROM::operator=(const LoadedROM& src) {
  // Delete and reallocate current file
  delete loadedFile_;
  loadedFile_ = new Tbyte[src.loadedFileSize_];
  
  // Copy data
  std::memcpy(loadedFile_, src.loadedFile_, src.loadedFileSize_);
  loadedFileSize_ = src.loadedFileSize_;
  loadedFileName_ = src.loadedFileName_;
  slot0BankNum_ = src.slot0BankNum_;
  slot1BankNum_ = src.slot1BankNum_;
  slot2BankNum_ = src.slot2BankNum_;
  bankSlotStack_ = src.bankSlotStack_;
  bankNumStack_ = src.bankNumStack_;
  
  // Return self-reference
  return *this;
}

int LoadedROM::loadedFileSize() const {
	return loadedFileSize_;
}

std::string LoadedROM::loadedFileName() const {
	return loadedFileName_;
}

int LoadedROM::slot0BankNum() const {
	return slot0BankNum_;
}

void LoadedROM::setSlot0BankNum(int newSlot0BankNum__) {
	slot0BankNum_ = newSlot0BankNum__;
}

int LoadedROM::slot1BankNum() const {
	return slot1BankNum_;
}

void LoadedROM::setSlot1BankNum(int newSlot1BankNum__) {
	slot1BankNum_ = newSlot1BankNum__;
}

int LoadedROM::slot2BankNum() const {
	return slot2BankNum_;
}

void LoadedROM::setSlot2BankNum(int newSlot2BankNum__) {
	slot2BankNum_ = newSlot2BankNum__;
}

int LoadedROM::getBank(int slotNum) {
	switch (slotNum) {
	case 0:
		return slot0BankNum_;
		break;
	case 1:
		return slot1BankNum_;
		break;
	case 2:
		return slot2BankNum_;
		break;
	default:
		return -1;
		break;
	}
}

void LoadedROM::changeBank(int slotNum, int bankNum) {
	switch (slotNum) {
	case 0:
		slot0BankNum_ = bankNum;
		break;
	case 1:
		slot1BankNum_ = bankNum;
		break;
	case 2:
		slot2BankNum_ = bankNum;
		break;
	default:
		break;
	}
}

const Tbyte* LoadedROM::directRead(int address) const {
	return (loadedFile_ + address);
}

const Tbyte* LoadedROM::bankedRead(int address) const {
	// Slot 2 access
	if (address >= slot2StartAddress) {
		return (loadedFile_ 
				+ (slot2BankNum_ * bankSize)
				+ (address - slot2StartAddress));
	}
	// Slot 1 access
	else if (address >= slot1StartAddress) {
		return (loadedFile_ 
				+ (slot1BankNum_ * bankSize)
				+ (address - slot1StartAddress));
	}
	// Slot 0 access
	else {
		return (loadedFile_ 
				+ (slot0BankNum_ * bankSize)
				+ (address - slot0StartAddress));
	}
}

int LoadedROM::getDirectAddress(int bankNum, int bankedAddress) {
	return ((bankNum * bankSize) 
			+ (bankedAddress 
				- (getBankedAddressSlot(bankedAddress) * bankSize)));
}

int LoadedROM::toIndex(int tableDirectAddr,
                       int dataBankedAddr,
                       int entrySize) {

  // Convert to banked form
  int bankedTableAddr = directToBankedAddress(tableDirectAddr);
    
  // Get the position in the table (in bytes)
  int tablePos = dataBankedAddr - bankedTableAddr;
  
  // Convert to index by dividing by entry size
  return (tablePos / entrySize);
}

int LoadedROM::indexToBankedAddr(int tableDirectAddr,
                                 int index,
                                 int entrySize) {
  // Get direct address of entry
  int directAddr = (tableDirectAddr + (index * entrySize));
  
  // Return as banked address
  return (directToBankedAddress(directAddr));
}

int LoadedROM::directToBankNum(int directAddress) {
  return (directAddress / bankSize);
}

int LoadedROM::directToBankedAddress(int directAddress) {
  // If this is a slot2 address, return in same format
  if (directAddress >= slot2StartAddress) {
    return ((directAddress % bankSize) + slot2StartAddress);
  }
  // Otherwise, return as slot0 or slot1
  else {
    return directAddress;
  }
}

void LoadedROM::saveBank(int slot) {
	bankSlotStack_.push(slot);
	bankNumStack_.push(getBank(slot));
}

void LoadedROM::restoreBank() {
  
  if (bankSlotStack_.empty()) {
    throw PoppedEmptyStackException(TALES_SRCANDLINE,
                                    "LoadedROM::restoreBank",
                                    "bankSlotStack_");
  }
	int slot = bankSlotStack_.top();
	bankSlotStack_.pop();
	
  if (bankNumStack_.empty()) {
    throw PoppedEmptyStackException(TALES_SRCANDLINE,
                                    "LoadedROM::restoreBank",
                                    "bankNumStack_");
  }
	int bankNum = bankNumStack_.top();
	bankNumStack_.pop();

	changeBank(slot, bankNum);
}

int LoadedROM::getBankedAddressSlot(int bankedAddress) {
	// Slot 2 access
	if (bankedAddress >= slot2StartAddress) {
		return 2;
	}
	// Slot 1 access
	else if (bankedAddress >= slot1StartAddress) {
		return 1;
	}
	// Slot 0 access
	else {
		return 0;
	}
}


};
