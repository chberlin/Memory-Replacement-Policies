#include "PageGenerate.h"
#include "RepPolicies.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

string toString(double value);

void makeCSVFile(string fileName, const vector<int> & pages, RepPolicies memory);

int main(){
	PageGenerate disk = PageGenerate();
	vector<int> noLocality = disk.generateNoLocality();
	vector<int> _8020 = disk.generate8020();
	vector<int> looping = disk.generateLooping();
	RepPolicies memory = RepPolicies();

	//print statements for debugging.
	//memory.setMaxMemory(5); 
	/*cout << "Optimal No-Locality " << memory.optimal(noLocality) << endl;
	cout << "Optimal 8020 " << memory.optimal(_8020) << endl;
	cout << "Optimal looping " << memory.optimal(looping) << endl;

	cout <<"FIFOPolicy noLocality " << memory.FIFOPolicy(noLocality) << endl;
	cout <<"FIFOPolicy 8020 " << memory.FIFOPolicy(_8020) << endl;
	cout <<"FIFOPolicy looping " << memory.FIFOPolicy(looping) << endl;

	cout <<"RandomPolicy No-Locality " << memory.randomPolicy(noLocality) << endl;
	cout <<"RandomPolicy 8020 " << memory.randomPolicy(_8020) << endl;
	cout <<"RandomPolicy looping " << memory.randomPolicy(looping) << endl;

	cout <<"LRU No-Locality " << memory.LRU(noLocality) << endl;
	cout <<"LRU 8020 " << memory.LRU(_8020) << endl;
	cout <<"LRU looping " << memory.LRU(looping) << endl;

	cout <<"Clock No-Locality " << memory.clock(noLocality) << endl;
	cout <<"Clock 8020 " << memory.clock(_8020) << endl;
	cout <<"Clock looping " << memory.clock(looping) << endl;*/

	makeCSVFile("No-Locality.csv", noLocality, memory);
	makeCSVFile("8020.csv", _8020, memory);
	makeCSVFile("Loop.csv", looping, memory);

	return 0;
}

void makeCSVFile(string fileName, const vector<int> & pages, RepPolicies memory){
	std::ofstream myfile;
	myfile.open(fileName);
	cout << fileName << endl;
	double opt;
	double lru;
	double fifo;
	double rand;
	double clock;

	myfile << "#" + fileName + ", OPT, LRU, FIFO, RAND, CLOCK \n";
	for(int i = 5; i <= 100; i++){
		if( i % 5 == 0){
			memory.setMaxMemory(i);
			opt = memory.optimal(pages);
	 		lru = memory.LRU(pages); 
			fifo = memory.FIFOPolicy(pages);
			rand = memory.randomPolicy(pages);
			clock = memory.clock(pages);
			myfile << i << "," << opt << "," << lru << "," << fifo << "," << rand << "," << clock << endl;
		}
	}
	myfile.close();
}

string toString(double value){
	stringstream strs;
	strs << value;
	string str = strs.str();
	return str;

}
	
			
