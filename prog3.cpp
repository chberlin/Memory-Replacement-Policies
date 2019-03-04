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


	//memory.randomPolicy(noLocality);
	//memory.randomPolicy(_8020);
	//memory.randomPolicy(looping);

	//LRU has not been implemented
	//Clock has not been implemented

	memory.setMaxMemory(10);
	//repeat
	//Makes sense to send these into a function to make a collective array to use for graph. 
	//Need to run all the algorithims with memory size 5 to 100 in increments of 5. 
}