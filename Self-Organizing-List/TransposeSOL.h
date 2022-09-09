#pragma once

#include "SelfOrderedList.h"
#include "llist.h"

template <typename E>
class TransposeSOL : SelfOrderedListADT<E>
{
private:
    int comps = 0;
    LList<E> Transpose_List;

public:
    TransposeSOL() {}

    ~TransposeSOL() {}

    //Look for 'it'.  If found return true and execute the self-ordering
    //heuristic used for ordering the list: count, move-to-front, or transpose.
    //Increments the compare instance variable every time it compares 'it' to
    //other members of the list. Returns true if 'it' is found.
    bool find(const E& it)
    {
        bool isFound{ false };      //is item in list
        Transpose_List.moveToStart();     //go to start of the list

        for (int C = 0; C < size(); C++)    //loop through the list
        {
            comps++;    //increment comparisons for every loop
            if (it == Transpose_List.getValue())  //if value we are looking for is in the list
            {
                Transpose_List.setFrequency(Transpose_List.getFrequency() + 1); //increase frequncy for that node
                reorder();  //implement heuristic
                isFound = true; //item was found
                break; //break loop
            }
            Transpose_List.next();    //move to next link
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
        Transpose_List.append(it);
    }

    int getCompares() const   //Returns the number of accumulated compares
    {
        return comps;
    }

    int size() const       //Returns the size of the list
    {
        return Transpose_List.length();
    }

    //Print the list
    //In order print of the list.  printlist() prints the entire list
    //whereas printlist(n) prints n nodes.
    void printlist()
    {
        Transpose_List.print();
    }

    void printlist(int n)
    {
        Transpose_List.print(n);
    }

    //reorder list using tranpose heurisitc
    void reorder() 
    {
        //if list is empty for has 1 element return
        if (Transpose_List.isEmpty())
        {
            return;
        }
        else
        {
            // in temp variables get frequency, value, and position of the found node
            //then delete node
            int tempFreq = Transpose_List.getFrequency(); 
            int pos = Transpose_List.currPos();
            E temp = Transpose_List.remove();

            //move to the node infront of the found node
            Transpose_List.moveToPos(pos - 1);

            //re-insert found node
            Transpose_List.insert(temp);
            Transpose_List.setFrequency(tempFreq);

            return;
        }
        }
};
