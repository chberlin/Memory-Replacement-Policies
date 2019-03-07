prog3 : prog3.o PageGenerate.o RepPolicies.o
	g++ prog3.o PageGenerate.o RepPolicies.o -o prog3

PageGenerate.o : PageGenerate.cpp
	g++ -c -std=c++11 PageGenerate.cpp

RepPolicies.o : RepPolicies.cpp
	g++ -c -std=c++11 RepPolicies.cpp

prog3.o : prog3.cpp
	g++ -c -std=c++11 prog3.cpp

clean:
	rm *.o  *.csv prog3
