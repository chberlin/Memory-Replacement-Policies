#include "PageGenerate.cpp"
#include "RepPolicies.cpp"

int main(){
	PageGenerate disk = PageGenerate();

	vector<int> noLocality = disk.generateNoLocalityFILE("numbers.txt");
	vector<int> _8020 = disk.generate8020();
	vector<int> looping = disk.generateLooping();


}