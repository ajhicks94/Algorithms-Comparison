/* Author: Anthony Hicks
 * Class : CSCE 4110 - Algorithms
 * Prof  : Dr. Shahrokhi
 * Assgn : Term Project - Algorithm Comparison
 * Descr : 
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using std::cout;
using std::endl;
using std::istringstream;
using std::vector;
using std::string;
using std::ifstream;
using std::ofstream;
using std::getline;



int main(int argc, char* argv[]){

    if(argc != 2){
        cout << "usage: " << argv[0] << " <input_file>\n";
        return 0;
    }

    // Open the input file
    ifstream input;
    input.open(argv[1]);

    if(input.is_open()){
        int n;
        char fchar;
        string firstLine;

        // Get the first line
        getline(input, firstLine);

        // Confirm that we have the line above the matrix
        if(firstLine[0] == 'n'){
            cout << "Correctly identified first line" << endl;

            // Parse number of nodes from the first line
            istringstream iss (firstLine);
            iss >> fchar >> fchar >> n;
            
            // Create vector of vectors with size n x n
            vector<vector<int> > m (n, vector<int>(n));

            /*input >> m[0][0];
            cout << "m[0][0]= " << m[0][0] << '\n';
            input >> m[0][1];
            cout << "m[0][1]= " << m[0][1] << '\n';
*/
            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                    input >> m[i][j];
                }
            }

            // Run dijsktra's n times
            // Run Floyd-Warshall's

            /*for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                    cout << m[i][j] << " ";
                }
                cout << '\n';
            }*/
        }
    }
    else cout << "There was a problem opening the input file: " << argv[1] << endl;

    return 0;
}
