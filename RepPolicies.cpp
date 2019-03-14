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

double RepPolicies::clock(const vector<int> pages) {

	// the structure that will hold the page number and
	// the bit information (such as use/reference bit) for
	// a given page
	//struct pagestruct {

	//	int page_num;
	//	int reference_bit;

	//}; 

	// create a list of pagestruct objects fro the input pages list
	vector<pagestruct> all_pages;

	// make a pagestruct object for each int in pages and initialize it
	for (int x : pages) {

		// populate a struct with the proper values
		pagestruct page;
		page.page_num = x;
		page.reference_bit = 0; // should I initialize all of these as 0 or 1?

		// once initialized, add the pagestruct to the vector of pagestruct structures
		all_pages.push_back(page);

	}

	cout << "JUST AS A TEST" << endl;

	for (pagestruct p : all_pages) {

	cout << endl;
	cout << p.page_num << " ; " << p.reference_bit << endl;
	cout << endl;

	}

	int hit = 0, miss = 0;
	int memory[maxMemory];
	int memorySize = 0; // this value shows how full/not full the memory Array is
	int curr_pagenum;
	intalizeMemoryArray(memory);
	bool found_page = false;

	// We need to go thru each page reference in the stream to check if we have
	// the page in memory or not and act accordingly
	for (int ii = 0; ii < all_pages.size(); ii++) {

		// We need to look at the page number that we're currently trying to 
		// access and update its reference bit to 1 (since it has been called)
		curr_pagenum = pages[ii];

		for (pagestruct xpage : all_pages) {

			// take every pagestruct with page number that matches curr_pagenum
			// and set it's reference bit to 1 (since it is currently being accessed)
			if (xpage.page_num == curr_pagenum) {
				xpage.reference_bit = 1;
			}

		}

		/* Now we can begin checking if the page we're currently accesssing
		   is in memory (and acting accordingly) */

		// if the page that we currently need is already in memory
		if (inMemory(memory, pages[ii])) {
			hit += 1;
		}

		// If we are in this block (below), then we know that the needed page is not in memory (the cache)
		// There are a number of actions we could take within
		else {

			// First let's see if there is more space left in memory
			if (memorySize < maxMemory) {
				// if, so then all we need to do is add the pagestruct to the next open spot in memory
				memory[memorySize] = pages[ii];
				memorySize += 1;

				cout << "Are we seg faulting?" << endl;
			}

			// If memory is full then we need to make an eviction
			else {

				bool found_page = false;
				int counter = 0;
				int index;	
				int victim_index;
				pagestruct current_page;

				cout << "No, not anymore" << endl;

				while (!found_page) {

					index = counter % maxMemory;
					cout << "index value is " << index << endl;

					cout << "Wait, we're not stuck in this while loop, are we?" << endl;
					cout << "current_page.reference_bit = " << current_page.reference_bit << endl;

					// Find the current page
					for (pagestruct xpage : all_pages) {

						if (xpage.page_num == memory[index]) {
							current_page = xpage;
						}

					}

					// Now, check the current page's reference bit
					if (current_page.reference_bit == 0) {

						cout << "ATTENTION, WE HAVE FOUND A PAGE TO REPLACE" << endl;

						// Then stop the traversal (by setting found_page
						// to true) and just use this current page as a victim
						found_page = true;
						victim_index = indexByValue(memory, current_page.page_num);
						cout << "current page_num: " << current_page.page_num << endl;
						for (int jj = 0; jj < sizeof(memory) / sizeof(int); jj++) {
							cout << memory[jj] << endl;
						}
						cout << "VICTIM INDEX IS " << victim_index << endl;

					}

					// the only other case is that the reference bit is set to 1
					else { 

						cout << "replacement page not yet found, we're working on it" << endl;

						// If so, just set the ref bit to 0 and move on looking for another page
						// If nothing else, this page can be used again in the next go around (which
						// is the worst case scenario)
						// Also, set the found_page bool to true to end the loop
						//found_page = true;
						current_page.reference_bit = 0;
					}

					// Increment the counter so that we can keep going up "around"
					// the list of pages.
					counter += 1;
	
				}

				cout << "We almost were, but not anymore, it's something else." << endl;

				// Once the above while loop is over, we have found our victim index and we
				// can swap it out of memory for the new page that we are currently bringing in
				memory[victim_index] = pages[ii];

				cout << "Is it you?!?!?!?!?!?!?!?!??!" << endl;
				cout << "IT IS, well if you're seeing this, IT WAS!!!!!!!" << endl;

				cout << "VICTIM INDEX (AGAIN, lol) " << victim_index << endl;

			}

			cout << "This is where we seg fault" << endl;
			cout << "yes here" << endl;

			// Since this was a miss, we incremement the miss counter
			// We incremement the miss value here because even if we miss due to the 
			// cache (memory) not yet being full it still counts as a miss
			miss += 1;

			cout << "or.....is it here" << endl;


		}


		cout << "okay, maybe here?" << endl;

	}

	cout << "WAIT WHAT??????" << endl;

	/* For Testing */

	///*
	cout << "-------------------" << endl;
	cout << "[";

	cout << "CLOCK TEST: runtrhough of memory" << endl << endl;
	for(int j = 0; j < maxMemory; j++){
		cout << memory[j] << ", ";
	}

	cout << "]" << endl;
	cout << "-------------------" << endl;
	//*/

	cout << "We getting out of this function, dog" << endl;

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

