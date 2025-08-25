#include "Algorithms.hpp"
#include "Graph.hpp"
#include <iostream>
#include <unistd.h> // getopt
#include <cstdlib>  // atoi
#include <random>
using namespace graph;
using namespace std;

void printTitle(const std::string& title) {
    std::cout << "\n=== " << title << " ===\n";}





int main(int argc, char* argv[]) {
    int opt;
    int vertex = 0, edge = 0, root = 0;

    while ((opt = getopt(argc, argv, "v:e:r:")) != -1) {
        switch (opt) {
            case 'v':
                vertex = atoi(optarg); 
                break;
            case 'e':
                edge = atoi(optarg);
                break;
            case 'r':
                root = atoi(optarg);
                break;
            case '?':
                cerr << "שגיאה: אופציה לא מוכרת או חסר ערך" << endl;
                return 1;
        }
    }

    cout << "Vertex: " << vertex << endl;
    cout << "Edge: " << edge << endl;
    cout << "Root: " << root << endl;


    Graph g(vertex) ;
    g=g.generateRandomGraph(vertex,edge);

    
    // g.addEdge(0, 1, 4);
    // g.addEdge(1, 2, 3);
    // g.addEdge(2, 0, 1);
    // // g.addEdge(8, 9, 2);
    // g.addEdge(2, 3, 4);
    // // g.addEdge(11, 11, 0);
    

    printTitle("Original Graph");
    g.print_graph();


    // BFS
    printTitle("Euler_circle");
    
    if ( Algorithms::Euler_circle(g, 0))
    {
        cout<< "true"<<endl;
    }else  cout<< "false"<<endl;
    
   
   
    
    return 0;
}
