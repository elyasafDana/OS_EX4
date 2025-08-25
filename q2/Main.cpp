#include "Algorithms.hpp"
#include "Graph.hpp"
#include <iostream>
using namespace graph;
using namespace std;
void printTitle(const std::string& title) {
    std::cout << "\n=== " << title << " ===\n";}
int main() {
 


    Graph g(13);
    
    g.addEdge(0, 1, 4);
    g.addEdge(1, 2, 3);
    g.addEdge(2, 0, 1);
    // g.addEdge(8, 9, 2);
    g.addEdge(2, 3, 4);
    // g.addEdge(11, 11, 0);
    

    printTitle("Original Graph");
    g.print_graph();


    // BFS
    printTitle("BFS Tree from vertex 0");
    
    if ( Algorithms::Euler_circle(g, 0))
    {
        cout<< "true"<<endl;
    }else  cout<< "false"<<endl;
    
   
   
    
    return 0;
}