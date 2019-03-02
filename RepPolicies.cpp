#include "RepPolicies.h"


RepPolicies::RepPolicies(int maxMemory){
	this->maxMemory = maxMemory;
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
	int i;
	for(i = 0; i < pages.size(); i++){
		if(inMemory(memory, pages.at(i))){
			hit++;
			cout << "Page: " << pages.at(i) << endl;
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
				for(int m = 0; m < maxMemory; m++){
					maxArray[m] = findDistanceToNextCall(pages, pages.at(i), memory[m]);
				}
				memory[findMaxIndex(maxArray)] = pages.at(i);
			}
			miss++;
		}
		/*for(int c = 0; c < maxMemory; c++){
			cout << memory[c] << endl;
		}
		cout << "--------------------" << endl;*/
	}
	cout << "hits: " << hit << endl;
	cout << "misses: " << miss << endl;
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
				int randVal = rand() % (maxMemory);
				list<int>::iterator iter = find(memory.begin(), memory.end(), randVal);
				memory.erase(iter);
				memory.push_front(page);
			}
		miss++;
		}
	}
	return hitRate(hit, miss);
}
int RepPolicies::findDistanceToNextCall(vector<int> pages, int start, int value){
	for(int i = start; i < pages.size(); i++){
		if(pages.at(i) == value){
			return i;
		}
	}
	return -1;
}

double RepPolicies::hitRate(int hit, int miss){
	return (double(hit)/ (double(hit) + miss));
}
int RepPolicies::findMaxIndex(int maxArray[]){
	int max = 0;
	for(int i = 0; i < maxMemory; i++){
		if (maxArray[i] > max){
			max = i;
		}
	}
	return max;
}
bool RepPolicies::inMemory(int memory[], int value){
	for(int i = 0; i < maxMemory; i++){
		cout << "memory: " << memory[i] << " value: " << value << endl;
		if(memory[i] == value){

			cout << "FOUND. HIT REGISTERED!!!!!!" << endl;
			return true;
		}
	}
	return false;
}