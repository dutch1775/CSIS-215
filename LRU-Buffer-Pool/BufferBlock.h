#pragma once

#include "BufferBlockADT.h"

class Bufferblock : public BufferblockADT
{
private:
    //Instance variables:
    int blockID;        //id of block
    char* blockData;    //data that buffer block holds
    int size;           //size of the buffer block

public:

    //sz is the size of the character array data
    //points to.
    //default constructor sets variables to zero or null
    Bufferblock()
    {
        blockData = nullptr;
        blockID = 0;
        size = 0;
    }

    //multi-arg constructor initializes buffer block data members
    Bufferblock(char* data, int id, int sz = 4096)
    {
        blockData = data;
        blockID = id;
        size = sz;
    }

    virtual ~Bufferblock() {}

    //read the block from pos to pos + sz-1 (or to the end of the block)
    void getData(int pos, int sz, char* data)
    {
        //end of the block read-in
        int EOB;

        if (pos + sz > size)        //if read size is too large
        {
            EOB = size - 1;         //read to end of the block
        }
        else
        {
            EOB = pos + sz - 1;     //else read from pos + sz -1
        }

        //read data from block unitl EOB
        for (int c = 0; c + pos <= EOB; c++)
        {
            data[c] = blockData[c + pos];
        }
    }

    //setID
    void setID(int id)
    {
        blockID = id;
    }

    //getID
    int getID() const
    {
        return blockID;
    }

    //getBlocksize
    int getBlocksize() const
    {
        return size;
    }

    //return the block
    char* getBlock() const
    {
        return blockData;
    }

    //set the block
    void setBlock(char* blk)
    {
        blockData = blk;
    }
};
