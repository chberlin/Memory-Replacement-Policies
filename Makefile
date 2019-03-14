prog3 : prog3.o PageGenerate.o RepPolicies.o
	g++ prog3.o PageGenerate.o RepPolicies.o -o prog3

PageGenerate.o : PageGenerate.cpp
	g++ -c -std=c++11 PageGenerate.cpp

RepPolicies.o : RepPolicies.cpp
	g++ -c -std=c++11 RepPolicies.cpp

prog3.o : prog3.cpp
	g++ -c -std=c++11 prog3.cpp

clean:
	rm *.o  *.csv prog3 *.png

graph:
	gnuplot -e "title='The No-Locality Workload'" -e "input_filename='No-Locality.csv'" plot_hit_rates.plt > No-Locality.png
	gnuplot -e "title='The 80-20 Workload'" -e "input_filename='8020.csv'" plot_hit_rates.plt > 8020.png
	gnuplot -e "title='The Looping-Sequential Workload'" -e "input_filename='Loop.csv'" plot_hit_rates.plt > Loop.png
