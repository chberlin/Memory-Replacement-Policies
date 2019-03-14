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
	gnuplot -e "title='No-Locality'" -e "input_filename='No-Locality.csv'" plot_hit_rates.plt > No-Locality.png
	gnuplot -e "title='8020'" -e "input_filename='8020.csv'" plot_hit_rates.plt > 8020.png
	gnuplot -e "title='loop'" -e "input_filename='loop.csv'" plot_hit_rates.plt > loop.png
