#include "MCST.h"

int main()
{
    std::cout << "Michael Dutchin - Lab 5: Minimum Cost Spanning Tree" << std::endl;

    //make graph
    std::unique_ptr<MCST> graph = std::make_unique<MCST>("input.txt");
    graph->print(0);    //print graph details

    //make MCSTs from different vertcies
    MCST* mcst1 = graph->Prim(0);
    MCST* mcst2 = graph->Prim(4);
    MCST* mcst3 = graph->Prim(2);

    //write MCSTs to files
    mcst1->write("mcst1.txt");
    mcst2->write("mcst2.txt");
    mcst3->write("mcst3.txt");
}