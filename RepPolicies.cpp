#include "RepPolicies.h"


RepPolicies::RepPolicies(int maxMemory){
	this->maxMemory = maxMemory;
	this->voidValue = 9999;
}

bool RepPolicies::setMaxMemory(int newSize){
	if(newSize < 1){
		cout << "Error: Memory needs to have a size" << endl;
		return false;
	}
	else{
		this->maxMemory = newSize;
		return true;
	}
}

double RepPolicies::optimal(vector<int> pages){
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
					maxArray[m] = findDistanceToNextCall(pages, i, memory[m]);
					//cout << maxArray[m] << endl;
				}
				int victimIndex = findMaxIndex(maxArray);
				memory[victimIndex] = pages.at(i);
			}
			miss++;
		}
		//cout << "-------------------" << endl;
		//	for(int j = 0; j < maxMemory; j++){
		//	cout << memory[i] << endl;
		//}
	}
	return hitRate(hit, miss);
}

double RepPolicies::FIFOPolicy(vector<int> pages){
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

double RepPolicies::randomPolicy(vector<int> pages){
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
double RepPolicies::LRU(vector<int> pages){
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
					maxArray[m] = findDistanceToLastCall(pages, i, memory[m]);
					//cout << maxArray[m] << endl;
				}
				memory[findMaxIndex(maxArray)] = pages.at(i);
			}
			miss++;
		}
		//cout << "-------------------" << endl;
		//for(int j = 0; j < maxMemory; j++){
		//	cout << memory[i] << endl;
		//}
	}
	return hitRate(hit, miss);
}
int RepPolicies::findDistanceToLastCall(const vector<int> &pages, int start, int value){
	for(int i = start; i >= 0; i--){
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
	//cout << endl;
	return max;
}
bool RepPolicies::inMemory(int *memory, int value){
	for(int i = 0; i < maxMemory; i++){
		if(memory[i] == value && memory[i] != -1){
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