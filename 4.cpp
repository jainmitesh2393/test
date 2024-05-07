#include <iostream>
#include <unordered_map>
#include <list>
#include <queue>
#include <vector>
using namespace std;

class Graph {
public:
    unordered_map<int, list<int>> adj;

    void addEdge(int u, int v, int direction) {
        // direction = 0 undirected graph;
        // direction = 1 directed graph;

        adj[u].push_back(v);
        if (direction == 0) {
            adj[v].push_back(u);
        }
    }

    void printList() {
        for (auto i : adj) {
            cout << i.first << "->";
            for (auto j : i.second) {
                cout << j << ",";
            }
            cout << endl;
        }
    }
};

void bfsHelper(unordered_map<int, list<int>>& adj, unordered_map<int, bool>& visited, vector<int>& ans, int node) {
    queue<int> q;
    q.push(node);
    visited[node] = true;

    while (!q.empty()) {
        int frontNode = q.front();
        q.pop();

        ans.push_back(frontNode);

        for (auto i : adj[frontNode]) {
            if (!visited[i]) {
                q.push(i);
                visited[i] = true;
            }
        }
    }
}

vector<int> BFS(int vertex, unordered_map<int, list<int>>& adj) {
    vector<int> ans;
    unordered_map<int, bool> visited;
    for (int i = 0; i < vertex; i++) {
        if (!visited[i]) {
            bfsHelper(adj, visited, ans, i);
        }
    }
    return ans;
}

void dfsHelper(int node, unordered_map<int, bool>& visited, unordered_map<int, list<int>>& adj, vector<int>& comp) {
    comp.push_back(node);
    visited[node] = true;

    for (auto i : adj[node]) {
        if (!visited[i]) {
            dfsHelper(i, visited, adj, comp);
        }
    }
}

vector<int> DFS(int V, int E, unordered_map<int, list<int>>& adj) {
    vector<int> ans;
    unordered_map<int, bool> visited;

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            dfsHelper(i, visited, adj, ans);
        }
    }
    return ans;
}

int main() {
    int vertex;
    cout << "Enter the number of nodes" << endl;
    cin >> vertex;

    int edges;
    cout << "Enter the number of edges" << endl;
    cin >> edges;

    Graph g;
    for (int i = 0; i < edges; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v, 0);
    }
    g.printList();

    // Perform BFS traversal
    cout << "BFS Traversal:" << endl;
    vector<int> bfsResult = BFS(vertex, g.adj);
    for (int node : bfsResult) {
        cout << node << " ";
    }
    cout << endl;

    // Perform DFS traversal
    cout << "DFS Traversal:" << endl;
    vector<int> dfsResult = DFS(vertex, edges, g.adj);
    for (int node : dfsResult) {
        cout << node << " ";
    }
    cout << endl;

    return 0;
}
