#include <iostream>
#include <cstdlib> 
#include <cstring>
#include <unordered_set>
#include <exception>

template<class T>
struct Node
{
    Node(){
        std::cout<<"Node ctor neutral called"<<std::endl;
        next = NULL;
    }
    //interesting to remind: if you put here data = d, and you forget to make a operator =  for your T class
    //then it will be deleted twice!
    //here we call the copy ctor bc we made one, but it is also likely to crash if you forget to implement one
    //Also we pass by reference, in order to avoid a copy
    Node(const T& d):data(d){
        next = NULL;
    }
    Node* next;
    T data;
};
