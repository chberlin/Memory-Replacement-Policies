prog3: PageGenerate.o RepPolicies.o prog3.o
	g++ PageGenerate.o RepPolicies.o -o prog3

PageGenerate.o: PageGenerate.cpp
	g++ -c -std=c++11 PageGenerate.cpp

RepPolicies.o: RepPolicies.cpp
	g++ -c -std=c++11 RepPolicies.cpp
prog3.o: prog3.cpp
	g++ -c -std=c++11 prog3.cpp

clean:
	rm*.o*.exe