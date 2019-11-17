#include <string>
#include <vector>

class Generator
{
    public:
        void printUsage(char* argv[]);
        void printError(std::string msg, char* argv[]);
        int getParameters(int parms[], int argc, char* argv[]);
        void populateMatrix(int n,
                            std::vector<std::vector<int> >& m,
                            int max_weight_of_edges);
        void writeMatrix(int n,
                         const std::vector<std::vector<int> >& m);
        void generate_matrices(unsigned int num_matrices_, unsigned int max_nodes_, unsigned int max_edge_weight_);
};