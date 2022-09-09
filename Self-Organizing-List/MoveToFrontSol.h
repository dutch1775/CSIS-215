#pragma once

#include "SelfOrderedList.h"
#include "llist.h"

template <typename E>
class MoveToFrontSOL : SelfOrderedList<E>
{
private:
    int comps = 0;      //number of comparisons
    LList<E> MTF_List;  //move to front linked list

public:
    //constructor and destructor
    MoveToFrontSOL() {}
    ~MoveToFrontSOL() {}

    //Look for 'it'.  If found return true and execute the self-ordering
    //heuristic used for ordering the list: count, move-to-front, or transpose.
    //Increments the compare instance variable every time it compares 'it' to
    //other members of the list. Returns true if 'it' is found.
    bool find(const E& it)
    {
        bool isFound{ false };      //is item in list
        MTF_List.moveToStart();     //go to start of the list

        for (int C = 0; C < size(); C++)    //loop through the list
        {
            comps++;    //increment comparisons for every loop
            if (it == MTF_List.getValue())  //if value we are looking for is in the list
            {
                MTF_List.setFrequency(MTF_List.getFrequency() + 1); //increase frequncy for that node
                reorder();  //implement heuristic
                isFound = true; //item was found
                break; //break loop
            }
            MTF_List.next();    //move to next link
        }

        if (!isFound)   //if item was not found
        {
            add(it);    //add the item to the list
            reorder();  //reorder list using heuristic
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
        MTF_List.append(it);
    }

    int getCompares() const   //Returns the number of accumulated compares
    {
        return comps;
    }

    int size() const       //Returns the size of the list
    {
        return MTF_List.length();
    }

    //Print the list
    //In order print of the list.  printlist() prints the entire list
    //whereas printlist(n) prints n nodes.
    void printlist()
    {
        MTF_List.print();
    }

    void printlist(int n)
    {
        MTF_List.print(n);
    }

    //move-to-front heuristic reorder
    void reorder() 
    {
        //if list is empty or has 1 element return
        if (MTF_List.isEmpty())
        {
            return;
        }
        else
        {
            //in temp variables hold frequency and value of the found node and remove the node
            int tempFreq = MTF_List.getFrequency();
            E temp = MTF_List.remove();

            //move to start of the list
            MTF_List.moveToStart();

            //re insert found element at the front of the list
            MTF_List.insert(temp);
            MTF_List.setFrequency(tempFreq);

            return;
        }
    }
};