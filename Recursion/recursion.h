#include <iostream>
#include <vector>
#include <stack>

using std::string;
using std::vector;
using std::stack;
using std::pair;
using std::make_pair;

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