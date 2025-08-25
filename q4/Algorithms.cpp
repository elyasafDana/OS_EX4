#include "Algorithms.hpp"
#include <vector>
#include <list>
#include <stack>
#include<queue>

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
                delete[] visited;
                return false;
            }
            
        }
        if(!g.isEven()){
            delete[] visited;
            return false;
        }// check if the number of neighbors for etch vertex is even
   
        delete[] visited;
        return true;
    }

   

