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

template<class T>
class Stack{
public:
    Stack(){
        tail = NULL;
        size = 0;
    }
    Stack(T d){
        tail = NULL;
        size = 0;
        push(d);
    }
    Stack(const Stack<T>& cpy):tail(NULL), size(0){
        Node<T>* tmp = cpy.tail;
        while(tmp != NULL){
            push(tmp->data);
            tmp = tmp->next;
        }
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
    T peek(){
        if(tail)
            return tail->data;
        else
            return -1;
    }
    void push(const T& item){
        auto* tmp = new Node<T>(item); 
        tmp->next = tail;
        tail = tmp;
        size++;
    }
    T pop(){
        size--;
        Node<T>* tmp = tail;
        tail = tmp->next;
        T data = tmp->data;
        delete tmp;
        return data;
    }

    friend std::ostream& operator<<(std::ostream& os, Stack const& tc) {
        Node<T>* tmp = tc.tail;
        while(tmp){
            os<<tmp->data<<" ";
            tmp = tmp->next;
        } 
        return os;
    }
    int get_size(){return size;}
    Node<T>* get_tail(){return tail;}
    void set_tail(Node<T>* tmp){tail = tmp;}
protected:
    Node<T>* tail;
    int size;
}; 

//Implemented as a Stack of Stack using templates!
class SuperStack{
public:
    SuperStack(int cap=16){
        size = 0;
        capacity = cap;
        if(capacity == 0){
            throw std::logic_error("Stack won't work with 0 capacity");
        }
    }

    bool empty(){
        return super.empty();
    }

    int peek(){
        if(!empty())
            return super.get_tail()->data.peek();
    }
   
    void push(int item){
       if(empty() || super.get_tail()->data.get_size() >= capacity){
           Stack<int> tmp(item);
           super.push(tmp);
           size++;
       }else{
           super.get_tail()->data.push(item);
       }
    }
    
    int pop(){
        if(!empty()){
            int value = super.get_tail()->data.pop();
            if(super.get_tail()->data.empty()){
                super.pop();
                size--;
            }
            return value;
        }
    }

    int popAt(int idx){
        if(idx < 0 || idx > size-1)
            throw std::logic_error("index > stack.size");
        Node<Stack<int>>* curr = super.get_tail();
        Node<Stack<int>>* prev = NULL;
        for(int i=0;i<idx-1;i++){
            prev = curr;
            curr = curr->next;
        }
        int value = curr->data.pop();
        if(curr->data.empty()){
            Node<Stack<int>>* tmp = curr;
            if(!prev){
                super.set_tail(curr->next);
            }else{
                prev->next = curr->next;
            }
            delete tmp;
        }
        return value;
    }

    friend std::ostream& operator<<(std::ostream& os, SuperStack& tc) {
        os<<tc.super;
        return os;
    }
    
    int get_size(){return size;}
private:
    Stack<Stack<int>> super;
    int capacity;
    int size;
};  



//A stack that can retrieve minimum in 0(1)
//BUGFIX: there is a bug in here with empty() function
template<class T>
class MinStack : public Stack<T>{
public:
    MinStack():mins(){
        this->tail = NULL;
    }
    MinStack(int d):Stack<T>(d){
        mins.push(d);
    }
    int min(){
        return mins.peek();
    }
    void push(int item){
        if(item < mins.peek() || mins.empty()){
            mins.push(item);
        }
        Stack<T>::push(item);
    }
    int pop(){
        if( Stack<T>::peek() == mins.peek())
            mins.pop();
        return Stack<T>::pop();
    }

public:
    Stack<T> mins;
};

template<class T>
class Queue{
public:
    Queue(){
        head = tail = NULL;
    }
    Queue(int d){
        head = tail = new Node<T>(d);
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
    T peek(){
        if(head)
            return head->data;
    }

    //extends tail
    void push(const T& item){
        auto* tmp = new Node<T>(item);
        tail->next = tmp;
        tail = tmp;
    }

    //removes head
    T pop(){
        Node<T>* tmp = head;
        head = tmp->next;
        T data = tmp->data;
        delete tmp;
        return data;
    }

    friend std::ostream& operator<<(std::ostream& os, Queue<T> const& tc) {
        Node<T>* tmp = tc.head;
        while(tmp != NULL){
            os<<tmp->data<<" ";
            tmp = tmp->next;
        } 
        return os;
    }

private:
    Node<T>* head;
    Node<T>* tail;
}; 

//A Single Queue using a simple array (goal is then to design 3 different stacks inside this array)
template<class T>
class ArrayStack{
public:
    ArrayStack(int d=0){
        max_size = 16;
        array = new T[max_size];
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
    T* array;
    int max_size;
    int size;

    void extend(){
        max_size *= 2;
        T* new_array = new int[max_size];
        memcpy(new_array, array, max_size*sizeof(T));
        delete []array;
        array = new_array;
    }
};

//first push to s1
//then as popping from s1, push to s2
class QueuebyStack{

private:
    Stack<int> s1, s2;
};