#ifndef pagegenerate_
#define pagegenerate_
#include <cassert>
#include <string>
#include <fstream>
#include <sstream>
#include<iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;



class PageGenerate{
public:
	PageGenerate();
	//Default constructor

	bool setNumPages(int newValue);
	//setter to modify numPages data member

	bool setminInt(int newValue);
	//setter to modify minInt data member

	bool setmaxInt(int newValue);
	//setter to modify maxInt data member


	vector<int> generateNoLocality();
	//behavior: makes unsorted numPages of values between minInt and maxInt

	vector<int> generate8020();
	//behavior: Makes values 0-19 repersent 80% of elments. Values 20-99 repersent 20%
	//Output: returns unsorted vector of ints with 80% of values containing elements 0-19. 20% containing 20-99

	vector<int> generateLooping();
	//output: Makes page vector with values that start at 0 and go to maxInt(unique page numbers), then repeats
	//example: [0,1,2,3,0,1,2,3,0,1,2,3]

private:
	int numPages;
	//Number of Pages to read in
	int minInt;
	//Minimum number of pages to read in
	int maxInt;
	//Maximum number of pages
};
#endif
