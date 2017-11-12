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
#include <algorithm>

using std::cout;
using std::endl;
using std::ios;
using std::istringstream;
using std::vector;
using std::string;
using std::ifstream;
using std::ofstream;
using std::getline;
using std::min;

void dijkstra(int src, int dist[], const vector<vector<int> >& m, int n);
void output_dijkstra(const vector<vector<int> >& d, int n, int counter);

int main(int argc, char* argv[]){

    if(argc != 2){
        cout << "usage: " << argv[0] << " <input_file>\n";
        return 0;
    }

    // Remove any previous output file
    remove("alg_output.txt");

    // Open the input file
    ifstream input;
    input.open(argv[1]);

    if(input.is_open()){
        int counter = 1;
        string firstLine;

        // Parse the file
        while(getline(input, firstLine)){

            int n;
            char fchar;

            // Confirm that we have the line above the matrix
            if(firstLine[0] == 'n'){

                // Parse number of nodes from the first line
                istringstream iss (firstLine);
                iss >> fchar >> fchar >> n;
            
                // Create vector of vectors with size n x n
                vector<vector<int> > m (n, vector<int>(n));

                for(int i = 0; i < n; i++){
                    for(int j = 0; j < n; j++){
                        input >> m[i][j];
                    }
                }
                
                // New vector for output of Dijkstra's Algorithm
                vector<vector<int> > d (m);

                // Run Dijkstra's Algorithm n times
                for(int i = 0; i < n; i++){
                    int dist[n];

                    dijkstra(i, dist, m, n);

                    for(int j = 0; j < n; j++){
                        d[i][j] = dist[j];
                    }
                }
                
                // Output the cost matrix to file
                output_dijkstra(d, n, counter);

                // Run Floyd-Warshall's
                counter++;
            }
        }
    }
    else cout << "There was a problem opening the input file: " << argv[1] << endl;

    return 0;
}
void output_dijkstra(const vector<vector<int> >& d, int n, int counter){

    ofstream alg_output;
    alg_output.open("alg_output.txt", ios::app);

    alg_output << "Graph #" << counter << '\n';
    alg_output << "Dijkstra's:\n";

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            alg_output << d[i][j] << " ";
        }
        alg_output << '\n';
    }

    alg_output << '\n';

    alg_output.close();
}

void dijkstra(int src, int dist[], const vector<vector<int> >& m, int n){
    
    // Set of visited nodes
    bool visited[n];

    for(int i = 0; i < n; i++){

        // Initialize all nodes to unvisited
        visited[i] = false;

        // Initial distance from source to each node is taken from cost matrix
        dist[i] = m[src][i];
    }

    // Mark source as visited
    visited[src] = true;

    // Distance from source to itself is 0
    dist[src] = 0;

    for(int i = 0; i < (n - 1); i++){
        int u = n / 2; 

        // Choose a vertex u that is unvisited whose distance from src is minimum
        for(int j = 0; j < n; j++){
            if(visited[j] == false){
                u = ((dist[u] < dist[j]) ? u : j);
            }
        }

        // Mark u as visited
        visited[u] = true;

        // For each neighbor j of u that has not been visited, updated distances
        for(int j = 0; j < n; j++){
            if((visited[j] == false) && (dist[j] > dist[u] + m[u][j])){
                dist[j] = dist[u] + m[u][j];
            }
        }
    }
}

