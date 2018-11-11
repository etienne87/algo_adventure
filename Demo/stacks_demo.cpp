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

    try{
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
            SuperStack<int> lifo(1);
            lifo.push(1);
            lifo.push(2);
            lifo.push(3);
            lifo.push(4);
            int val = lifo.popAt(0);
            int val2 = lifo.popAt(0);
            std::cout<<val<<" "<<val2<<" "<<lifo<<std::endl;
        }else if(exo == 4){
            QueueViaStack fifo;
            fifo.push(1);
            fifo.push(2);
            fifo.push(3);
            fifo.push(4);
            int val1 = fifo.pop();
            fifo.push(5);
            int val2 = fifo.pop();
            fifo.push(6);
            int val3 = fifo.pop();
            fifo.push(7);
            std::cout<<val1<<" "<<val2<<" "<<val3<<" ";
            std::cout<<fifo.pop()<<" "<<fifo.pop()<<" "<<
            fifo.pop()<<" "<<fifo.pop()<<std::endl;
        }else if(exo == 5){
            SortedStack lifo;
            for(int i=0;i<10;i++){
                lifo.push(rand()%100);
            }
            for(int i=0;i<10;i++){
                std::cout<<lifo.pop()<<std::endl;
            }
        }        
        
    }catch(std::exception& e){
        std::cout<<"Error: "<<e.what()<<std::endl;
    }
    



}
