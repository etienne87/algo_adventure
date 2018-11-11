#include <ctime> 
#include <iostream>
#include <vector>
#include <time.h>
#include "stacks.h"


int main(int argc, char* argv[]){
    srand(0);
    std::cout<<"Stacks Demo"<<std::endl;
    int exo = 0;
    if(argc > 1)
        exo = atoi(argv[1]);


    if(exo == 0){
        auto lifo = Stack<int>(0);
        auto fifo = Queue<int>(0);
        for(int i=1;i<10;i++){
            lifo.push(i);
            fifo.push(i);
        }
        std::cout<<"lifo: "<<lifo<<std::endl;
        std::cout<<"fifo: "<<fifo<<std::endl; 
    }else if(exo == 2){
        auto mins = MinStack<int>();
        for(int i=1;i<10;i++){
            int item = rand()%100;
            mins.push(item);
            std::cout<<mins.min()<<" "<<item<<std::endl;
        }
        std::cout<<"done pushing"<<std::endl;
        while(!mins.empty()){
            mins.pop();
            std::cout<<mins.min()<<" "<<mins.peek()<<std::endl;
        } 
    }else if(exo == 3){
        Stack<Stack<int>> lifo;
        std::cout<<lifo.get_tail()->data<<std::endl;
        
        //std::cout<<"lifo: "<<lifo<<std::endl;
        //std::cout<<"done pushing"<<std::endl;
    }  
    



}
