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

bool intersect(Node* rA, Node* rB){
    unordered_set<Node*> hash;
    deque<Node*> qA, qB;
    qA.push_back(rA);
    qB.push_back(rB);
    while(!qA.empty() && !qB.empty()){
        if(!qA.empty()){
            Node* a = qA.front();  
            if(hash.find(a) != hash.end())
                return true;   
            qA.pop_front();   
            for(auto val: a->children){
                qA.push_back(val);
            }
        }
        
        if(!qB.empty()){
            Node* b = qB.front();  
            if(hash.find(b) != hash.end())
                return true;   
            qB.pop_front();   
            for(auto val: b->children){
                qB.push_back(val);
            }
        }
    }

}

void minimal_tree(vector<Node>& tree, int low=0, int high=-1){  
    if(high < 0){
        high = tree.size();
    }
    int middle = (low+high)/2; 
    int left = (low+middle)/2;
    int right = (middle+high)/2;
    //std::cout<<"["<<low<<";"<<high<<"] | ["<<left<<" "<<middle<<" "<<right<<"]"<<std::endl;
   
    if(low < middle-2)
        minimal_tree(tree, low, middle);
    if(middle < high-2)
        minimal_tree(tree, middle, high); 
    if(left<middle)
        tree[middle].children.push_back(&tree[left]);
    if(middle<right)
        tree[middle].children.push_back(&tree[right]); 
}

vector<vector<Node*>> list_depth(Node* root){
    vector<vector<Node*>> levels;
    deque<pair<int,Node*>> stack; 
    stack.push_back(pair<int,Node*>(0,root));
    while(!stack.empty()){
        int level = stack.back().first;
        Node* a = stack.back().second; 
        if(level >= levels.size()){
            vector<Node*> vec;
            vec.push_back(a);
            levels.push_back(vec);
        }else{
            levels[level].push_back(a);
        }
        stack.pop_back();   
        for(auto val: a->children){
            stack.push_back(pair<int,Node*>(level+1,val));
        }
    }
    return levels;
}

void print_tree_by_levels(Node* root){
    vector<vector<Node*>> levels = list_depth(root);
    for(int i=0;i<levels.size();i++){
        for(int j=0;j<levels[i].size();j++){
            std::cout<<levels[i][j]->data<<",";
        }
        std::cout<<std::endl;
    }
}

bool is_balanced(Node* root){
    //1. reuse list_depth idea, len(list_depth[idx+1]) = 2 * len(list_depth[idx])
}

bool is_binary_search_tree(Node* root){
    //1. reuse is_balanced + first half < second half?
}

Node* in_order_successor(Node* tmp){
    //. in order is node/ left/ right
}

