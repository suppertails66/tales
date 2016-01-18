#ifndef LOADEDROM_H
#define LOADEDROM_H

#include <string>
#include <stack>
#include "structs/Tbyte.h"
#include "exception/PoppedEmptyStackException.h"

namespace Tales {


/**
* Stack type for bank slot storage.
*/
typedef std::stack<int> BankSlotStack;

/**
* Stack type for bank number storage.
*/
typedef std::stack<int> BankNumStack;

/**
 * Class for loading and reading a ROM file.
 * Contains functions for reading using both direct addressing
 * and Sega mapper banking conventions, as well as auxiliary
 * functions for simulating bank switching.
 */
class LoadedROM {
public:
  /**
	* Constructor.
	* @param filename The name of the ROM file to load.
	* @throws FileNotFoundException
	*/
	LoadedROM(const std::string& filename);
	
  /**
	* Destructor.
	*/
	~LoadedROM();
	
  /**
	 * Copy constructor.
	 * @param src Source to copy from.
	 */
	LoadedROM(const LoadedROM& src);
	
  /**
	 * Copy assignment.
	 * @param src Source to copy from.
	 */
	LoadedROM& operator=(const LoadedROM& src);

	/**
	* The size, in bytes, of each simulated ROM bank.
	*/
	const static int bankSize = 0x4000;

	/**
	* Starting address of bank slot 0.
	*/
	const static int slot0StartAddress = 0x0000;

	/**
	* Starting address of bank slot 1.
	*/
	const static int slot1StartAddress = 0x4000;

	/**
	* Starting address of bank slot 2.
	*/
	const static int slot2StartAddress = 0x8000;

	/**
	* Retrieves the size of the currently loaded ROM file.
	* @return The size of the currently loaded ROM file.
	*/
	int loadedFileSize() const;

	/**
	* Retrieves the path to the currently loaded ROM file.
	* @return The path to the currently loaded ROM file.
	*/
	std::string loadedFileName() const;

  /**
	* Retrieves the number of the bank currently loaded in a slot.
	* @param slotNum The number of the slot to check.
	* @return The bank currently loaded in slotNum.
	*/
	int getBank(int slotNum);

  /**
	* Changes the number of the bank currently loaded in a slot.
	* @param slotNum The number of the slot whose bank to change.
	* @param bankNum The number of the bank to be loaded.
	*/
	void changeBank(int slotNum, int bankNum);

  /**
	* Get a const pointer to the data at (address), using direct ROM addressing.
	* @param address A direct (non-banked) ROM address.
	* @return A const pointer to the raw data at (address).
	*/
	const Tbyte* directRead(int address) const;
	
	/**
	* Gets a const pointer to the data at (address), using mapper conventions.
	* Using the Sega mapper format, this corresponds to:
	* $0000-3FFF = slot 0
	* $4000-7FFF = slot 1
	* $8000-BFFF = slot 2
	* @param address An address in the banked range 0x0000-0xBFFF.
	* @return A const pointer to the raw data at the banked address.
	*/
	const Tbyte* bankedRead(int address) const;

  /**
	* Converts a banked address to a direct address.
	* @param bankNum The number of the bank.
	* @param bankedAddress A Sega mapper format banked address.
	* @return The direct address corresponding to the banked address.
	*/
	static int getDirectAddress(int bankNum, int bankedAddress);
	
	/**
	 * Converts several parameters into a table index.
	 * @param tableDirectAddr The direct (unbanked) address of the table start.
	 * @param dataBankedAddr A banked (slot-2) address of some data in the table.
	 * @param entrySize The size in bytes of each entry in the table.
	 * @return The index that tableDirectAddr corresponds to in the table.
	 */
	static int toIndex(int tableDirectAddr,
	                   int dataBankedAddr,
	                   int entrySize);
	
	/**
	 * Converts several parameters into a table index.
	 * @param tableDirectAddr The direct (unbanked) address of the table start.
	 * @param index An index into the table.
	 * @param entrySize The size in bytes of each entry in the table.
	 * @return The index that tableDirectAddr corresponds to in the table.
	 */
	static int indexToBankedAddr(int tableDirectAddr,
	                             int index,
	                             int entrySize);

  /**
	* Computes the bank number corresponding to a direct address.
	* @param directAddress A direct (unbanked) address.
	* @return The bank number corresponding to the direct address.
	*/
	static int directToBankNum(int directAddress);

  /**
	* Computes the banked address corresponding to a direct address.
	* Returned address corresponds to slot 2 (0x8000-0xBFFF).
	* @param directAddress A direct (unbanked) address.
	* @return The slot 2 banked address corresponding to the direct address.
	*/
	static int directToBankedAddress(int directAddress);
	
  /**
	* Saves the bank number in the given slot, to be restored with restoreBank().
	* This is a shortcut used to save and restore banks during processing.
	* A call to this function pushes the bank number and the associated slot
	* number onto internal stacks. Subsequent calls to restoreBank() pop the
	* pushed bank numbers back to the corresponding slots. Thus, each call to
	* this function should have a corresponding call to restoreBank().
	* @param slot The number of the slot to be saved.
	* @see restoreBank()
	*/
	void saveBank(int slot);
	
  /**
	* Restores the bank to the slot most recently save with saveBank().
	* @see saveBank()
	* @throws PoppedEmptyStackException
	*/
	void restoreBank();

protected:

	/**
	* Retrieve the number of the bank loaded in slot 0.
	* @return The number of the bank loaded in slot 0.
	*/
	int slot0BankNum() const;

	/**
	* Change the number of the bank loaded in slot 0.
	* @param newSlot0BankNum__ The new slot 0 bank number.
	*/
	void setSlot0BankNum(int newSlot0BankNum__);


	/**
	* Retrieve the number of the bank loaded in slot 1.
	* @return The number of the bank loaded in slot 1.
	*/
	int slot1BankNum() const;

	/**
	* Change the number of the bank loaded in slot 1.
	* @param newSlot1BankNum__ The new slot 1 bank number.
	*/
	void setSlot1BankNum(int newSlot1BankNum__);

	/**
	* Retrieve the number of the bank loaded in slot 2.
	* @return The number of the bank loaded in slot 2.
	*/

	int slot2BankNum() const;

	/**
	* Change the number of the bank loaded in slot 2.
	* @param newSlot2BankNum__ The new slot 2 bank number.
	*/
	void setSlot2BankNum(int newSlot2BankNum__);

	/**
	 * The raw contents of the loaded file.
	 */
	Tbyte* loadedFile_;
	
	/**
	 * Size of the loaded ROM file in bytes.
	 */
	int loadedFileSize_;
	
	/**
	 * The name of the loaded file.
	 */
	std::string loadedFileName_;

	/**
	 * The number of the bank currently loaded in slot 0.
	 */
	int slot0BankNum_;

	/**
	 * The number of the bank currently loaded in slot 1.
	 */
	int slot1BankNum_;

	/**
	 * The number of the bank currently loaded in slot 2.
	 */
	int slot2BankNum_;

	/**
	 * Stack of slot numbers for use with saveBank() and restoreBank().
	 */
	BankSlotStack bankSlotStack_;

	/**
	 * Stack of bank numbers for use with saveBank() and restoreBank().
	 */
	BankNumStack bankNumStack_;

	/**
	 * Retrieves the number of the slot associated with a banked address.
	 * @param bankedAddress A Sega mapper format banked address.
	 * @return The number of the slot corresponding to the banked address.
	 */
	static int getBankedAddressSlot(int bankedAddress);
	
};


};


#endif
