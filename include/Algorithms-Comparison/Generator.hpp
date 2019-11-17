#ifndef ALGORITHMS_COMPARISON_GENERATOR_HPP
#define ALGORITHMS_COMPARISON_GENERATOR_HPP

#include <string>
#include <vector>

class Generator
{
    public:
        Generator() {};
        void generate_matrices(unsigned int num_matrices_, unsigned int max_nodes_, unsigned int max_edge_weight_);
        static int getParameters(int parms[], int argc, char* argv[]);
    private:
        static void printUsage(char* argv[]);
        static void printError(std::string msg, char* argv[]);
        void populateMatrix(int n,
                            std::vector<std::vector<int> >& m,
                            int max_weight_of_edges);
        void writeMatrix(int n,
                         const std::vector<std::vector<int> >& m);
};
#endif