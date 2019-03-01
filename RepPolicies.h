#ifndef reppolicies_
#define reppolicies_
#include <list>
#include <algorithm>
#include <random>
#include <iterator>

using namespace std;

class RepPolicies{
public:
	RepPolicies(int maxMemory);
	//input: size of memory cache

	double Optimal(vector<int> pages);
	//input: vector containing pages as ints
	//behavior: On miss with full memory, replaces element in memory cache that will be the furthest away
	//output: hitrate

	double FIFOPolicy(vector<int> pages);
	//input: vector containing pages as ints
	//behavior: On miss with full memory, replaces element that came in first

	double randomPolicy(vector<int> pages);
	//input: vector containing pages as ints
	//behavior: on miss with full memory, replaces element from memory at random

private:

	double hitRate(int hit, int miss);
	//Helper function
	//input: number of hits
	//inpiut: number of misses
	//output: hitrate (hit/ (hit+miss));
	int maxMemory;
};
#endif