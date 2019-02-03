#include <ctime> 
#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>
#include "recursion.h"


int main(int argc, char* argv[]){
    srand(0);
    std::cout<<"Recursion Demo"<<std::endl;
    int exo = 0;
    if(argc > 1)
        exo = atoi(argv[1]);

    if(exo == 0){
        std::cout<<"climb stairs"<<std::endl;
        vector<int> ways{ 1, 2, 3 }; 
        int n = climb_stairs(10, ways);
        std::cout<<n<<" ways to climb 100 stairs"<<std::endl;
    }
    if(exo == 1){
        std::cout<<"robot grid"<<std::endl;
        int n = 6;
        vector<vector<bool>> grid(n);
        grid[0] = vector<bool>({0, 0, 1, 0, 0, 0});
        grid[1] = vector<bool>({1, 0, 0, 1, 0, 0});
        grid[2] = vector<bool>({0, 1, 0, 1, 0, 0});
        grid[3] = vector<bool>({0, 1, 0, 1, 0, 0});
        grid[4] = vector<bool>({0, 1, 0, 1, 1, 1});
        grid[5] = vector<bool>({0, 1, 0, 0, 0, 0});

        auto path = robot_grid(grid);
        for(auto it: path){
            for(auto jt: it)
                std::cout<<jt<<" ";
            std::cout<<std::endl;
        }

    }
}
