#pragma once

#include "SelfOrderedList.h"
#include "llist.h"

template <typename E>
class CountSOL : SelfOrderedList<E>
{
private:
    int comps = 0;          //number of comparisions
    LList<E> Count_List;    //linked list for count SOL

public:
    //constructor and destructor
    CountSOL() {}
    ~CountSOL() {}

    //Look for 'it'.  If found return true and execute the self-ordering
    //heuristic used for ordering the list: count, move-to-front, or transpose.
    //Increments the compare instance variable every time it compares 'it' to
    //other members of the list. Returns true if 'it' is found.
    bool find(const E& it)
    {
        bool isFound{ false };      //is item in list
        Count_List.moveToStart();     //go to start of the list

        for (int C = 0; C < size(); C++)    //loop through the list
        {
            comps++;    //increment comparisons for every loop
            if (it == Count_List.getValue())  //if value we are looking for is in the list
            {
                Count_List.setFrequency(Count_List.getFrequency() + 1); //increase frequncy for that node
                reorder();  //implement heuristic
                isFound = true; //item was found
                break; //break loop
            }
            Count_List.next();    //move to next link
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
        Count_List.append(it);
    }

    int getCompares() const   //Returns the number of accumulated compares
    {
        return comps;
    }

    int size() const       //Returns the size of the list
    {
        return Count_List.length();
    }

    //Print the list
    //In order print of the list.  printlist() prints the entire list
    //whereas printlist(n) prints n nodes.
    void printlist()
    {
        Count_List.print();
    }

    void printlist(int n)
    {
        Count_List.print(n);
    }

    //reroder the listed based on count heuristic
    void reorder() 
    {
        //if only 1 or no element in list return
        if (Count_List.isEmpty())
        {
            return;
        }
        else
        {
            int tempFreq = Count_List.getFrequency();   //temp variable holding frequncy of found node
            E temp = Count_List.remove();   //temp variable of type E holding element of found node
            //remove found node

            Count_List.moveToStart();   // move to start of the list

            for (int C = 0; C < size(); C++)    //loop through the list
            {
                if (Count_List.getFrequency() >= tempFreq)  //if the frequency of the found node is less
                {
                    Count_List.next(); //go to next node
                }
                else //if node is greater
                {
                    //re-insert the found node
                    Count_List.insert(temp);    
                    Count_List.setFrequency(tempFreq);

                    return;
                }
            }
        }
    }
};
