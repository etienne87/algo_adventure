#include <ctime> 
#include <iostream>
#include <vector>
#include <time.h>
#include "trees.h"


int main(int argc, char* argv[]){
    srand(0);
    std::cout<<"Trees Demo"<<std::endl;
    int exo = 0;
    if(argc > 1)
        exo = atoi(argv[1]);

    try{
        
    }catch(std::exception& e){
        std::cout<<"Error: "<<e.what()<<std::endl;
    }



}
