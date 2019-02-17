#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <tuple>

using std::string;
using std::vector;
using std::stack;
using std::queue;
using std::pair;
using std::make_pair;
using std::make_tuple;
using std::set;
using std::unordered_map;
using std::unordered_set;
using std::tuple;


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

void permute_dups(string& chars, bool use_set){
    queue<string> perm;
    string tmp = chars.substr(0,1);
    perm.push(tmp);

    for(int i=1;i<chars.size();i++){        
        int num = perm.size();

        unordered_set<string> set;
        for(int j=0;j<num;j++){
            string base = popq(perm);
            for(int k=0;k<base.size()+1;k++){
                tmp = base.substr(0,k) + chars[i] + base.substr(k, base.size());
                if(use_set){
                    if(set.find(tmp) == set.end()){
                        perm.push(tmp);
                        set.insert(tmp);
                    }
                }else
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

void parens(int npairs, string word="()"){
    if(npairs == 0){
        std::cout<<word<<std::endl;
        return;
    }
    //3 choices: (<solution>)| (),<solution> | <solution>,()
    string tmp = "(" + word + ")";
    parens(npairs-1, tmp);

    tmp = "()," + word;
    parens(npairs-1, tmp);
    
    tmp = word + ",()";
    parens(npairs-1, tmp);
}

typedef pair<int,int> point2d;
typedef tuple<int,int,int> color;

int get_group(unordered_map<int,int>& map, int src){
    auto it = map.find(src);
    while(it != map.end()){
        src = it->second;
        it = map.find(src);
    }
    return src;
}

void fill_update(vector<vector<int>>& groups, point2d& pt, color& new_color, 
                     unordered_map<int,int>& map,
                     vector<color>& colormaps){
    int height = groups.size();
    int width = groups[0].size();
    int ptx = pt.first;
    int pty = pt.second;
    int src = get_group(map, groups[pty][ptx]);
    for(int y=pty-1;y<pty+2;y++){
        if(y < 0 || y >= height)
            continue;
        for(int x=ptx-1;x<ptx+2;x++){
            if(x < 0 || x >= width)
                continue;
            if(x == ptx && pty == pty)
                continue;
            int dst = get_group(map, groups[y][x]);
            if(dst != src){
                if(colormaps[dst] == new_color){
                    map.insert(make_pair(src, dst)); // src now points to dst
                    src = dst;
                }
                
            }
        }
    }
}

int64_t makechange(int n, vector<int>& coins, int index){
    if(index >= 3)
        return 1;
    int coin = coins[index];
    int64_t count = 0;
    
    for(int i=0;i<n;i+=coin){
        count += makechange(n - i, coins, index+1);
    }
    return count;
}



void print_board(vector<int>& board){
    vector<vector<int>> hash(board.size());
    for(int i=0;i<board.size();i++)
        hash[i] = vector<int>(board.size(), 0);
    for(int y=0;y<board.size();y++){
        int x = board[y];
        hash[y][x] = 1;
    } 
    for(int y=0;y<board.size();y++){
        for(int x=0;x<board.size();x++)
            std::cout<<hash[y][x]<<" ";
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}

bool is_valid(vector<int>& board){
    int curr_row = board.size()-1;
    int curr_col = board.back();
    for(int row=0;row<board.size()-1;row++){
        int col = board[row];
        int diffcol = std::abs(curr_col-col);
        int diffrow = std::abs(curr_row-row);
        if(diffcol == 0 || diffrow == 0 || diffcol == diffrow)
            return false;
    }
    return true;
}

void nqueens(int n, vector<int>& board){
    if(n == board.size()){
        print_board(board);
    }
    for(int col=0;col<n;col++){
        board.push_back(col);
        if(is_valid(board)){
            nqueens(n, board);
        }
        board.pop_back();
    }
} 
typedef tuple<int,int,int> dims;

int stack_of_boxes(vector<dims>& whd, vector<vector<int>>& memo, int n=0, int height=0){
    //allocate memo array
    if(memo.size()==0){
        int total_height = 0;
        for(int i=0;i<whd.size();i++){
            total_height += std::get<1>(whd[i]);
        }
        memo.resize(whd.size());
        for(int i=0;i<whd.size();i++)
            memo[i].resize(total_height, 0);
    }
    if(n == whd.size()){
        return height;
    }
    int pw=0, ph=0, pd=0;
    if(n > 0){
        pw = std::get<0>(whd[n-1]);
        ph = std::get<1>(whd[n-1]);
        pd = std::get<2>(whd[n-1]);
    }
    
    int max_height = height;
    int curr_height = 0;
    for(int i=n;i<whd.size();i++){
        int w = std::get<0>(whd[i]);
        int h = std::get<1>(whd[i]);
        int d = std::get<2>(whd[i]);
        if(n == 0 || (w < pw && h < ph && d < pd)){
            if(memo[i][h] > 0){
                curr_height = memo[i][h];
            }else{
                curr_height = stack_of_boxes(whd, memo, i+1, height + h);
                memo[i][h] = curr_height;
            }
            max_height = std::max(max_height, curr_height);
        } 
    } 
    return max_height;
}

int count_eval(string& expr, bool result, unordered_map<string,int>& hash){
    if(expr.size() == 1){
        bool res = (bool)std::stoi(expr);
        return res == result;
    }
    int count = 0;
    for(int i=0;i<expr.size()-2;i+=2){
        string sub = expr.substr(i, 3);
        
        int v1 = std::stoi(sub.substr(0,1));
        char op = sub[1];
        int v2 = std::stoi(sub.substr(2,1));
        int v3 = 0; 

        if(op == '^')
            v3 = v1^v2;
        if(op == '|')
            v3 = v1|v2;
        if(op == '&')
            v3 = v1&v2;

        string reduced = expr.substr(0, i) + std::to_string(v3) + expr.substr(i+3, expr.size()-i-3);
        //std::cout<<reduced<<std::endl;
        int c = 0;
        if(hash.find(reduced) == hash.end()){
            c = count_eval(reduced, result, hash);
            if(c == 1){
                std::cout<<reduced<<std::endl;
            } 
            hash.insert(make_pair(reduced, c));
        }else{
            c = hash.find(reduced)->second;
        }
        count += c;
    }
    return count;
}