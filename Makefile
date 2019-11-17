all:
	g++ -c src/Generator.cpp -o src/Generator.o -I ./include
	g++ -c cli/generator.cpp -o cli/generator.o -I ./include
	g++ -o bin/generator cli/generator.o src/Generator.o

matrices := 5
max_nodes := 5
max_weight := 20

run:
	./bin/alg-compare $(matrices) $(max_nodes) $(max_weight)