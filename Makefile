

main: main.o 
	g++ -o main main.o -llapack -larmadillo

main.o: main.cpp
	g++ -c -std=c++14 main.cpp

c: 
	rm -rf *.o
