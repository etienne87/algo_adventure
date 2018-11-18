#include <iostream>
#include <cstdlib> 
#include <cstring>
#include <unordered_set>
#include <vector>
#include <deque>

using std::vector;
using std::pair;
using std::unordered_set;
using std::deque;

struct Node
{
    Node(int d=0):data(d){}
    std::vector<Node*> children;
    int data;
};

struct pair_hash {
    inline std::size_t operator()(const std::pair<int,int> & v) const {
        return v.first*31+v.second;
    }
};

vector<Node> build_directed_graph(int size=10, int max_connect=3){
    vector<Node> graph;
    graph.resize(size);
    unordered_set<pair<int,int>, pair_hash> visited;
    for(int u=0;u<size;++u){
        graph[u].data = rand()%100;
        int connections = rand()%max_connect;
        for(int j=0;j<connections;++j){
            int v = rand()%size;
            if(visited.find(pair<int,int>(v, u)) == visited.end()){
                graph[u].children.push_back(&graph[v]);
                visited.insert(pair<int,int>(u, v));
            }
        }
    }
    return graph;
}

vector<Node> build_binary_tree(int size=10){
    vector<Node> graph;
    graph.resize(size);
    for(int i=0;i<size;i++){
        graph[i].data = i;
        if(2*i+1 < size)
            graph[i].children.push_back(&graph[2*i+1]);
        if(2*i+2 < size)
            graph[i].children.push_back(&graph[2*i+2]);
    }

    return graph;
}

void print_graph(Node* node, bool dfs=true){
    if(dfs){
        deque<Node*> stack;
        stack.push_front(node);
        while(!stack.empty()){
            Node* node = stack.front();
            stack.pop_front();
            std::cout<<node->data<<std::endl;
            for(auto val: node->children){
                stack.push_front(val);
            }
        }
        
    }else{
        deque<Node*> queue;
        queue.push_back(node);
        while(!queue.empty()){
            Node* node = queue.front();
            queue.pop_front();
            std::cout<<node->data<<std::endl;
            for(auto val: node->children){
                queue.push_back(val);
            }
        }
        
    }
}

