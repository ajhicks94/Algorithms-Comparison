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
#include <ctime>
#include <climits>

using std::cout;
using std::endl;
using std::ios;
using std::istringstream;
using std::vector;
using std::string;
using std::ifstream;
using std::ofstream;
using std::getline;

void setup_summary();
void dijkstra(int src, int dist[], const vector<vector<int> >& m, int n);
void output_dijkstra(const vector<vector<int> >& d, int n, int counter, double time_elapsed);

void floyd_warshall(vector<vector<int> >& m, int n, clock_t &fw_begin, clock_t &fw_end);
void output_fw(const vector<vector<int> >& m, int n, double time_elapsed);

int main(int argc, char* argv[]){

    if(argc != 2){
        cout << "usage: " << argv[0] << " <input_file>\n";
        return 0;
    }

    // Remove any previous output file
    remove("alg_output.txt");
    remove("summary.txt");

    // Open the input file
    ifstream input;
    input.open(argv[1]);

    if(input.is_open()){

        setup_summary();

        int counter = 1;
        string firstLine;

        // Parse the file
        while(getline(input, firstLine)){

            int n;
            char fchar;
            clock_t d_begin;
            clock_t d_end;
            clock_t fw_begin;
            clock_t fw_end;
            double d_elapsed;
            double fw_elapsed;

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
                d_begin = clock();
                for(int i = 0; i < n; i++){
                    int dist[n];

                    dijkstra(i, dist, m, n);

                    for(int j = 0; j < n; j++){
                        d[i][j] = dist[j];
                    }
                }
                d_end = clock();
                d_elapsed = double(d_end - d_begin) / CLOCKS_PER_SEC;

                // Output the cost matrix to file
                output_dijkstra(d, n, counter, d_elapsed);

                // Run Floyd-Warshall's Algorithm on cost matrix
                floyd_warshall(m, n, fw_begin, fw_end);

                fw_elapsed = double(fw_end - fw_begin) / CLOCKS_PER_SEC;

                // Output results to file
                output_fw(m, n, fw_elapsed);

                // Increment counter
                counter++;
            }
        }

        // Close input stream
        input.close();
    }
    else cout << "There was a problem opening the input file: " << argv[1] << endl;

    return 0;
}

void setup_summary(){
    ofstream summary;
    summary.open("summary.txt", ios::app);

    summary << "-----------------------------------" << endl;
    summary << "|  n  | Dijkstra | Floyd-Warshall |" << endl;
    summary << "-----------------------------------" << endl;

    summary.close();
}


void output_fw(const vector<vector<int> >& m, int n, double time_elapsed){
    ofstream alg_output;
    alg_output.open("alg_output.txt", ios::app);

    alg_output << "Floyd-Warshall:\n";

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            alg_output << m[i][j] << " ";
        }
        alg_output << '\n';
    }

    alg_output << '\n';

    alg_output.close();
}

void floyd_warshall(vector<vector<int> >& m, int n, clock_t &fw_begin, clock_t &fw_end){
    fw_begin = clock();
    for(int k = 0; k < n; k++){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(m[i][j] > m[i][k] + m[k][j]){
                    m[i][j] = (m[i][k] + m[k][j]);
                }
            }
        }
    }
    fw_end = clock();
}

void output_dijkstra(const vector<vector<int> >& d, int n, int counter, double time_elapsed){

    ofstream alg_output;
    alg_output.open("alg_output.txt", ios::app);

    alg_output << "\tGraph #" << counter << ", n = " << n << '\n';
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

    for(int i = 0; i < n; i++){
        int u;
        int min = INT_MAX;

        // Choose a vertex u that is unvisited whose distance from src is minimum
        for(int j = 0; j < n; j++){
            if(visited[j] == false && dist[j] < min){
                u = j;
                min = dist[j];
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

