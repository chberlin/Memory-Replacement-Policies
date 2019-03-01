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

	vector<int> generateNoLocalitySTDIN();
	//output: vector<int>. Each element repersents value read from stdin

	vector<int> generateNoLocalityFILE(string filename);
	//input: Filename of int values to read in
	//output: vector<int>. Each element repersents value read from file

	vector<int> generate8020();
	//behavior: Makes values 0-19 repersent 80% of elments. Values 20-99 repersent 20%
	//Output: returns unsorted vector of ints with 80% of values containing elements 0-19. 20% containing 20-99

	vector<int> generateLooping();
	//output: Makes page vector with values that start at 0 and go to maxInt(unique page numbers), then repeats
	//example: [0,1,2,3,0,1,2,3,0,1,2,3]

private:
	bool readFromStdin(vector<int> &pages);
	//input: vector to hold pages once read in
	//output: vector containing page values

	bool readInputFile(vector<int> &pages, string inputFileName);
	//input: vector to hold pages once read in
	//input: filename of file to read from
	//output: vector containing page values

	int numPages;
	//Number of Pages to read in
	int minInt;
	//Minimum number of pages to read in
	int maxInt;
	//Maximum number of pages
};
#endif