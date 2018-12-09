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
            auto tree = build_binary_tree();
            std::cout<<"bfs: "<<std::endl;
            std::cout<<"==========="<<std::endl;
            print_graph(&tree[0], false);
            std::cout<<"dfs: "<<std::endl;
            std::cout<<"==========="<<std::endl;
            print_graph(&tree[0], true);
            print_graph_by_levels(&tree[0]);
        }
        if(exo == 1){
            auto graph = build_directed_graph();
            auto graph2 = build_directed_graph();
            //Take 2 random node
            auto* a = &graph[0];
            auto* b = &graph[7];
            auto* c = &graph2[0];
            bool check = intersect(a, b);
            bool check2 = intersect(a, c);
            if(check){
                std::cout<<"a & b intersect"<<std::endl;
            }else{
                std::cout<<"a & b do not intersect"<<std::endl;
            }
            if(check2){
                std::cout<<"a & c intersect"<<std::endl;
            }else{
                std::cout<<"a & c do not intersect"<<std::endl;
            }
        }
        if(exo == 2 || exo == 3){
            vector<int> array;
            for(int i=0;i<16;i++){
                array.push_back(rand()%100);
            }
            std::sort(array.begin(), array.end());

            vector<iBTNode> tree;
            tree.resize(array.size());
            for(int i=0;i<array.size();i++){
                tree[i].data = array[i];
            }
            minimal_tree(tree);
            print_tree_by_levels(&tree[tree.size()/2]);
        }
        if(exo == 4){
            vector<iBTNode> nodes(6);
            nodes[0].left = &nodes[1];
            nodes[0].right = 0;
            nodes[1].left = &nodes[3];
            nodes[1].right = 0;
            nodes[2].left = 0;
            nodes[2].right = 0;

            int depth = 0;
            if(is_tree_balanced(&nodes[0], depth)){
                std::cout<<"is balanced!"<<std::endl;
            }else{
                std::cout<<"not balanced!"<<std::endl;
            }

            nodes[0].right = &nodes[2];
            nodes[1].right = &nodes[4];

            if(is_tree_balanced(&nodes[0], depth)){
                std::cout<<"is balanced!"<<std::endl;
            }else{
                std::cout<<"not balanced!"<<std::endl;
            }
        }
        if(exo == 5){
            vector<int> array;
            for(int i=0;i<16;i++){
                array.push_back(rand()%100);
            }
            std::sort(array.begin(), array.end());

            vector<iBTNode> tree;
            tree.resize(array.size());
            for(int i=0;i<array.size();i++){
                tree[i].data = array[i];
            }
            minimal_tree(tree);
            print_tree_by_levels(&tree[tree.size()/2]); 

            if(is_tree_bst(&tree[tree.size()/2])){
                std::cout<<"is a binary search tree!"<<std::endl;
            }else{
                std::cout<<"not a bst"<<std::endl;
            }  
            
            //deserialize a tree
            int example[] = {5,3,7,2,4,6,10,1,4};
            vector<iBTNode> nodes(9);
            for(int i=0;i<9;i++)
                nodes[i].data = example[i];
            deque<int> queue;
            queue.push_back(0);
            while(!queue.empty()){
                int i = queue.back();
                queue.pop_back();
                auto* node = &nodes[i];
                if((2*i+1)<9){
                    node->left = &nodes[2*i+1];
                    queue.push_front(2*i+1);
                }
                if((2*i+2)<9){
                    node->right = &nodes[2*i+2];
                    queue.push_front(2*i+2);
                }
            }
            print_tree_by_levels(&nodes[0]);

            if(is_tree_bst(&nodes[0])){
                std::cout<<"is a binary search tree!"<<std::endl;
            }else{
                std::cout<<"not a bst"<<std::endl;
            }  
        }

        if(exo == 6){
            vector<string> projects;
            projects.push_back("a");
            projects.push_back("b");
            projects.push_back("c");
            projects.push_back("d");
            projects.push_back("e");
            projects.push_back("f");
            vector<pair<string, string>> dependencies;
            dependencies.push_back(pair<string,string>("a","d"));
            dependencies.push_back(pair<string,string>("f","b"));
            dependencies.push_back(pair<string,string>("b","d"));
            dependencies.push_back(pair<string,string>("f","a"));
            dependencies.push_back(pair<string,string>("d","c")); 
            dependencies.push_back(pair<string,string>("e","")); 

            auto res = build_order(projects, dependencies);

            for(auto val: res){
                std::cout<<val<<" ";
            }
            std::cout<<std::endl;
            
        }

        if(exo == 7){
            auto tree = build_real_binary_tree(16);
            auto* root = &tree[0];
            auto* subtree = &tree[2];
            
            print_tree_by_levels(&tree[0]);

            if(is_subtree(root, subtree)){
                std::cout<<"is subtree indeed"<<std::endl;
            }else{
                std::cout<<"not a subtree"<<std::endl;
            }
        }
       
        if(exo == 8){
            auto tree = build_binary_tree(32, true);
            auto* root = &tree[0];

            for(auto val: tree)
                std::cout<<val.data<<" ";
            std::cout<<std::endl;
            
            int sum = 3;
            int npaths = count_paths_sum(root, 0, sum);
            std::cout<<"num paths: "<<npaths<<std::endl;
        }

        if(exo == 9){
            std::string test = "ABC";
            permute<char>(&test[0], 0, 2);

            auto tree = build_binary_tree(7, true, 32);
            bst_sequence(&tree[0]);
        }
    }catch(std::exception& e){
        std::cout<<"Error: "<<e.what()<<std::endl;
    }

    



}
