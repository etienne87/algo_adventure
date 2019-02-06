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
    if(exo == 2){
        vector<int> array(100);
        array[0] = 1;
        for(int i=1;i<100;i++){
            if(i > array[i-1] && array[i-1] != i-1)
                array[i] = i;
            else
                array[i] = array[i-1] + rand()%2 + 1; // assures distinct numbers
        }

        for(auto it: array)
            std::cout<<it<<" ";
        std::cout<<std::endl;

        int i = magic_index(array);
        std::cout<<"magic index: "<<i<<" "<<array[i]<<std::endl;
    }
    if(exo == 3){
        vector<int> array(5);
        for(int i=0;i<array.size();i++){
            array[i] = i;
        }
        auto subsets = power_set(array);
        int gtsize = 1<<5;
        std::cout<<"num subsets: "<<subsets.size()<< " "<<gtsize<<std::endl;
        for(auto subset: subsets){
            for(auto item: subset){
                std::cout<<item<<" ";
            }
            std::cout<<std::endl;
        }
    }
    if(exo == 4){
        stack<int> s1, s2, s3;
        int n = 20;
        for(int i=0;i<n;i++)
            s1.push(i);
        move_n_items(s1, s3, s2, n);
        for(int i=0;i<n;i++){
            std::cout<<pop(s3)<<std::endl;
        }
    }
    if(exo == 5){
        string chars = "abcd";
        permute_wo_dups(chars);
    }
}
