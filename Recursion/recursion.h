#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <set>

using std::string;
using std::vector;
using std::stack;
using std::queue;
using std::pair;
using std::make_pair;
using std::set;


int climb_stairs(int n, vector<int>& ways){
    vector<int> memo(n, 0);
    memo[0] = 1;
    for(int i=1;i<n;i++){
        for(int k=0;k<ways.size();k++){
            int j = i - ways[k];
            if(j >= 0)
                memo[i] += memo[j];
        }
    }
    return memo[n];
}

vector<vector<string>> robot_grid(vector<vector<bool>>& grid){
    vector<vector<string>> directions; //0: not visited, 1: right, 2: down
    stack<pair<int,int>> todo;
    int n = grid.size();
    directions.resize(n, vector<string>(n, " "));
    todo.push(make_pair(n-1, n-1));
    while(!todo.empty()){
        auto position = todo.top();
        todo.pop();
        int x = position.first;
        int y = position.second;

        std::cout<<x<<" "<<y<<std::endl;
     
        if( x-1 >= 0){
            if(grid[y][x-1] == 0 && directions[y][x-1] == " " ){ //if not off-limits & never visited
                todo.push(make_pair(x-1, y));
                directions[y][x-1] = ">"; //go right
                std::cout<<"left"<<std::endl;
            }
        }
        if( y-1 >= 0){
            if(grid[y-1][x] == 0 && directions[y-1][x] == " " ){ 
                todo.push(make_pair(x, y-1));
                directions[y-1][x] = "v"; //go down
                std::cout<<"up"<<std::endl;
            }
        }

       
    }
    return directions;
}

int magic_index(vector<int> arr){
    int low = 0;
    int high = arr.size()-1;
    int i = 0;
    while( low < high ){
        i = (high+low)/2;
        if(arr[i] == i){
            return i;
        }else if(arr[i] > i){
            high = i-1;
        }else{
            low = i+1;
        }
    }
    return -1;
}

vector<vector<int>> power_set(vector<int>& set){
    vector<vector<int>> subsets;
    for(int i=0;i<set.size();i++){
        if(subsets.empty()){
            subsets.push_back(vector<int>({set[i]}));
            subsets.push_back(vector<int>());
        }else{
            int len = subsets.size();
            for(int j=0;j<len;j++){
                vector<int> subset(subsets[j]);
                subset.push_back(set[i]);
                subsets.push_back(subset);
            }
        }
    }
    return subsets;
}

int multiply(int a, int b){
    int s = 0;
    for(int i=0;i<b;i++)
        s += a;
    return s;
}

template<class T>
T pop(stack<T>& src){
    auto it = src.top();
    src.pop();
    return it;
}

void move_n_items(stack<int>& src, stack<int>& dst, stack<int>& tmp, int n){
    //hanoi-tower problem:
    //move top (1-n-1) from src to tmp, move nth to dst, move back top (1-n-1) to dst
    if(n == 2){
        //base case -> move 1 to tmp, move 2 to dst, move 1 to dst
        tmp.push(pop(src));
        dst.push(pop(src));
        dst.push(pop(tmp));
    }else{
        move_n_items(src, tmp, dst, n-1); //put n-1 items to another buffer. (not src, not dst: tmp)
        dst.push(pop(src));//move nth item to dst
        move_n_items(tmp, dst, src, n-1); //put back n-1 items to dst from tmp.
    }
}

template<class T>
T popq(queue<T>& q){
    T item = q.front();
    q.pop();
    return item;
}

void permute_wo_dups(string& chars){
    queue<string> perm;
    string tmp = chars.substr(0,1);
    perm.push(tmp);

    for(int i=1;i<chars.size();i++){        
        int num = perm.size();
        for(int j=0;j<num;j++){
            string base = popq(perm);
            for(int k=0;k<base.size()+1;k++){
                tmp = base.substr(0,k) + chars[i] + base.substr(k, base.size());
                perm.push(tmp);
            } 
        }
    }
    
    //print all solutions...or return them
    int i = 0;
    while(!perm.empty()){
        std::cout<<i++<<" "<<popq(perm)<<std::endl;
    }
}

void permute_w_dups(string& chars){
    //TODO
}


void print_parens(int n, int nbits){
    int nopen = 0;
    for(int i=0;i<nbits;i++){
        int bit = (n & (1<<(nbits - 1 - i))) > 0;
        
        if(bit){
            nopen++;
            std::cout<<"(";
        }else{
            if(nopen>0){
                std::cout<<")";
                nopen--;
            }
            std::cout<<",()";
        } 
    }
    for(int i=0;i<nopen;i++){
        std::cout<<")";
    }
    std::cout<<std::endl;
}

void parens(int n){
    int max = 1<<n; //2^n options
    for(int i=0;i<max;i++){
        print_parens(i, n);
    }
}