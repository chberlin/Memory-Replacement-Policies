#include "PageGenerate.h"
#include "RepPolicies.h"

int main(){
	PageGenerate disk = PageGenerate();
	vector<int> noLocality = disk.generateNoLocality();
	vector<int> _8020 = disk.generate8020();
	vector<int> looping = disk.generateLooping();

	//Memory size default is 5
	RepPolicies memory = RepPolicies(5);
	cout << "Optimal No-Locality " << memory.optimal(noLocality) << endl;
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
	//Clock has not been implemented

	memory.setMaxMemory(10);
	//repeat
	//Makes sense to send these into a function to make a collective array to use for graph. 
	//Need to run all the algorithims with memory size 5 to 100 in increments of 5. 
}