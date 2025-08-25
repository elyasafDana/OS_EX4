#include "Algorithms.hpp"
#include <vector>
#include <list>
#include <stack>
#include<queue>
#include <iostream>
#include <algorithm>
#include <climits>
#include "UnionFind.hpp"

using namespace std;
using namespace graph;
/**
 * Performs Breadth-First Search (BFS) traversal on the given graph,
 * starting from the specified vertex.
 *
 * @param g The input graph (undirected).
 * @param start The starting vertex for the BFS traversal.
 * @return A new graph representing the BFS tree (spanning tree rooted at start).
 * @throws Exception if the graph is empty or the start vertex is invalid.
 */

    bool Algorithms::Euler_circle(const Graph& d, int start) {
        Graph g=d;
        // for (int i = 0; i < g.getNumVertices(); i++)
        // {

            
        // }
        
        int n = g.getNumVertices();
        if (n <= 0) throw "Graph is empty.";
        if (start < 0 || start >= n) throw "this is not a valid start";
        Graph tree(n);
        bool* visited = new bool[n]{false};

        std::queue<int> q ;
        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            int current = q.front();
            q.pop();
            Neighbor** adj = g.getAdjList();
            Neighbor* neighbor = adj[current];
            while (neighbor) {
                int v = neighbor->vertex;
                if (!visited[v]) {
                    visited[v] = true;
                    tree.addEdge(current, v, neighbor->weight);
                    q.push(v);
                }
                neighbor = neighbor->next;
            }
        }
        for (int i = 0; i < n; i++)//check if there is more then one connection  compenent
        {
            Neighbor** adj = g.getAdjList();
            if (visited[i]==false && adj[i]!=nullptr)
            {
                return false;
            }
            
        }
        if(!g.isEven()){return false;}// check if the number of neighbors for etch vertex is even
   
        delete[] visited;
        return true;
    }
    //------------------MaxClique--------------------------------------------------

    bool Algorithms::isClique(const Graph& g, const vector<int>& nodes) {
    for (int i = 0; i < nodes.size(); i++) {
        for (int j = i + 1; j < nodes.size(); j++) {
            Neighbor** adj = g.getAdjList();
            bool isConnected = false;
            Neighbor* neighbor = adj[nodes[i]];
            while (neighbor) {
                if (neighbor->vertex == nodes[j]) {
                    isConnected = true;
                    break;
                }
                neighbor = neighbor->next;
            }
            if (!isConnected) return false;
        }
    }
    return true;
}


    vector<int> Algorithms::findMaxClique(const Graph& g, int n) {
    vector<int> maxClique;
    
    for (int i = 0; i < (1 << n); i++) {
        vector<int> clique;
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                clique.push_back(j);
            }
        }
        if (isClique(g, clique) && clique.size() > maxClique.size()) {
            maxClique = clique;
        }
    }
    return maxClique;
}


    //-----------------------number of cluqe-------------------

    int Algorithms::countCliques(const Graph& g, int n) {
    int cliqueCount = 0;
    for (int i = 0; i < (1 << n); i++) {
        vector<int> clique;
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                clique.push_back(j);
            }
        }
        if (isClique(g, clique)) {
            cliqueCount++;
        }
    }
    return cliqueCount;
}


//------------------MAX FLOW--------------------------
int Algorithms::fordFulkerson(vector<vector<int>>& graph, int s, int t) {
    int n = graph.size();
    vector<vector<int>> rGraph = graph;
    vector<int> parent(n);
    int maxFlow = 0;

    while (bfs(rGraph, s, t, parent)) {
        int pathFlow = INT_MAX;
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            pathFlow = min(pathFlow, rGraph[u][v]);
        }

        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            rGraph[u][v] -= pathFlow;
            rGraph[v][u] += pathFlow;
        }
        maxFlow += pathFlow;
    }
    return maxFlow;
}
//-----------------kruskal-----------------------





int Algorithms::findParent(int node, vector<int>& parent) {
    if (parent[node] == node) return node;
    return parent[node] = findParent(parent[node], parent);
}

void Algorithms::unionSets(int u, int v, vector<int>& parent, vector<int>& rank) {
    int root_u = findParent(u, parent);
    int root_v = findParent(v, parent);
    if (root_u != root_v) {
        if (rank[root_u] > rank[root_v]) parent[root_v] = root_u;
        else if (rank[root_u] < rank[root_v]) parent[root_u] = root_v;
        else {
            parent[root_v] = root_u;
            rank[root_u]++;
        }
    }
}

int Algorithms::kruskalMST(int n, vector<Edge>& edges) {
    sort(edges.begin(), edges.end());
    vector<int> parent(n);
    vector<int> rank(n, 0);
    for (int i = 0; i < n; i++) parent[i] = i;

    int mstWeight = 0;
    for (const Edge& edge : edges) {
        int u = edge.u;
        int v = edge.v;
        if (findParent(u, parent) != findParent(v, parent)) {
            unionSets(u, v, parent, rank);
            mstWeight += edge.weight;
        }
    }
    return mstWeight;
}
    //---------------------bfs-------------------------


bool Algorithms::bfs(vector<vector<int>>& rGraph, int s, int t, vector<int>& parent) {
    int n = rGraph.size();
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(s);
    visited[s] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 0; v < n; v++) {
            if (!visited[v] && rGraph[u][v] > 0) {
                q.push(v);
                visited[v] = true;
                parent[v] = u;
            }
        }
    }
    return visited[t];
}


   

