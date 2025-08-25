#pragma once

#include "stradegy.hpp"
#include<string>
class factory{
    public:
    factory(){}

    stradegy* create(string name){
        if(name=="Euler circle"){return new Euler_circle();}
        if(name=="max flow"){return  new fordFulkerson();}
        if(name=="count cliques"){return  new countCliques();}
        if(name=="find Max clique"){return  new findMaxClique();}
        if(name=="MST"){return  new kruskalMST();}

    }



};