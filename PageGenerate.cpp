
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
	return pages;



}
vector<int> PageGenerate::generateNoLocalityFILE(string filename){
	vector<int> pages;
	if(!readInputFile(pages, filename)){
		cout << "Error generating vector of pages from file" << endl;
	}
	return pages;
}

/*bool PageGenerate::generate8020(){
	
}*/


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


