#pragma once

#include "SelfOrderedListADT.h"
#include "llist.h"

template <typename E>
class SelfOrderedList : SelfOrderedListADT<E>
{
private:
	int comps = 0;      //number of comparisons
	LList<E> SOL_List;  //linked list

public:
    //constructor and destructor
    SelfOrderedList() {}
    ~SelfOrderedList() {}

    //Look for 'it'.  If found return true and execute the self-ordering
    //heuristic used for ordering the list: count, move-to-front, or transpose.
    //Increments the compare instance variable every time it compares 'it' to
    //other members of the list. Returns true if 'it' is found.
    bool find(const E& it)
    {
        bool isFound{ false };      //is item in list
        SOL_List.moveToStart();     //go to start of the list

        for (int C = 0; C < size(); C++)    //loop through the list
        {
            comps++;    //increment comparisons for every loop
            if (it == SOL_List.getValue())  //if value we are looking for is in the list
            {
                SOL_List.setFrequency(SOL_List.getFrequency() + 1); //increase frequncy for that node
                reorder();  //implement heuristic
                isFound = true; //item was found
                break; //break loop
            }
            SOL_List.next();    //move to next link
        }

        if (!isFound)   //if item was not found
        {
            add(it);    //add the item to the list
        }

        return isFound; //return if item was found
    }

    //Called by find if 'it' is not in the list. Adds the new 'it' to the list
    //Can also be called independently when initially loading the list with
    //unique values and when you want to load the list in the order 'it' is 
    //read without your re-order method being called (or the number of compares
    //being incremented.
    void add(const E& it)  //Add new 'it' to the list
    {
        SOL_List.append(it);
    }

    int getCompares() const   //Returns the number of accumulated compares
    {
        return comps;
    }

    int size() const       //Returns the size of the list
    {
        return SOL_List.length();
    }

    //Print the list
    //In order print of the list.  printlist() prints the entire list
    //whereas printlist(n) prints n nodes.
    void printlist()
    {
        SOL_List.print();
    }

    void printlist(int n)
    {
        SOL_List.print(n);
    }

    void reorder() {}
};