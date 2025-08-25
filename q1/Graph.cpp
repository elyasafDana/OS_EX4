#include "Graph.hpp"
#include <iostream>

namespace graph {

/**
 * Creates a new graph with the given number of vertices.
 *
 * @param vertices Number of vertices in the graph.
 * @throws If the number of vertices is 0 or negative.
 */
    Graph::Graph(int vertices) {
        if (vertices <= 0) {
            throw "Graph must have at least one vertex.";
        }
        numVertices = vertices;
        adjList = new Neighbor*[vertices];
        for (int i = 0; i < vertices; ++i) {
            adjList[i] = nullptr;
        }
    }

 /**
 * Frees the memory used by the graph.
 * Deletes all the neighbors and the adjacency list.
 */

    Graph::~Graph() {
        for (int i = 0; i < numVertices; ++i) {
            Neighbor* current = adjList[i];
            while (current) {
                Neighbor* temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] adjList;
    }
 /**
 * Adds an edge between two vertices with a given weight.
 * Since the graph is undirected, the edge is added in both directions.
 *
 * @param from The first vertex.
 * @param to The second vertex.
 * @param weight The weight of the edge.
 * @throws If one of the vertex indexes is not valid.
 */
    void Graph::addEdge(int from, int to, int weight) {
        if (from < 0 || from >= numVertices || to < 0 || to >= numVertices) {
            throw "Invalid vertex index.";
        }

        adjList[from] = new Neighbor(to, weight, adjList[from]);
        adjList[to] = new Neighbor(from, weight, adjList[to]);
    }

 /**
 * Removes one direction of an edge from the adjacency list of a vertex.
 *
 * @param from The vertex to remove the edge from.
 * @param to The neighbor to remove.
 * @throws If the edge does not exist.
 */
    void Graph::removeFromList(int from, int to) {
        Neighbor* current = adjList[from];
        Neighbor* prev = nullptr;

        while (current) {
            if (current->vertex == to) {
                if (prev) {
                    prev->next = current->next;
                } else {
                    adjList[from] = current->next;
                }
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }

        throw "Edge does not exist.";
    }

 /**
 * Removes an edge between two vertices from both directions.
 *
 * @param from The first vertex.
 * @param to The second vertex.
 * @throws If one of the vertex indexes is not valid,
 *         or if the edge does not exist.
 */
    void Graph::removeEdge(int from, int to) {
        if (from < 0 || from >= numVertices || to < 0 || to >= numVertices) {
            throw "Invalid vertex index.";
        }

        removeFromList(from, to);
        removeFromList(to, from);
    }

 /**
 * Prints the graph as an adjacency list.
 * Each line shows a vertex and its connected neighbors with weights.
 */
    void Graph::print_graph() const {
        for (int i = 0; i < numVertices; ++i) {
            std::cout << "Vertex " << i << ":";
            Neighbor* current = adjList[i];
            while (current) {
                std::cout << " -> (" << current->vertex << ", w=" << current->weight << ")";
                current = current->next;
            }
            std::cout << std::endl;
        }
    }
 
 /**
 * Returns the number of vertices in the graph.
 *
 * @return Number of vertices.
 */
    int Graph::getNumVertices() const {
    return numVertices;
    }

 /**
 * Returns the adjacency list of the graph.
 *
 * @return Pointer to the adjacency list.
 */
    Neighbor** Graph::getAdjList() const {
    return adjList;
    }

}