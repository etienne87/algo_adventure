#include <ctime> 
#include <iostream>
#include <vector>
#include <time.h>
#include "linked_lists.h"


int main(int argc, char* argv[]){
    srand(0);
    std::cout<<"LinkedLists Demo"<<std::endl;

    auto list = List(4);
    //list.arange(10);
    list.append(4);
    list.append(4);
    list.append(5);
    list.append(4);
    list.append(7);
    list.append(3);
    list.append(3);
    list.append(5);
    list.append(6);
    list.append(7);
    
    std::cout<<"list: "<<list<<std::endl;

    //list.delete_nodes(4);
    //remove_duplicates(list);

    int klast = kth_last(list, 3);

    //std::cout<<"list: "<<list<<std::endl;

    std::cout<<"klast: "<<klast<<std::endl;
}
