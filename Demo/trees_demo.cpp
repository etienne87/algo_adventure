#include <ctime> 
#include <iostream>
#include <vector>
#include <time.h>
#include "trees.h"


int main(int argc, char* argv[]){
    srand(0);
    std::cout<<"Trees Demo"<<std::endl;
    int exo = 0;
    if(argc > 1)
        exo = atoi(argv[1]);

    try{
        vector<Node> graph = build_binary_tree();
        std::cout<<"bfs: "<<std::endl;
        std::cout<<"==========="<<std::endl;
        print_graph(&graph[0], false);
        std::cout<<"dfs: "<<std::endl;
        std::cout<<"==========="<<std::endl;
        print_graph(&graph[0], true);

    }catch(std::exception& e){
        std::cout<<"Error: "<<e.what()<<std::endl;
    }

    



}
