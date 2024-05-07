#include <bits/stdc++.h>
using namespace std;

vector<int> dijkstras(vector<vector<int>>& vec, int V, int Edges, int source) {
    unordered_map<int, list<pair<int, int>>> adj;
    for (int i = 0; i < Edges; i++) {
        int u = vec[i][0];
        int v = vec[i][1];
        int w = vec[i][2];

        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    }

    vector<int> dist(V, INT_MAX);

    set<pair<int, int>> st;
    dist[source] = 0;
    st.insert(make_pair(0, source));

    while (!st.empty()) {
        auto top = *(st.begin());

        int nodeDist = top.first;
        int topNode = top.second;

        st.erase(st.begin());

        for (auto neigh : adj[topNode]) {
            if (nodeDist + neigh.second < dist[neigh.first]) {
                auto record = st.find(make_pair(dist[neigh.first], neigh.first));
                if (record != st.end()) {
                    st.erase(record);
                }

                dist[neigh.first] = nodeDist + neigh.second;

                st.insert(make_pair(dist[neigh.first], neigh.first));
            }
        }
    }
    return dist;
}

int main() {
    int V = 5, Edges = 7;
    vector<vector<int>> graph = { {0,1,7},{0,2,1},{0,3,2},{1,2,3},{1,3,5},{1,4,1},{3,4,7}};

    int source = 0; // Source node index
    int lastNode = V - 1; // Index of the last node

    vector<int> distances = dijkstras(graph, V, Edges, source);

    // Print the distances
    cout << "Shortest distances from source vertex to all other vertices:" << endl;
    for (int i = 0; i < V; ++i) {
        cout << "Distance to vertex " << i << " is " << distances[i] << endl;
    }
    
    // Distance between the source node and the last node
    int distanceToLastNode = distances[lastNode];

    cout << "Distance between source node and last node: " << distanceToLastNode << endl;

    return 0;
}
