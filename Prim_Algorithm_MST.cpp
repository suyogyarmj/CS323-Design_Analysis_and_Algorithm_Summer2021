/*
CSCI 323-2021-Summer
Assignment 1
Suyogya Rayamajhi
*/

// A C++ program for Prim's Minimum
// Spanning Tree (MST) algorithm. The program is
// for adjacency matrix representation of the graph

#include <fstream>
#include <sstream>
#include <chrono>
#include <iostream>

using namespace std;

// Number of vertices in the graph
int V = 0;
int num_operations = 0;

// A utility function to find the vertex with
// minimum key value, from the set of vertices
// not yet included in MST
int minKey(int key[], bool mstSet[])
{
    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (mstSet[v] == false && key[v] < min)
        {
            num_operations++;
            min = key[v], min_index = v;
        }

    return min_index;
}

// A utility function to print the
// constructed MST stored in parent[]
void printMST(int parent[], int **graph)
{
    cout<<"Edge \tWeight\n";
    for (int i = 1; i < V; i++)
        cout<<parent[i] + 1<<" - "<<i + 1<<" \t"<<graph[i][parent[i]]<<" \n";
}

// Function to construct and print MST for
// a graph represented using adjacency
// matrix representation
void primMST(int **graph)
{
    // Array to store constructed MST
    int *parent = new int[V];
    
    // Key values used to pick minimum weight edge in cut
    int *key = new int[V];
    
    // To represent set of vertices included in MST
    bool *mstSet = new bool[V];

    // Initialize all keys as INFINITE
    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = false;

    // Always include first 1st vertex in MST.
    // Make key 0 so that this vertex is picked as first vertex.
    key[0] = 0;
    parent[0] = -1; // First node is always root of MST

    // The MST will have V vertices
    for (int count = 0; count < V - 1; count++)
    {
        // Pick the minimum key vertex from the
        // set of vertices not yet included in MST
        int u = minKey(key, mstSet);

        // Add the picked vertex to the MST Set
        mstSet[u] = true;

        // Update key value and parent index of
        // the adjacent vertices of the picked vertex.
        // Consider only those vertices which are not
        // yet included in MST
        for (int v = 0; v < V; v++)
        {

            // graph[u][v] is non zero only for adjacent vertices of m
            // mstSet[v] is false for vertices not yet included in MST
            // Update the key only if graph[u][v] is smaller than key[v]
            num_operations++;
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
        }
    }

    // print the constructed MST
    printMST(parent, graph);

    delete[] mstSet;
    delete[] key;
    delete [] parent;
}

// Driver code
int main()
{
    /* Let us create the following graph
        2 3
    (0)--(1)--(2)
    | / \ |
    6| 8/ \5 |7
    | / \ |
    (3)-------(4)
            9    */


    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    
    int E = 0; // Number of edges in graph

    ifstream fin;

    fin.open("input.txt");

    if (!fin.is_open()) 
    {
        cout << "File input.txt not found" << endl;

    }

    string line;
    int num1, num2;

    // count total edges and vertices in the graph
    while (getline(fin, line)) 
    {

        V++;
        istringstream iss(line);
        string value;

        if (getline(iss, value, ':'))
        {
            // read the string before comma
            while (getline(iss, value, ',')) 
            {
                // first number is destination
                // second number is the weight
                istringstream iss2(value);
                iss2 >> num1;
                iss2 >> num2;
                E++;
            }
        }
    }

    fin.close();


    // create 2D array
    int** graph = new int*[V];

    // create 1D array and assign memory
    int* graph_mem = new int[V * V];

    for (int i = 0; i < V; i++)
    {
        graph[i] = &graph_mem[i * V];
    }


    // set initial distances to zero
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            graph[i][j] = 0;
        }
    }


    fin.open("input.txt");


    int vert = 0;

    // now the read the file again the build the graph
    while (getline(fin, line)) 
    {
        istringstream iss(line);
        string value;

        if (getline(iss, value, ':'))
        {

            // first number is the sourced node
            istringstream iss1(value);
            iss1 >> vert;
            while (getline(iss, value, ',')) 
            {

                // second two numbers are destination and weight
                istringstream iss2(value);
                iss2 >> num1;
                iss2 >> num2;
                graph[vert - 1][num1 - 1] = num2;
                
            }
        }
    }

    fin.close();


    // Print the solution
    primMST(graph);

    delete [] graph[0];
    delete [] graph;


    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    cout << "Time taken (sec) = " <<  (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) /1000000.0  <<std::endl;
    cout << "Total operations: " << num_operations << endl;

    return 0;
}

// This code is contributed by rathbhupendra
