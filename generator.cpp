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

using std::vector;
using std::ofstream;
using std::ios;
using std::cout;

void populateMatrix(int n, vector<vector<int> >& m);
void writeMatrix(int n, const vector<vector<int> >& m);

int main(){
    
    // Remove any previous file
    remove("matrices.txt");

    // Seed our random number generator
    srand(time(0));

    cout << "Generating matrices...";

    // Generate 30 cost matrices
    for(int i = 0; i < 30; i++){

        // Random number of nodes from 50-1000
        int n = rand() % 951 + 50;

        // Create a vector of vectors with size n x n
        vector<vector<int> > m (n, vector<int>(n));
    
        // Assign the edge values
        populateMatrix(n, m);

        // Send the cost matrix to the output file
        writeMatrix(n, m);

        }

    cout << "complete!\nOutput in matrices.txt\n";

    return 0;
}

void populateMatrix(int n, vector<vector<int> >& m){
    // Populate edge values (1-100)
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(i == j){
                m[i][j] = 0;
            }
            else{
               m[i][j] = rand() % 100 + 1; 
            }
        }
    }
}

void writeMatrix(int n, const vector<vector<int> >& m){
    // Open output file in append mode
    ofstream output;
    output.open("matrices.txt", ios::app);

    // Write cost matrix to file, using ; on it's own line as a delimiter between matrices
    if(output.is_open()){
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
        output << ";\n";
        output.close();
    }
    else cout << "There was a problem opening the output file: \"matrices.txt\"\n";
}
