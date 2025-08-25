#pragma once
#include <vector>
#include "Graph.hpp"

namespace graph {
    class Algorithms {

    public:
            struct Edge {
        int u, v, weight;
        bool operator<(const Edge& other) const {
            return weight < other.weight;
    }
};
       static bool Euler_circle(const Graph& g, int start); 
       static bool bfs(vector<vector<int>>& rGraph, int s, int t, vector<int>& parent);
       static int kruskalMST(int n, vector<Edge>& edges);
       static void unionSets(int u, int v, vector<int>& parent, vector<int>& rank);
       static int findParent(int node, vector<int>& parent);
       static int fordFulkerson(vector<vector<int>>& graph, int s, int t);
       static int countCliques(const Graph& g, int n);
       static vector<int> findMaxClique(const Graph& g, int n);
       static bool isClique(const Graph& g, const vector<int>& nodes);
    };
}
