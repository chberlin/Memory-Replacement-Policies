#include "RepPolicies.h"


RepPolicies::RepPolicies(int maxMemory){
	this->maxMemory =maxMemory;
}

double RepPolicies::Optimal(vector<int> pages){
	//We can modulate this. But, holy BIG oh Batman!!
	int miss = 0;
	int hit = 0;
	list<int> memory;
	for(int page: pages){
		if(find(memory.begin(), memory.end(), page) != memory.end()){
			hit++;
		}
		else{
			int maxArray[maxMemory];
			for(auto const& i : memory){
				for(int j = 0; j < pages.size(); j++){
					if(i == j){
						maxArray[i] = j;
						break;
					}
				}
			}
			int maxPage = 0;
			for(int q = 0; q < maxMemory; q++){
				if(maxArray[q] > maxPage){
					maxPage = q;
				}
			}
			list<int>::iterator iter = find(memory.begin(), memory.end(), maxPage);
			memory.erase(iter);
			memory.push_front(page);
			miss++;
		}
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

double RepPolicies::hitRate(int hit, int miss){
	return (double(hit)/ double(hit + miss));
}