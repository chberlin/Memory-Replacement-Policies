#include "RepPolicies.h"


RepPolicies::RepPolicies(){
	this->maxMemory = 0;
	this->voidValue = 99999;
}

bool RepPolicies::setMaxMemory(int newSize){
	if(newSize < 0){
		cout << "Error: Memory needs to have a size" << endl;
		return false;
	}
	else{
		this->maxMemory = newSize;
		return true;
	}
}

double RepPolicies::optimal(const vector<int> pages){
	int miss = 0;
	int hit = 0;
	int memory[maxMemory];
	int memorySize = 0;
	intalizeMemoryArray(memory);
	int i;
	for(i = 0; i < pages.size(); i++){
		if(inMemory(memory, pages.at(i))){
			hit++;
		}
		else{
			//memory isn't full. Add to Memory
			if(memorySize < maxMemory){
				memory[memorySize] = pages.at(i);
				memorySize++;
			}
			else{
				//Check for victim that will be called furthest away
				int maxArray[maxMemory];
				for(int m = 0; m < memorySize; m++){
					maxArray[m] = findDistanceToNextCall(pages, i+1, memory[m]);
				}
				int victimIndex = findMaxIndex(maxArray);
				memory[victimIndex] = pages.at(i);
			}
			miss++;
		}
		/*cout << "-------------------" << endl;
		cout<<"[";
			for(int j = 0; j < maxMemory; j++){
				cout << memory[j] << ", ";
			}
			cout << "]"<< endl;*/
	}	
	return hitRate(hit, miss);
}

double RepPolicies::FIFOPolicy(const vector<int> pages){
	int miss = 0;
	int hit = 0;
	list<int> memory;
	for(int page : pages){
		if(find(memory.begin(), memory.end(), page) != memory.end()){
			hit++;
		}
		else{
			if(memory.size() < maxMemory){
				memory.push_front(page);
			}
			else{
				memory.pop_back();
				memory.push_front(page);
			}
			miss++;
		}
	}
	return hitRate(hit, miss);
}

double RepPolicies::randomPolicy(const vector<int> pages){
	int miss = 0;
	int hit = 0;
	int memory[maxMemory];
	int memorySize = 0;
	for(int i = 0; i < pages.size(); i++){
		if(inMemory(memory, pages.at(i))){
			hit++;
		}
		else{
			if(memorySize < maxMemory){
				memory[memorySize] = pages.at(i);
				memorySize++;
			}
			else{
				int randVal = rand() % (maxMemory);
				memory[randVal] = pages.at(i);
			}
			miss++;
		}
	}
	return hitRate(hit, miss);
}


double RepPolicies::LRU(const vector<int> pages){
	int miss = 0;
	int hit = 0;
	int memory[maxMemory];
	int memorySize = 0;
	intalizeMemoryArray(memory);
	//int count = 0;
	/*for(int j : pages){
		if(count % 10 == 0){
			cout << endl;
		}
		cout << j << " ";
		count++;
	}*/
	int i;
	for(i = 0; i < pages.size(); i++){
		if(inMemory(memory, pages.at(i))){
			hit++;
		}
		else{
			//memory isn't full. Add to Memory
			if(memorySize < maxMemory){
				memory[memorySize] = pages.at(i);
				memorySize++;
			}
			else{
				//Check for victim that was called furthest away
				int maxArray[maxMemory];
				for(int m = 0; m < memorySize; m++){
					maxArray[m] = findDistanceToLastCall(pages, i, memory[m]);
				}
				int victimIndex = findMaxIndex(maxArray);
				//cout << "New entry: " << pages.at(i) << " Victim: " << memory[victimIndex] << endl;
				memory[victimIndex] = pages.at(i);
			}
			miss++;
		}
		/*cout << "-------------------" << endl;
		cout<<"[";
			for(int j = 0; j < maxMemory; j++){
				cout << memory[j] << ", ";
			}
			cout << "]"<< endl;*/
	}	
	return hitRate(hit, miss);
}
double RepPolicies::clock(const vector<int> pages){
	//set to remove duplicates
	set<int> s;
	for( int i = 0; i < pages.size(); i++ ){
		s.insert(pages.at(i));
	}
	//Map:
	//Key: Int value from pages
	//Value: Use bit
	map<int, int> pageMap;
	for(int value : s){
		pageMap.insert(pair<int, int>(value, 0));
	}

	int miss = 0;
	int hit = 0;
	int memory[maxMemory];
	int memorySize = 0;
	intalizeMemoryArray(memory);
	int i;
	for(i = 0; i < pages.size(); i++){
		if(inMemory(memory, pages.at(i))){
			hit++;
			pageMap[pages.at(i)] = 1;
		}
		else{
			//memory isn't full. Add to Memory
			if(memorySize < maxMemory){
				memory[memorySize] = pages.at(i);
				memorySize++;
			}
			else{
				int victimIndex = 0;
				for(int m = 0; m < memorySize; m++){
					if(pageMap[memory[m]] == 0){
						victimIndex = m;
						break;
					}
					else if(pageMap[memory[m]] == 1){
						pageMap[memory[m]] = 0;
					}
				}
				memory[victimIndex] = pages.at(i);
			}
			miss++;
		}
		/*cout << "-------------------" << endl;
		cout<<"[";
			for(int j = 0; j < maxMemory; j++){
				cout << memory[j] << ", ";
			}
			cout << "]"<< endl;*/
	}
	return hitRate(hit, miss);
}

int RepPolicies::findDistanceToLastCall(const vector<int> &pages, int start, int value){
	for(int i = start; i >= 0; --i){
		if(pages.at(i) == value){
			return (i);
		}
	}
	return voidValue;//Indicates value is not going to be called again, so should be victim. Return value greater than range of pages
}

int RepPolicies::findDistanceToNextCall(const vector<int> &pages, int start, int value){
	for(int i = start; i < pages.size(); i++){
		if(pages.at(i) == value){
			return (i-start);
		}
	}
	return voidValue;//Indicates value is not going to be called again, so should be victim. Return value greater than range of pages
}

double RepPolicies::hitRate(int hit, int miss){
	return (double(hit)/ (double(hit) + miss));
}
int RepPolicies::findMaxIndex(int maxArray[]){
	int max = 0;
	for(int i = 0; i < maxMemory; i++){
		//cout << maxArray[i] << " , ";
		if (maxArray[i] > maxArray[max]){
			max = i;
		}
	}
	return max;
}
bool RepPolicies::inMemory(int *memory, int value){
	for(int i = 0; i < maxMemory; i++){
		if(memory[i] == value && memory[i]){
			return true;
		}
	}
	return false;
}
void RepPolicies::intalizeMemoryArray(int *memory){
	for(int i = 0; i < maxMemory; i++){
		memory[i] = voidValue;
	}
}

// In a given array, memory, find the index of the given value
int RepPolicies::indexByValue(int * memory, int value) {

	for (int ii = 0; ii < maxMemory; ii++) {
		if (memory[ii] == value) {
			return ii;
		}
	}
	// This is the case in which we didn't find the value in the array,
	// which shouldn't happen due to the checks that happen before this
	// function would be called
	return -1;

}

