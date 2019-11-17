/* Author: Anthony Hicks
 * Class : CSCE 4110 - Algorithms
 * Prof  : Dr. Shahrokhi
 * Assgn : Term Project - Algorithm Comparison
 * Descr : Generates 30 cost matrices with number of nodes ranging from 50-1000 and cost of each edge ranging from 1-100
 *         The output is to be used as input to the Dijkstra's vs FW comparison program.
 */
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

#include <Algorithms-Comparison/Generator.hpp>

using std::vector;
using std::string;
using std::ofstream;
using std::istringstream;
using std::ios;
using std::cout;
using std::endl;

void Generator::printUsage(char* argv[]){
    cout << "Usage: " << argv[0] << " <num_matrices_> <max_num_of_nodes> <max_weight_of_edges>" << endl;
}

void Generator::printError(string msg, char* argv[]){
    cout << "Error: " << msg << endl;
    printUsage(argv);
}

int Generator::getParameters(int parms[], int argc, char* argv[]) {
    
    if(argc != 4){
        printError("Incorrect number of parameters", argv);
        return 0;
    }

    for(int i = 0; i < argc - 1; i++){
        istringstream ss(argv[i+1]);

        if(!(ss >> parms[i])){
            string e = "Invalid parameter: ";
            e += argv[i+1];
            printError(e, argv);
            return 0;
        }
    }

    return 1;
};

void Generator::generate_matrices(unsigned int num_matrices_,
                                  int max_nodes_,
                                  uint max_edge_weight_)
{
    // Remove any previous file
    remove("matrices.txt");

    // Seed our random number generator
    srand(time(0));

    cout << "Generating matrices..." << std::flush;

    // Generate cost matrices
    for(int i = 0; i < num_matrices_; i++){

        // Random number of nodes from 50-1000
        // TODO: fix the fact that max_nodes_ has to be signed
        int n = rand() % (max_nodes_ - 49) + 50;

        // Create a vector of vectors with size n x n
        vector<vector<int> > m (n, vector<int>(n));
    
        // Assign the edge values
        populateMatrix(n, m, max_edge_weight_);

        // Send the cost matrix to the output file
        writeMatrix(n, m);
        }

    cout << "complete!\nOutput in matrices.txt\n";
}

void Generator::populateMatrix(int n, vector<vector<int> >& m, int max_weight_of_edges){
    // Populate edge values (1-100)
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(i == j){
                m[i][j] = 0;
            }
            else{
               m[i][j] = rand() % max_weight_of_edges + 1; 
            }
        }
    }
}

void Generator::writeMatrix(int n, const vector<vector<int> >& m){
    // Open output file in append mode
    ofstream output;
    output.open("matrices.txt", ios::app);

    // Write cost matrix to file, using the number of nodes as a delimiter between matrices
    if(output.is_open()){
        output << "n = " << n << '\n';
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(j == (n - 1)){
                    output << m[i][j];
                }
                else{
                    output << m[i][j] << " ";
                }
            }
            output << '\n';
        }
        output.close();
    }
    else cout << "There was a problem opening the output file: \"matrices.txt\"\n";
}
