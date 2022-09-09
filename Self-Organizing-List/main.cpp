#include <string>
#include <fstream>
#include "CountSOL.h"
#include "MoveToFrontSol.h"
#include "TransposeSOL.h"

using namespace std;

int main()
{
	cout << "Michael Dutchin - CSIS 215 Lab 4: Self Ordered List \n\n";

	// char test arrays
	char inserts[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H' };
	char finds[] = { 'F', 'D', 'F', 'G', 'E', 'G', 'F', 'A', 'D', 'F', 'G', 'E', 'H', 'I'};

	// CHAR TEST
	CountSOL<char> countList;		//count list
	MoveToFrontSOL<char> mtfList;	//move to front list
	TransposeSOL<char> tList;		//transpose list

	//loop through insert array add elements to lists
	for (int C = 0; C < 8; C++)
	{
		countList.add(inserts[C]);
		mtfList.add(inserts[C]);
		tList.add(inserts[C]);
	}

	//print start list, will be same for all
	cout << "My starting list structure for all heuristics is: \n";
	countList.printlist();
	cout << "\n \n";

	//loop through find array, each list will handle differently based on heuristic
	for (int C = 0; C < 14; C++)
	{
		countList.find(finds[C]);
		mtfList.find(finds[C]);
		tList.find(finds[C]);
	}

	//char test count test
	cout << "Count Heuristic: \n";
	cout << "The number of compares is: " << countList.getCompares() << "\n";
	cout << "My final list structure with frequencies is: \n";
	countList.printlist();
	cout << "\nMy list size is: " << countList.size() << "\n\n";

	//char test move to front test
	cout << "Move-to-front Heuristic: \n";
	cout << "The number of compares is: " << mtfList.getCompares() << "\n";
	cout << "My final list structure with frequencies is: \n";
	mtfList.printlist();
	cout << "\nMy list size is: " << mtfList.size() << "\n\n";

	//char test transpose test
	cout << "Transpose Heuristic: \n";
	cout << "The number of compares is: " << tList.getCompares() << "\n";
	cout << "My final list structure with frequencies is: \n";
	tList.printlist();
	cout << "\nMy list size is: " << tList.size() << "\n\n\n\n";

	// STRING TEST
	CountSOL<string> sCountList;		//string count list
	MoveToFrontSOL<string> sMtfList;	//string move to front list
	TransposeSOL<string> sTList;		//string transpose list

	ifstream inFile;			//var for file to open
	inFile.open("test.txt");	//open file
	string word;				//word placeholder var

	//loop through file and find word in the file to list
	while (inFile >> word) 
	{
		sCountList.find(word);
		sMtfList.find(word);
		sTList.find(word);
	}

	//string test count test
	cout << "Count Heuristic: \n";
	cout << "The number of compares is: " << sCountList.getCompares() << "\n";
	cout << "My final list structure with frequencies is: \n";
	sCountList.printlist(10);
	cout << "\nMy list size is: " << sCountList.size() << "\n\n";

	//string test move to front test
	cout << "Move-to-front Heuristic: \n";
	cout << "The number of compares is: " << sMtfList.getCompares() << "\n";
	cout << "My final list structure with frequencies is: \n";
	sMtfList.printlist(10);
	cout << "\nMy list size is: " << sMtfList.size() << "\n\n";

	//string test transpose test
	cout << "Transpose Heuristic: \n";
	cout << "The number of compares is: " << sTList.getCompares() << "\n";
	cout << "My final list structure with frequencies is: \n";
	sTList.printlist(10);
	cout << "\nMy list size is: " << sTList.size() << "\n\n";

	system("Pause");
	return 0;
}