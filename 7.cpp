#include <bits/stdc++.h>
using namespace std;

bool cmp(vector<int> &a,vector<int> &b){
    return a[2] < b[2];
}
void makeSet(vector<int> &parent,vector<int> &rank,int n){
    for(int i=0;i<n;i++){
        parent[i] = i;
        rank[i] = 0;
    }
}

int findparent(vector<int> &parent,int node){
    if(parent[node] == node){
        return node;
    }
    return parent[node] = findparent(parent,parent[node]);
}

void unionSet(int u,int v,vector<int> &parent,vector<int> &rank){
    u = findparent(parent,u);
    v = findparent(parent,v);

    if(rank[u] < rank[v]){
        parent[u] = v;
    }
    else if(rank[v] < rank[u]){
        parent[v] = u;
    }
    else{
        parent[v] = u;
        rank[u]++;
    }
}

int minimumSpanningTree(vector<vector<int>>& edges,int n){
    sort(edges.begin(),edges.end(),cmp);
    vector<int> parent(n);
    vector<int> rank(n);

    makeSet(parent,rank,n);
    int minwt = 0;
    //sort edges by wt
    for(int i=0;i<edges.size();i++){
        int u = findparent(parent,edges[i][0]);
        int v = findparent(parent,edges[i][1]);

        int wt = edges[i][2];

        if(u != v){
            minwt += wt;
            unionSet(u,v,parent,rank);
        }
    }
    return minwt;
}
int main(){
    int n;
    vector<vector<int>> edges ={{1,4,1},{1,2,2},{2,3,3},{2,4,3},{1,5,4},{3,4,5},{2,6,7},{3,6,8},{4,5,9}};

    int ans = minimumSpanningTree(edges,n);
    cout << "Minimum spanning Tree : w" << ans << endl;
    return 0;
}
