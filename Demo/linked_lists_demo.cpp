#include <ctime> 
#include <iostream>
#include <vector>
#include <time.h>
#include "linked_lists.h"


int main(int argc, char* argv[]){
    srand(0);
    std::cout<<"LinkedLists Demo"<<std::endl;

    auto list = build_random_list(10);
    std::cout<<"list: "<<list<<std::endl;

}
