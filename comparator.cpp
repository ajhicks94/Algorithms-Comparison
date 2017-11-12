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
using std::istringstream;
using std::vector;
using std::string;
using std::ifstream;
using std::ofstream;
using std::getline;
using std::min;

void dijkstra(int src, int dist[], const vector<vector<int> >& m, int n);

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

            int dist[n];
            dijkstra(2, dist, m, n);
            for(int i = 0; i < n; i++){
                cout << "dist[0][" << i << "]= " << dist[i] << '\n';
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

