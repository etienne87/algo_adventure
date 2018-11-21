#include <iostream>
#include <cstdlib> 
#include <cstring>
#include <unordered_set>
#include <unordered_map>
#include <list>
#include <vector>
#include <deque>

using std::vector;
using std::pair;
using std::list;
using std::unordered_set;
using std::unordered_map;
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
    if(left<middle)
        tree[middle].children.push_back(&tree[left]);
    if(middle<right)
        tree[middle].children.push_back(&tree[right]); 
    if(low < middle-2)
        minimal_tree(tree, low, middle);
    if(middle < high-2)
        minimal_tree(tree, middle, high); 
    
}


vector<vector<Node*>> list_depth(Node* root){
    vector<vector<Node*>> levels;
    deque<pair<int,Node*>> queue; 
    queue.push_back(pair<int,Node*>(0,root));
    while(!queue.empty()){
        int level = queue.back().first;
        Node* a = queue.back().second; 
        if(level >= levels.size()){
            vector<Node*> vec;
            vec.push_back(a);
            levels.push_back(vec);
        }else{
            levels[level].push_back(a);
        }
        queue.pop_back();   
        for(auto val: a->children){
            queue.push_front(pair<int,Node*>(level+1,val));
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

bool is_balanced(Node* tmp, int& count){
    //2 subtrees at same levels are never different in size more than 1
    int cnt_left = 0, cnt_right = 0;
    bool ck_left = true, ck_right = true;
    if(tmp->children.size())
        ck_left = is_balanced(tmp->children[0], cnt_left);
    if(tmp->children.size()>1)
        ck_right = is_balanced(tmp->children[1], cnt_right);
    if(!ck_left || !ck_right || abs(cnt_left-cnt_right) > 1)
        return false;
    count += 1 + cnt_left + cnt_right;
    return true;
}

bool is_bst(Node* tmp, int high){
    bool ck_left = true, ck_right = true;
    if(tmp->children.size()){
        int left = tmp->children[0]->data;
        if(left > tmp->data){
            return false;
        }
        ck_left = is_bst(tmp->children[0], tmp->data);
    }
    if(tmp->children.size() > 1){
        int right = tmp->children[1]->data;
        if(right < tmp->data || right > high){
            return false;
        }
        ck_right = is_bst(tmp->children[0], tmp->data);
    }
    return ck_right && ck_left;
}


struct Node2{
    Node2(int d=0, Node2* ancestor=NULL):data(d){
        left = right = NULL;
        parent = ancestor;
    }
    Node2* left, *parent, *right;
    int data;
};

//TODO:
//check this works
Node2* in_order_successor(Node2* tmp){
    //. in order is left/ node/ right/
    //. so if node->right, if left->parent, if right->right
    bool is_left = false;
    if(tmp->parent && tmp->parent->left == tmp)
        return tmp->parent;
    else
        return tmp->right;
}

//TODO:
//check this works
Node2* find_common_ancestor(Node2* a, Node2* b){
    Node2* pa = a, *pb = b;
    while(pa != pb && pa && pb){
        pa = pa->parent;
        if(pa == pb)
            return pa;
        pb = pb->parent;
        if(pa == pb)
            return pb;
    }
    return NULL;
}

//TODO
//built the graph while keeping track of the beginning of the queue?
//exo: detect a cycle dependency
vector<Node*> build_order(std::vector<pair<Node*,Node*>>& dependencies){
    vector<Node*> vec;
    Node* ancestor;
    unordered_map<Node*, Node*> mmap; //child to parent
    for(auto val: dependencies){
        Node* a = val.first;
        Node* b = val.second;
        a->children.push_back(b);
        unordered_map<Node*, Node*>::iterator it = mmap.find(b);
        if(it == mmap.end()){
            mmap.insert({a,b});
        }else{
            ancestor = a;
        }
    }
    //at this point, all 
    return vec;
}

//TODO
//find all possible ways to traverse an array left to right leading 
//to tree in argument
vector<vector<int>> bst_sequence(Node* root){
    vector<vector<int>> all_seq;
    return all_seq;
}

//TODO
//copy current node, perform traversal from here
//of t2 & node.
bool is_subtree(Node* t1, Node* t2){

}

