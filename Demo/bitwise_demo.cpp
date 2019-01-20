#include <ctime> 
#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>
#include "bitwise.h"
#include <bitset>

int main(int argc, char* argv[]){
    srand(0);
    std::cout<<"Bitwise Demo"<<std::endl;
    int exo = 0;
    if(argc > 1)
        exo = atoi(argv[1]);

    try{
      
    }catch(std::exception& e){
        std::cout<<"Error: "<<e.what()<<std::endl;
    }

    if(exo == 0){
        int N = 0b10111111101;
        int M = 0b0000010011;

        
        int R =  insert(N, M, 2, 6);
        std::cout<<std::bitset<12>(R)<<std::endl;

    }
    



}
