all:
	g++ -c src/Generator.cpp -o src/Generator.o -I ./include
	g++ -c cli/alg-compare.cpp -o cli/alg-compare.o -I ./include
	g++ -o bin/alg-compare cli/alg-compare.o src/Generator.o

run:
	./bin/alg-compare 1 5 20