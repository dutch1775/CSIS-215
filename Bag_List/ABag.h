#pragma once

#include <memory>						//include memory allows smart pointers
#include "bagADT.h"						//include bagADT for bag inheritance

const size_t DEFAULT_BAG_SIZE = 10;		//default size of bag (testing will use default)

//bag-array implementation 
//inherets from BagADT
template <typename E>					//array implementation of Bag-list ADT
class ABag : public Bag<E>
{
private:

	int bagSize;						//max size of the bag
	int topOfBag;						//counter tracking how many elements in bag
	std::unique_ptr<E[]> bag;			//unique pointer to bag of E elements 

public:
	
	//base constrcutor
	ABag(int size = DEFAULT_BAG_SIZE)
	{
		bagSize = size;							//set size of bag to specified amount, default if no value given
		topOfBag = 0;							//set top of the bag to zero, since no items have been added
		bag = std::make_unique<E[]>(size);		//dynamically create new bag of type E with size
	}

	//base deconstructor
	~ABag()
	{
		bag.reset(nullptr);							//reset memory from bag and dealloc
		topOfBag = 0;								//set top to 0
		bagSize = 0;								//set bag to 0
	}

	// Insert a new item into the bag -- return false if fails and true if
	// successful
	bool addItem(const E& item)
	{
		bool itemAdded{ false };				//var to hold if item added, default fail

		if (topOfBag != bagSize)				//if bag is not full
		{
			bag[topOfBag] = item;				//set item to bag at open position 						
			itemAdded = true;					//item was added to bag so set true
		}

		if (itemAdded)							//if item was added
		{
			topOfBag++;							//increment top
		}

		return itemAdded;						//return if item was added
	}

	// Looks for 'item' in the bag and if found updates 'item' with the 
	// bag value and returns true.  Otherwise 'item' is left unchanged
	// and the method returns false.
	bool remove(E& item)
	{
		bool isRemoved{ false };					//bool to track removed status

		for (int i = topOfBag; i > 0; --i)			//from top loop through all of the bag
		{
			if (bag[i] == item)						//if item is in bag
			{
				item = bag[i];						//set item to the bag element
				isRemoved = true;					//set is removed to true;

				for (int j = i; j < topOfBag; j++)	//from i, increment until top
				{
					bag[j] = bag[j + 1];			//move all higher elements down
				}
				
			}
		}
		if (isRemoved)							//if item was removed
		{
			topOfBag--;							//decrement top
		}
		return isRemoved;						//return if item was removed
	}

	// Removes the top record from the bag, puts it in returnValue, and
	// returns true if the bag is not empty.  If the bag is empty the 
	// function returns false and returnValue remains unchanged.
	bool removeTop(E& returnValue)
	{
		bool isTopRemoved{ false };					//bool to track top removal
		
		if (topOfBag != 0)							//if bag is not empty
		{
			returnValue = bag[--topOfBag];			//set returnValue to the top element
			isTopRemoved = true;					//top was removed
		}

		return isTopRemoved;						//return if top was removed
	}

	// Finds the record using returnValue and if the record is found updates
	// returnValue based on the contents of the bag and returns true.  If the
	// record is not found the function returns false.  Works just like remove()
	// except that the found record is not removed from the bag.
	bool find(E& returnValue) const
	{
		bool isFound{ false };						//bool tracking if returnValue was found

		for (int i = topOfBag; i > 0; --i)			//from top loop through array
		{
			if (bag[i] == returnValue)				//if returnValue is in the bag
			{
				returnValue = bag[i];				//set returnValue to bag element
				isFound = true;						//set found to true
			}
		}
		return isFound;								//return if returnValue was found
	}

	// Inspect the top of the bag.  If the bag is empty return
	// false and leave 'item' unchanged; otherwise, return true and update 
	// 'item' with the contents of the bag.
	bool inspectTop(E& item) const
	{
		bool isInspected{ false };					//bool tracking if top is inspected

		int tempTop = topOfBag;						//temp var set to top

		if(topOfBag != 0)							//if bag is not empty
		{
			item = bag[--tempTop];					//set item to top
			isInspected = true;						//inspected is true
		}

		return isInspected;							//return if inspected
	}

	// empties the bag
	void emptyBag()
	{
		bag.reset();								//reset the bag to clear contents
		bag = std::make_unique<E[]>(bagSize);		//reinitialize the bag
		topOfBag = 0;								//set top to 0
	}

	// use the += operator to add an item to the bag
	bool operator+=(const E& addend) 
	{
		return addItem(addend);						//add item to bag
	}

	// get the number of items in the bag
	int size() const
	{
		return topOfBag;							//return top to get items in bag
	}

	// get the capacity of the bag (size of your bag's array)
	int bagCapacity() const
	{	
		return bagSize;								//return bag capacity size
	}

};
