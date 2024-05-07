#include<bits/stdc++.h>
using namespace std;

// Function to find the vertex with minimum key value
int minKey(vector<int>& key, vector<bool>& mstSet, int V) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; ++v) {
        if (mstSet[v] == false && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

// Function to print the constructed MST stored in parent[]
void printMST(vector<int>& parent, vector<vector<int>>& graph, int V) {
    cout << "Edge \tWeight\n";
    for (int i = 1; i < V; ++i)
        cout << parent[i] << " - " << i << "\t" << graph[i][parent[i]] << endl;
}

// Function to construct and print MST for a graph represented using adjacency matrix representation
void primMST(vector<vector<int>>& graph, int V) {
    vector<int> parent(V); // Array to store constructed MST
    vector<int> key(V);    // Key values used to pick minimum weight edge in cut
    vector<bool> mstSet(V); // To represent set of vertices included in MST

    // Initialize all keys as INFINITE
    for (int i = 0; i < V; ++i) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    // Always include first 1st vertex in MST.
    key[0] = 0;     
    parent[0] = -1; 

    for (int count = 0; count < V - 1; ++count) {
        int u = minKey(key, mstSet, V);

        mstSet[u] = true;
        for (int v = 0; v < V; ++v) {
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    // Print the constructed MST
    printMST(parent, graph, V);
}

int main() {
    // Example 
    vector<vector<int>> graph = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
    };

    primMST(graph, 5); // 5 is the number of vertices

    return 0;
}
