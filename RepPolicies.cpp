#include "RepPolicies.h"


RepPolicies::RepPolicies(int maxMemory){
	this->maxMemory = maxMemory;
	this->voidValue = 99999;
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

	struct pagestruct {

		int page_num;
		int reference_bit;

	}; 

	// create a list of pagestruct objects fro the input pages list
	vector<pagestruct> all_pages;

	for (int x : pages) {

		// populate a struct with the proper values
		pagestruct page;
		page.page_num = x;
		page.reference_bit = 0; // should I initialize all of these as 0 or 1?

		// once initialized, add the pagestruct to the vector of pagestruct structures
		all_pages.push_back(page);

	}

	int hit = 0, miss = 0;
	int memory[maxMemory];
	int memorySize = 0; // this value shows how full/not full the memory Array is
	initalizeMemoryArray(memory);
	bool found_page = false;

	// We need to go thru each page reference in the stream to check if we have
	// the page in memory or not and act accordingly
	for (int ii = 0; ii < all_pages.size(); ii++) {

		// if the page that we currently need is already in memory
		if (inMemory(memory, pages[i])) {
			hit += 1;
		}

		// If we are in this block, then we know that the needed page is not in memory (the cache)
		// There are a number of actions we could take
		else {

			// First let's see if there is more space left in memory
			if (memorySize < maxMemory) {
				// if, so then all we need to do is add the pagestruct to the next open spot in memory
				memory[memorySize] = pages[i];
			}

			// If memory is full then we need to make an eviction
			else {

				bool found_page = false;
				int counter = 0;
				int index;	
				pagestruct current_page;
			
				while (!found_page) {

					index = counter % all_pages.size();

					current_page = all_pages[index];
					if (current_page.reference_bit = 0) {
						// Then stop the traversal and just use this current page as a victim

						// HANDLE THIS!!!!!					

					}

					else { // the only other case is that the reference bit is set to 1
						// Just set the ref bit to 0 and move on looking for another page
						// If nothing else, this page can be used again in the next go around
						current_page.reference_bit = 0;
					}

					counter += 1;
	
				}


			}

			// Since this was a miss, we incremement the miss counter
			// We incremement the miss value here because even if we miss due to the 
			// cache (memory) not yet being full it still counts as a miss
			miss += 1;


		}

	}
	

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
