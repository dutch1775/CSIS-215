#pragma once

#include "constants.h"
#include "BufferPoolADT.h"
#include "BufferBlock.h"
#include <fstream>
#include <iostream>

class LRUBufferPool : public BufferPoolADT
{
private:

	//The buffer pool consists of X number of buffer blocks
	int buffPoolSize;			//size of buffer pool
	int buffBlockSize;			//buffer block size
	std::fstream inputFile;		//input file variable
	Bufferblock* LRUPool;		//array of buffer blocks = buffer pool

public:

	//default constructor initializes data members to base values
	LRUBufferPool()
	{
		buffPoolSize = 0;
		buffBlockSize = BLOCKSIZE;
		LRUPool = new Bufferblock[POOL_SIZE];
	}

	//multi-arg Constructor gets the filename of the file to be buffered,
	//opens the file, and instantiates poolSize buffer blocks by
	//reading the file and filling the blocks in order.  When the constructor
	//is done the buffer pool blocks should be full with the beginning
	//contents of the input file.
	LRUBufferPool(string filename, int poolSize = 5, int blockSize = 4096)
	{
		buffPoolSize = poolSize;											//set pool size
		buffBlockSize = blockSize;											//set block size
		inputFile.open(filename.c_str(), fstream::in | fstream::binary);	//open file for data in binary form
		LRUPool = new Bufferblock[poolSize];								//initialze buffer pool with size

		//loop until pool size for first blocks of file
		for (int c = 0; c < poolSize; c++)
		{
			char* inputData = new char[blockSize];					//create char* array for input
			inputFile.seekg(c * blockSize);							//seek in file for block proper read position
			inputFile.read(inputData, blockSize);					//read file into inputData from file from position
			LRUPool[c] = Bufferblock(inputData, c, blockSize);		//store id, inputData, and blocksize in new block
		}

	}
	
	//deconstructor
	~LRUBufferPool() 
	{
		inputFile.close();	//close file
		delete[] LRUPool;	//delete pool
	}

	// Copy "sz" bytes from position "pos" of the buffered
	//   storage to "space".
	void getBytes(char* space, int sz, int pos)
	{
		int id = pos / buffBlockSize;		//find id of block to get bytes from
		int loc = pos % buffBlockSize;		//find location to read in buffer block
		Bufferblock newBlock;				//empty buffer block 
		Bufferblock temp;					//buffer block for temp
		int index = -1;						//index at -1 for searchin

		//see if block we want is already in the pool
		for (int c = 0; c < buffPoolSize; c++)			//loop through pool
		{
			if (LRUPool[c].getID() == id)				//if id we want is already in the pool
			{
				index = c;								//index is that block
			}
		}

		//check if block is already present
		if (index >= 0)						//if index is positve it was set (not -1)
		{
			newBlock = LRUPool[index];		//block set to what we want to read at index in pool
		}
		else								//if block is not already in the pool
		{
			char* inputData = new char[buffBlockSize];				//make char* array for input
			inputFile.seekg(id * buffBlockSize);					//seek in file for block proper read position
			inputFile.read(inputData, buffBlockSize);				//read file into inputData from file from position
			newBlock = Bufferblock(inputData, id, buffBlockSize);	//store id, inputData, and blocksize in new block
		}

		newBlock.getData(loc, sz, space);	//get data from the block we made or identified

		//LRU heuristic
		if (index >= 0)									//if block was already in the pool
		{
			temp = LRUPool[index];						//block we found copied as temp

			for (int c = index; c < buffPoolSize; c++)	//from index loop through pool
			{
				if (c + 1 < buffPoolSize)				//if element can be moved up
				{
					LRUPool[c] = LRUPool[c + 1];		//move element up
				}
			}
			LRUPool[buffPoolSize - 1] = temp;			//set found block to back
		}
		else											//if the block was added
		{
			LRUPool[buffPoolSize - 1] = newBlock; 		//assign new block to back
		}

		temp = LRUPool[0];								//temp holds front of pool
		LRUPool[0] = LRUPool[buffPoolSize - 1];			//LRU block in back is now front of the pool

		for (int c = buffPoolSize - 1; c > 1; c--)		//loop through the pool from back
		{
			LRUPool[c] = LRUPool[c - 1];				//move elements down
		}
		LRUPool[1] = temp;								//place temp into proper place, 2nd position
		//LRU structure complete
	}

	// Print the order of the buffer blocks using the block id numbers.
	void printBufferBlockOrder()
	{
		//loop through buffer pool
		for (int c = 0; c < buffPoolSize; c++)
		{
			std::cout << LRUPool[c].getID() << ' ';	//print id's of blocks in the pool
		}
		std::cout << "\n";	//newline for formatting
	}

	// Get the block id number of the least recently used buffer block.
	int getLRUBlockID()
	{
		return LRUPool[buffPoolSize].getID();
	}
};
