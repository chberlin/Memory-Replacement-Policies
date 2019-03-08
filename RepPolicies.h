#ifndef reppolicies_
#define reppolicies_
#include <list>
#include <iterator>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class RepPolicies{
public:
	RepPolicies();

	bool setMaxMemory(int newSize);
	//setter to change size of memory

	double optimal(const vector<int> pages);
	//input: vector containing pages as ints
	//behavior: On miss with full memory, replaces element in memory cache that will be the furthest away
	//output: hitrate

	double FIFOPolicy(const vector<int> pages);
	//input: vector containing pages as ints
	//behavior: On miss with full memory, replaces element that came in first

	double randomPolicy(const vector<int> pages);
	//input: vector containing pages as ints
	//behavior: on miss with full memory, replaces element from memory at random

	double LRU(const vector<int> pages);
	//input: vector containing pages as ints
	//behavior: on miss with full memory, repalces elemment that was least recently used

	double clock(const vector<int> pages);
	//input: vector containing pages as ints

private:

	double hitRate(int hit, int miss);
	//Helper function
	//input: number of hits
	//inpiut: number of misses
	//output: hitrate (hit/ (hit+miss));

	int findMaxIndex(int maxArray[]);
	//finds maximum element, returns associated index value

	int findDistanceToNextCall(const vector<int> &pages, int start, int value);
	//iterates through pages vector from start position, returns number of iterations until value is found

	bool inMemory(int memory[], int page);
	//checks to see if page value is in memory

	void intalizeMemoryArray(int *memory);
	//initalizes memory with a high number such as 9999

	int findDistanceToLastCall(const vector<int> &pages, int start, int value);
	//iterates through pages vector from start position to beginning, returns number of iterations until value is found

	int indexByValue(int * memory, int value);
	//iterates through memory array and returns index of first entry with contents matching value variable

	int maxMemory;
	int voidValue;
};
#endif
