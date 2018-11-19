#include <ctime> 
#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>
#include "trees.h"


int main(int argc, char* argv[]){
    srand(0);
    std::cout<<"Trees Demo"<<std::endl;
    int exo = 0;
    if(argc > 1)
        exo = atoi(argv[1]);

    try{
        if(exo == 0){
            vector<Node> graph = build_binary_tree();
            std::cout<<"bfs: "<<std::endl;
            std::cout<<"==========="<<std::endl;
            print_graph(&graph[0], false);
            std::cout<<"dfs: "<<std::endl;
            std::cout<<"==========="<<std::endl;
            print_graph(&graph[0], true);

            auto levels = list_depth(&graph[0]);
        }
        if(exo == 1){
            vector<Node> graph = build_directed_graph();
            //Take 2 random node
            Node* a = &graph[rand()%graph.size()];
            Node* b = &graph[rand()%graph.size()];
            bool check = intersect(a, b);
            if(check){
                std::cout<<"a & b intersect"<<std::endl;
            }
        }
        if(exo == 2 || exo == 3){
            vector<int> array;
            for(int i=0;i<16;i++){
                array.push_back(rand()%100);
            }
            std::sort(array.begin(), array.end());

            /* for(auto i: array)
                std::cout<<i<<" ";
            std::cout<<std::endl; */

            vector<Node> tree;
            tree.resize(array.size());
            for(int i=0;i<array.size();i++){
                tree[i].data = array[i];
            }
            minimal_tree(tree);
          
            print_tree_by_levels(&tree[tree.size()/2]);
        }
       
    }catch(std::exception& e){
        std::cout<<"Error: "<<e.what()<<std::endl;
    }

    



}
