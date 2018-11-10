#include <iostream>
#include <cstdlib> 
#include <cstring>
#include <unordered_set>


struct Node
{
    Node(int d=0){
        data = d;
        next = NULL;
    }
    Node* next;
    int data;
};

class Stack{
public:
    Stack(){
        tail = NULL;
    }
    Stack(int d){
        tail = new Node(d);
    }
    ~Stack(){
        while(tail){
            pop();
        }
        tail = NULL;
    }
    bool empty(){
        return tail == NULL;
    }
    int peek(){
        if(tail)
            return tail->data;
        else
            return -1;
    }
    void push(int item){
        Node* tmp = new Node(item);
        tmp->next = tail;
        tail = tmp;
    }
    int pop(){
        Node* tmp = tail;
        tail = tmp->next;
        int data = tmp->data;
        delete tmp;
        return data;
    }

    friend std::ostream& operator<<(std::ostream& os, Stack const& tc) {
        Node* tmp = tc.tail;
        while(tmp != NULL){
            os<<tmp->data<<" ";
            tmp = tmp->next;
        } 
        return os;
    }

public:
    Node* tail;
}; 

//A stack that can retrieve minimum in 0(1)
//BUGFIX: there is a bug in here with empty() function
class MinStack : public Stack{
public:
    MinStack():mins(){
        this->tail = NULL;
    }
    MinStack(int d):Stack(d){
        mins.push(d);
    }
    int min(){
        return mins.peek();
    }
    void push(int item){
        if(item < mins.peek() || mins.empty()){
            mins.push(item);
        }
        Stack::push(item);
    }
    int pop(){
        if( peek() == mins.peek())
            mins.pop();
        return Stack::pop();
    }

public:
    Stack mins;
};


class Queue{
public:
    Queue(){
        head = tail = NULL;
    }
    Queue(int d){
        head = tail = new Node(d);
    }
    ~Queue(){
        while(head){
            pop();
        }
        head = tail = NULL;
    }
    bool empty(){
        return head == tail == NULL;
    }
    int peek(){
        if(head)
            return head->data;
    }

    //extends tail
    void push(int item){
        Node* tmp = new Node(item);
        tail->next = tmp;
        tail = tmp;
    }

    //removes head
    int pop(){
        Node* tmp = head;
        head = tmp->next;
        int data = tmp->data;
        delete tmp;
        return data;
    }

    friend std::ostream& operator<<(std::ostream& os, Queue const& tc) {
        Node* tmp = tc.head;
        while(tmp != NULL){
            os<<tmp->data<<" ";
            tmp = tmp->next;
        } 
        return os;
    }

private:
    Node* head;
    Node* tail;
}; 

//A Single Queue using a simple array
class ArrayStack{
public:
    ArrayStack(int d=0){
        max_size = 16;
        array = new int[max_size];
        array[0] = d;
        size += 1;
    }
    ~ArrayStack(){
        delete []array;
        array = NULL;
        max_size = 0;
        size = 0;
    }
   

    bool is_empty(){
        return size == 0;
    }
    int peek(){
        return array[size-1];
    }
    void push(int item){
        if( size + 1 > max_size){
            extend();
        }
        array[size] = item;
        size += 1;
    }

    //removes head
    int pop(){
        int elem = peek();
        size -= 1;
        return elem;
    }

    friend std::ostream& operator<<(std::ostream& os, ArrayStack const& tc) {
    
        for(int i=tc.size-1;i>=0;i--){
            os<<tc.array[i]<<" ";
        }
        return os;
    }

private:
    int* array;
    int max_size;
    int size;

    void extend(){
        max_size *= 2;
        int* new_array = new int[max_size];
        memcpy(new_array, array, max_size*sizeof(int));
        delete []array;
        array = new_array;
    }
};

