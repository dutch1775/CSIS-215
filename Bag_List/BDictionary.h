#pragma once

#include "dictionaryADT.h"
#include "kvpair.h"
#include "ABag.h"

//implementation of dictionaryADT
//inherents from dictADT
template<typename Key, typename E>
class BDictionary : public Dictionary<Key, E>
{
private:

	ABag<KVpair<Key, E>>* DictBag;						//create pointer to bag, DictBag
	int DictSize{ 0 };									//holds size of the dictionary

public:

	// Default constructor
	BDictionary(int size = 10)					
	{
		DictSize = size;								//dictionary size is set to passed in param
		DictBag = new ABag<KVpair<Key, E>>(DictSize);	//dynamically create bag with size DictSize
	}

	// Base destructor
	~BDictionary() 
	{
		delete[] DictBag;								//delete dynamically allocated bag
	}					

	// Reinitialize dictionary
	void clear()
	{
		DictBag->emptyBag();							//call emptyBag bag function
	}

	// Insert a record
	// k: The key for the record being inserted.
	// e: The record being inserted.
	// Return true if insert is successful and false otherwise
	bool insert(const Key& k, const E& e)
	{
		KVpair<Key, E> tempPair(k, e);					//create temporary KVpair, temp, store param
		bool isInserted{ false };						//var to hold if item was inserted
		
		isInserted = (*DictBag += tempPair);			//isInserted is if item was added dictionary

		return isInserted;								//return if item was inserted
	}

	// Looks for a record using the key and if found does the following:
	// - updates the E& rtnVal
	// - removes the record from the dictionary
	// - returns true
	// If the record is not found the function returns false.
	bool remove(const Key& k, E& rtnVal)
	{
		KVpair<Key, E> tempPair(k, rtnVal);				//create temporary KVpair, temp, store param
		bool isRemoved{ false };						//var to hold if item was removed

		isRemoved = DictBag->remove(tempPair);			//isRemoved is if item was removed from dictionary

		if (isRemoved)									//if item was removed
		{
			rtnVal = tempPair.value();					//set rtnVal to the value in temp
		}

		return isRemoved;								//return if item was removed
	}

	// Takes an arbitrary record from the dictionary and does the following:
	// - updates the E& returnValue
	// - removes the record from the dictionary
	// - returns true
	// If the dictionary is empty the function returns false.
	bool removeAny(E& returnValue)
	{
		KVpair<Key, E> tempPair;						//create temporary KVpair, temp, store param
		bool isRemoved{ false };						//var to hold if item was removed

		isRemoved = DictBag->removeTop(tempPair);		//isRemoved is if top item was removed from dictionary

		if (isRemoved)									//if item was removed
		{
			returnValue = tempPair.value();				//set rtnVal to the value in temp
		}

		return isRemoved;								//return if item was removed
	}

	// Looks for a record using the key and if found does the following:
	// - updates the E& returnValue
	// - returns true
	// If the record is not found the function returns false.
	bool find(const Key& k, E& returnValue) const
	{
		KVpair<Key, E> tempPair(k, returnValue);		//create temporary KVpair, temp, store param
		bool isFound{ false };							//var to hold if item was found

		isFound = DictBag->find(tempPair);				//isFound is if the item was found

		if (isFound)									//if item was found
		{
			returnValue = tempPair.value();				//set returnValue to the item value
		}

		return isFound;									//return if item was found
	}

	// Return the number of records in the dictionary.
	int size()
	{	
		return DictBag->size();							//return size of the dictionary
	}
};
