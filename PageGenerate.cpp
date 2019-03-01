
#include "PageGenerate.h"

PageGenerate::PageGenerate(){
	numPages = 10000;
	minInt = 0;
	maxInt = 99;
}


vector<int> PageGenerate::generateNoLocalitySTDIN(){
	vector<int> pages;
	if(!readFromStdin(pages)){
		cout << "Error generating vector of pages from stdin" << endl;
	}
	if(pages.size() != numPages){
		cout << "Error: Incomplete pages" << endl;
	}
	return pages;



}
vector<int> PageGenerate::generateNoLocalityFILE(string filename){
	vector<int> pages;
	if(!readInputFile(pages, filename)){
		cout << "Error generating vector of pages from file" << endl;
	}
	if(pages.size() != numPages){
		cout << "Error: Incomplete pages" << endl;
	}
	return pages;
}

vector<int> PageGenerate::generate8020(){
	//Making values 0-19 repersent 80% of pages
	vector<int> pages;
	int hotQuantity = .8 * numPages;
	int i;
	for(i = 0; i < hotQuantity; i++){
		int val = rand()%(20);
		pages.push_back(val);
	}
	while(i < numPages){
		int rVal = rand()%(99-20 + 1) + 20;
		pages.push_back(rVal);
		i++;
	}
	auto rng = default_random_engine {};
	shuffle(begin(pages), end(pages), rng);
	return pages;
}

vector<int> PageGenerate::generateLooping(){
	vector<int> pages;
	int count = 0;
	for(int i = 0; i < numPages; i++){
		if(count > maxInt){
			count = 0;
		}
		pages.push_back(count);
	}
	return pages;
}


bool PageGenerate::readFromStdin(vector<int> &pages){
	string line;
	while(getline(cin, line)) {
		stringstream ss(line);
		if(!line.empty()){
			int value;
			if(value > maxInt || value < minInt){
				cout << "Page number must be between 0 - 99" << endl;
				exit(1);
			}
			int count = 0;
			while(ss >> value && count < numPages){
				pages.push_back(value);
			}
		}
	}
	return true;
}

bool PageGenerate::readInputFile(vector<int> &pages, string inputFileName){
	ifstream ifFile(inputFileName);
	string line;
	if(ifFile.is_open()){
		cout << "Error opening file" << endl;
		exit(1);
		return false;
	}
	else{
		while(getline(ifFile, line)){
			stringstream ss(line);
			if(!line.empty()){
				int value;
				if(value > maxInt || value < minInt){
					cout << "Page number must be between 0 - 99" << endl;
					exit(1);
				}
				int count = 0;
				while(ss >> value && count < numPages){
					pages.push_back(value);
					count++;
				}
			}
		}
	}
	return true;
}


