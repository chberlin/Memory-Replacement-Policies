
#include "PageGenerate.h"

PageGenerate::PageGenerate(){
	numPages = 25;
	minInt = 0;
	maxInt = 99;
}

bool PageGenerate::setNumPages(int newValue){
	if(numPages <= 0){
		cout << "Pages must be greater than 0" << endl;
		return false;
	}
	else{
		this->numPages = newValue;
		return true;
	}
}

bool PageGenerate::setminInt(int newValue){
	if(newValue > maxInt || newValue < 0){
		cout << "Invalid min value" << endl;
		return false;
	}
	else{
		this->minInt = newValue;
		return true;
	}
}
bool PageGenerate::setmaxInt(int newValue){
	if(newValue < minInt || newValue < 0){
		cout << "Invalid max value" << endl;
		return false;
	}
	else{
		this->maxInt = newValue;
	}	return true;
}

vector<int> PageGenerate::generateNoLocality(){
	vector<int> pages;
	int randNum;
	for(int i = 0; i < numPages; i++){
		randNum = (rand() % (maxInt - minInt + 1)) + minInt;
		pages.push_back(randNum);
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
		if(count > (maxInt/2)){
			count = 0;
		}
		pages.push_back(count);
		count++;
	}
	return pages;
}