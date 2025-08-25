#pragma once

#include "Algorithms.hpp"
#include "Graph.hpp"
#include<string>
#include <iostream>
using namespace std;
using namespace graph;


class stradegy{
//    virtual  void print()=0;
public:
   virtual ~stradegy(){}
   virtual string run(Graph& g,int start,int end){return "null";};
};
class Euler_circle: public stradegy{
    string run( Graph& g, int start,int end){
        bool t= Algorithms::Euler_circle(g,start);
        if(t){
            return "Euler circle";
        }
        return "not Euler circle";
    }

};

class fordFulkerson:public stradegy{
    string run(Graph& g,int start,int end){
        vector<std::vector<int>> cap=graphToVec(g);
        int maxflow = Algorithms::fordFulkerson(cap, start, end);
        return to_string(maxflow);

    }

    private:
    vector<std::vector<int>> graphToVec(Graph& g){   

    // std::vector<std::vector<int>> convertGraphToAdjMatrix(const graph::Graph& g) {
    int n = g.getNumVertices();  // מספר הצמתים בגרף
    std::vector<std::vector<int>> cap(n, std::vector<int>(n, 0));  // אתחול מטריצה בגודל n*n עם כל הערכים ב-0

    // עוברים על כל הצמתים
    for (int i = 0; i < n; ++i) {
        // מקבלים את רשימת השכנות של הצומת i
        graph::Neighbor** adjList = g.getAdjList();
        graph::Neighbor* neighbor = adjList[i];

        // עוברים על כל השכנים של הצומת i
        while (neighbor) {
            int j = neighbor->vertex;  // הצומת השכן
            int weight = neighbor->weight;  // המשקל של הקשת

            // ממלאים את המטריצה עם המשקל של הקשת בשני כיוונים, כי הגרף לא מכוון
            cap[i][j] = weight;
            cap[j][i] = weight;

            // ממשיכים לשכן הבא
            neighbor = neighbor->next;
        }
    

    return cap;
}


    }

};

class countCliques:public stradegy{
    string run(Graph& g,int start,int end){
        int num=Algorithms::countCliques(g, start);
        return  to_string(num);
    }

};

class findMaxClique:public stradegy{
    public:
    findMaxClique(){}
    string run(Graph& g,int start,int end) override{
        vector<int> maxClique =Algorithms::findMaxClique(g, start);
        return to_string(maxClique.size());
    }

};


class kruskalMST:public stradegy{
    string run(Graph& g,int start,int end){
         vector<Algorithms::Edge> edges;
    
    {
        auto adj = g.getAdjList();
        for (int u = 0; u < end; ++u) {
            for (Neighbor* cur = adj[u]; cur; cur = cur->next) {
                int v = cur->vertex, w = cur->weight;
                if (u < v) edges.push_back({u, v, w});
            }
        }
    }

  

    // ייתכן שאצלך יש operator< ל-Edge; אם לא, נסדר מיון לפי weight לפני הקריאה (kruskalMST ממיין שוב).
    int mstWeight = Algorithms::kruskalMST(end, edges);
    return to_string(mstWeight);
    
    }

};
