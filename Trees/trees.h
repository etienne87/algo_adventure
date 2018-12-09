#include <iostream>
#include <sstream>
#include <cstdlib> 
#include <cstring>
#include <unordered_set>
#include <unordered_map>
#include <list>
#include <vector>
#include <deque>
#include <string>
#include <cmath>
#include <climits>


using std::vector;
using std::pair;
using std::list;
using std::unordered_set;
using std::unordered_map;
using std::deque;
using std::string;

template<class T>
struct Node
{
    Node(T d=0):data(d){}
    std::vector<Node<T>*> children;
    T data;
};
typedef Node<int> iNode;
typedef Node<string> sNode;

struct pair_hash {
    inline std::size_t operator()(const std::pair<int,int> & v) const {
        return v.first*31+v.second;
    }
};

//more specialized node with parent node
template<class T>
struct BTNode{
    BTNode(T d=0, BTNode* l=NULL, BTNode* r=NULL, BTNode* p=NULL):data(d){
       left = l;
       right = r;
       parent = p;
    }
    BTNode<T>* left, *parent, *right;
    T data;
};
typedef BTNode<int> iBTNode;


vector<iNode> build_directed_graph(int size=10, int max_connect=3){
    vector<iNode> graph;
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

vector<iNode> build_binary_tree(int size=10, bool random=false, int max_val=2){
    vector<iNode> graph;
    graph.resize(size);
    for(int i=0;i<size;i++){
        if(random)
            graph[i].data = rand()%max_val;
        else
            graph[i].data = i;
        if(2*i+1 < size)
            graph[i].children.push_back(&graph[2*i+1]);
        if(2*i+2 < size)
            graph[i].children.push_back(&graph[2*i+2]);
    }

    return graph;
}

vector<iBTNode> build_real_binary_tree(int size=10, bool random=false, int max_val=2){
    vector<iBTNode> tree;
    tree.resize(size);
    for(int i=0;i<size;i++){
        if(random)
            tree[i].data = rand()%max_val;
        else
            tree[i].data = i;
        if(2*i+1 < size)
            tree[i].left = &tree[2*i+1];
        if(2*i+2 < size)
            tree[i].right = &tree[2*i+2];
    }

    return tree;
}

void print_graph(iNode* node, bool dfs=true){
    if(dfs){
        deque<iNode*> stack;
        stack.push_front(node);
        while(!stack.empty()){
            iNode* node = stack.front();
            stack.pop_front();
            std::cout<<node->data<<std::endl;
            for(auto val: node->children){
                stack.push_front(val);
            }
        }
        
    }else{
        deque<iNode*> queue;
        queue.push_back(node); 
        while(!queue.empty()){
            iNode* node = queue.front();
            queue.pop_front();
            std::cout<<node->data<<std::endl;
            for(auto val: node->children){
                queue.push_back(val);
            }
        }
    }
}

bool intersect(iNode* rA, iNode* rB){
    unordered_set<iNode*> hA, hB;
    deque<iNode*> qA, qB;
    qA.push_back(rA);
    qB.push_back(rB);
    while(!qA.empty() || !qB.empty()){
        iNode* a=NULL, *b=NULL;
        if(!qA.empty()){
            a = qA.front();
            if(hB.find(a) == hB.end()){
                hA.insert(a);
            }else{
                return true;
            }
            qA.pop_front();   
            for(auto val: a->children){
                if(hA.find(val) == hA.end())
                    qA.push_back(val);
            }
        }
        if(!qB.empty()){
            b = qB.front();  
            if(hA.find(b) == hA.end()){
                hB.insert(b);
            }else{
                return true;
            }
            qB.pop_front();   
            for(auto val: b->children){
                if(hB.find(val) == hB.end())
                    qB.push_back(val);
            }
        }
        if(a == b)
            return true;
    }
    return false;
}

void minimal_tree(vector<iBTNode>& tree, int low=0, int high=-1){  
    if(high < 0){
        high = tree.size();
    }
    int middle = (low+high)/2; 
    int left = (low+middle)/2;
    int right = (middle+high)/2;
    //std::cout<<"["<<low<<";"<<high<<"] | ["<<left<<" "<<middle<<" "<<right<<"]"<<std::endl;
    if(left<middle)
        tree[middle].left = &tree[left];
    if(middle<right)
        tree[middle].right = &tree[right];
    if(low < middle-2)
        minimal_tree(tree, low, middle);
    if(middle < high-2)
        minimal_tree(tree, middle, high); 
    
}

vector<vector<iBTNode*>> tree_list_depth(iBTNode* root){
    vector<vector<iBTNode*>> levels;
    //simpler to explain
    deque<iBTNode*> queue;
    queue.push_front(root);
    while(!queue.empty()){
        vector<iBTNode*> level; 
        int len = queue.size();  
        for(int i=0;i<len;i++){
            auto* node = queue.back();
            queue.pop_back();
            level.push_back(node);
            if(node->left)
                queue.push_front(node->left);
            if(node->right)
                queue.push_front(node->right);
        }
        levels.push_back(level);
    } 
    return levels;
}

void print_tree_by_levels(iBTNode* root){
    vector<vector<iBTNode*>> levels = tree_list_depth(root);
    for(int i=0;i<levels.size();i++){
        for(int j=0;j<levels[i].size();j++){
            std::cout<<levels[i][j]->data<<",";
        }
        std::cout<<std::endl;
    }
}

bool is_tree_balanced(iBTNode* tmp, int& depth){
    if(!tmp)
        return true;
    int depth_left = 0, depth_right = 0;
    if(tmp->left)
        if(!is_tree_balanced(tmp->left, ++depth_left))
            return false;
    if(tmp->right)
        if(!is_tree_balanced(tmp->right, ++depth_right))
            return false;
    if(abs(depth_left-depth_right) > 1)
        return false;
    depth += std::max(depth_left, depth_right);
    return true;
}

bool is_tree_bst(iBTNode* tmp, int low=INT_MIN, int high=INT_MAX){
    //std::cout<<"range: ["<<low<<";"<<high<<"]"<<std::endl;
    int data = tmp->data;
    if(tmp->right){
        int right = tmp->right->data;
        if(right >= low && right <= high && right >= data){
            if(!is_tree_bst(tmp->right, data, high))
                return false;
        }else{
            //std::cout<<"["<<low<<";"<<high<<"] -> right: "<<right<<std::endl;
            return false;
        }
    }

    if(tmp->left){
        int left = tmp->left->data;
        if(left >= low && left <= high && left <= data){
            if(!is_tree_bst(tmp->left, low, data))
                return false;
        }else{
            //std::cout<<"["<<low<<";"<<high<<"] -> left: "<<left<<std::endl;
            return false;
        }
    }
    return true;
}


//general implementation for any graph
vector<vector<iNode*>> graph_list_depth(iNode* root){
    vector<vector<iNode*>> levels;
    deque<pair<int,iNode*>> queue; 
    queue.push_back(pair<int,iNode*>(0,root));
    while(!queue.empty()){
        int level = queue.back().first;
        iNode* a = queue.back().second; 
        if(level >= levels.size()){
            vector<iNode*> vec;
            vec.push_back(a);
            levels.push_back(vec);
        }else{
            levels[level].push_back(a);
        }
        queue.pop_back();   
        for(auto val: a->children){
            queue.push_front(pair<int,iNode*>(level+1,val));
        }
    }
    return levels;
}

void print_graph_by_levels(iNode* root){
    vector<vector<iNode*>> levels = graph_list_depth(root);
    for(int i=0;i<levels.size();i++){
        for(int j=0;j<levels[i].size();j++){
            std::cout<<levels[i][j]->data<<",";
        }
        std::cout<<std::endl;
    }
}

//TODO:
//check this works
template<class T>
BTNode<T>* in_order_successor(BTNode<T>* tmp){
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
template<class T>
BTNode<T>* find_common_ancestor(BTNode<T>* a, BTNode<T>* b){
    BTNode<T>* pa = a, *pb = b;
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


vector<string> build_order(vector<string> vec, vector<pair<string, string>> map){
    /* some comment here to better understand my own code :
       1. build a map name: node<string>
       2. build the graph, find root 
       (if root is a tail, root become the current head given by list of dependencies)
       3. parse the graph breadth-first, starting from root with an hash to avoid any duplications.
    */
    vector<string> ordered;
    unordered_map<string, sNode> nodes;
    for(auto val: vec){
        auto a = sNode(val);
        nodes.insert(pair<string, sNode>(val, a));
    }
    sNode* root = NULL;
    for(auto val: map){
        string a = val.first;
        string b = val.second;
        
        auto node1 = &nodes.find(a)->second;
        auto node2 = &nodes.find(b)->second;
        node1->children.push_back(node2);
        
        if(root == NULL || root == node2){
            root = node1;
        }
    }  
    //NOW: BFS
    deque<sNode*> queue;
    queue.push_back(root);
    
    unordered_set<string> inside;
    
    while(!queue.empty()){
        sNode* node = queue.front();

        if( inside.find(node->data) == inside.end()){
            inside.insert(node->data);
            ordered.push_back(node->data);
        }

        queue.pop_front();
        for(auto val: node->children){
            queue.push_back(val);
        }
    }
    for(auto val: vec){
        if( inside.find(val) == inside.end()){
            ordered.push_back(val);
        }
    }
    
    
    return ordered;
}

template<class T>
void swap(T* a, T* b){
    T tmp = *b;
    *b = *a;
    *a = tmp;
}

template<class T>
void permute(T* s, int l, int r){
    if(l==r){
        for(int i=0;i<=r;i++){
            std::cout<<s[i]<<",";
        }
        std::cout<<std::endl;
    }
    else{
        for(int i=l;i<=r;i++){
            swap(&s[l], &s[i]);
            permute(s, l+1, r);
            swap(&s[l], &s[i]); //backtrack
        }
    }
}

//TODO: 
//by level, any permutation could have lead to the same binary tree.
//some we need to retrieve nodes by levels, & generate any permutation?
vector<vector<int>> bst_sequence(iNode* root){
    vector<vector<int>> all_seq;
    //all we need is run bfs, each level we generate 2**N permutations and add them.
    auto list =  graph_list_depth(root);
    for(auto vec: list){
        vector<int> vals;
        for(auto val: vec)
            vals.push_back(val->data);
        permute(&vals[0], 0, vec.size()-1);
    }
    return all_seq;
}

bool tree_equal(iBTNode* t1, iBTNode* t2){
    if(t1 == NULL && t2 == NULL)
        return true;
    if(t1->data == t2->data){
        bool check = true;
        check &= tree_equal(t1->left, t2->left);
        check &= tree_equal(t1->right, t2->right);
        return check;
    }else{
        return false;
    }
}

bool is_subtree(iBTNode* t1, iBTNode* t2){
    if(!t1){
        return false;
    }
    if(tree_equal(t1, t2)){
        return true;
    }
    else{
        bool check = false;
        check |= is_subtree(t1->left, t2);
        check |= is_subtree(t1->right, t2);
        return check;
    }
}

bool graph_equal(iNode* t1, iNode* t2){
    if(t1->data == t2->data && t1->children.size() == t2->children.size()){
        bool check = true;
        for(int i=0;i<t1->children.size();i++){
            check &= graph_equal(t1->children[i], t2->children[i]);
        }
        return check;
    }else{
        return false;
    }
}

bool is_subgraph(iNode* t1, iNode* t2){
    if(!t1)
        return false;
    if(graph_equal(t1, t2)){
        return true;
    }
    else{
        bool check = false;
        for(auto val: t1->children){
            check |= is_subgraph(val, t2);
        }
        return check;
    }
}

//Array Implementation
//Allows to retrieve a random node
//getLeftChild(idx) = 2*idx + 1
//getRightChild(idx) = 2*idx + 2
class BinaryTree{
public:
    BinaryTree(int data, int capacity=16){
        nodes.reserve(capacity);
        nodes[0] = data;
    }
    int findNode(int data){
        //run dfs
        deque<int> stack;
        stack.push_back(0);
        while(!stack.empty()){
            int idx = stack.back();
            stack.pop_back();
            if(idx > 0){
                if(nodes[idx] == data){
                    return idx;
                }
                int left = getLeftChild(idx);
                int right = getRightChild(idx);
                if(left)
                    stack.push_back(left);
                if(right)
                    stack.push_back(right);
            }
        }
    }
    int deleteNode(int idx){
        int parent = std::floor(float(idx-1)/2);
        if(parent==-1)
            nodes.resize(0);
        else{
            int left = getLeftChild(parent);
            int right = getRightChild(parent);
            if( ((left == idx) && (right < 0)) ||
                ((left == idx) && (right < 0))){
                nodes.resize(parent);
            }
        }
    }
    int getRandomNode(){
        return nodes[rand()%nodes.size()];
    }
    int insertLeft(int idx, int data){
        int left = getLeftChild(idx);
        if(left < 0){
            nodes.resize(nodes.capacity()*2);
        }
        nodes[left] = data;
        return left;
    }
    int insertRight(int idx, int data){
        int right = getRightChild(idx);
        if(right < 0){
            nodes.resize(nodes.capacity()*2);
        }
        nodes[right] = data;
        return right;
    }
    int getLeftChild(int idx){
        int index = 2 * idx + 1;
        if(index < nodes.size())
            return index;
        else
            return -1;
    }
    int getRightChild(int idx){
        int index = 2 * idx + 2;
        if(index < nodes.size())
            return index;
        else
            return -1;
    }

private:
    vector<int> nodes;
};

int count_paths_sum(iNode* root, int partial_sum, int ref_sum){
    /*comment to better understand my code:
        - each time partial sum = ref sum, we increment num_paths & return it
        - we run this recursively (dfs) for every children
    */
    int num_paths = 0;
    if(!root)
        return num_paths;
    partial_sum += root->data;
    if(partial_sum == ref_sum){
        num_paths += 1;
    }
    for(auto child: root->children)
        num_paths += count_paths_sum(child, partial_sum, ref_sum);

    return num_paths;
}