/* Author: Anthony Hicks
 * Class : CSCE 4110 - Algorithms
 * Prof  : Dr. Shahrokhi
 * Assgn : Term Project - Algorithm Comparison
 * Descr : 
 */
#include <iostream>
#include <fstream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;
using std::ifstream;
using std::ofstream;

int main(int argc, char* argv[]){

    if(argc != 2){
        cout << "usage: " << argv[0] << " <input_file>\n";
        return 0;
    }

    ifstream input;
    input.open(argv[1]);

    if(input.is_open()){

    }
    else cout << "There was a problem opening the input file: " << argv[1] << endl;

    return 0;
}
