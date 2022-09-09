#include "BST.h"
#include "book.h"
#include <iostream>

void wait();

int main()
{
	std::cout << "Michael Dutchin -- CSIS 215 Programming Assignment 2 -- Threaded Binary Tree" << std::endl;

	//make BTBST
	BST<int, string> testBST;

	//insert nodes into the tree
	std::cout << "Testing the insert function to build my tree.";
	testBST.insert(77, "seventy-seven");
	testBST.insert(70, "seventy");
	testBST.insert(75, "seventy-five");
	testBST.insert(66, "sixty-six");
	testBST.insert(79, "seventy-nine");
	testBST.insert(68, "sixty-eight");
	testBST.insert(67, "sixty-seven");
	testBST.insert(69, "sixty-nine");
	testBST.insert(90, "ninety");
	testBST.insert(85, "eighty-five");
	testBST.insert(83, "eighty-three");
	testBST.insert(87, "eighty-seven");
	testBST.insert(65, "sixty-five");
	std::cout << "\n";

	//test size
	std::cout << "The BST tree size is " << testBST.size() << "\n\n";

	//test print
	std::cout << "Testing the print function to see the tree's structure (testing printHelp changes):" << "\n";
	testBST.print();
	std::cout << "\n";

	//test inorder
	std::cout << "Inorder print function (testing right threads and printInorder() function):" << "\n";
	testBST.printInorder();
	std::cout << "\n";

	//test reverse
	std::cout << "Reverse print function (testing left threads and printReverse() function):" << "\n";
	testBST.printReverse();
	std::cout << "\n";

	wait();
	return 0;
}

//Used to pause the screen wherever desired
void wait()
{
	//The following if-statement checks to see how many characters are in cin's buffer
	//If the buffer has characters in it, the clear and ignore methods get rid of them.
	if (cin.rdbuf()->in_avail() > 0) //If the buffer is empty skip clear and ignore
	{
		cin.clear();
		cin.ignore(256, '\n'); //Clear the input buffer 
	}
	char ch;
	cout << "Press the Enter key to continue ... ";
	cin.get(ch);
}