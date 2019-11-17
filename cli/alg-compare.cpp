#include <Algorithms-Comparison/Generator.hpp>

int main(int argc, char* argv[])
{

    int parms[argc-1];

    if(!Generator::getParameters(parms, argc, argv)){
        return -1;
    }

    unsigned int num_of_matrices = parms[0];
    unsigned int max_num_of_nodes = parms[1];
    unsigned int max_weight_of_edges = parms[2];

    Generator generator = Generator();

    generator.generate_matrices(num_of_matrices, max_num_of_nodes, max_weight_of_edges);

    return 0;
}