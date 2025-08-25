#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <set>
#include <utility>
using namespace std;
namespace graph {

    struct Neighbor {
        int vertex;
        int weight;
        Neighbor* next;

        Neighbor(int v, int w, Neighbor* n = nullptr)
            : vertex(v), weight(w), next(n) {}
        
    };

    class Graph {
    private:
        int numVertices;
        Neighbor** adjList;

        void removeFromList(int from, int to);

    public:
        Graph(int vertices);
        ~Graph();
        Graph(const Graph& other);

        void addEdge(int from, int to, int weight = 1);
        void removeEdge(int from, int to);
        void print_graph() const;
        bool isEven() const;
        Graph generateRandomGraph (int v , int e);
        bool isInside(set<pair<int,int>> used_pairs,int a, int b );
        int getNumOfNeighbors(int i) const;
        Graph& operator=(const Graph& other);
        static Neighbor* cloneList(Neighbor* head) ;


        

        int getNumVertices() const;
        Neighbor** getAdjList() const;
    };

}

#endif