#include <iostream>
#include <cstdlib> 
#include <cstring>
#include <unordered_set>
#include <exception>

template<class T>
struct Node
{
    Node(){
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
template<class T>
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
   
    void push(const T& item){
       if(empty() || super.get_tail()->data.get_size() >= capacity){
           Stack<T> tmp(item);
           super.push(tmp);
           size++;
       }else{
           super.get_tail()->data.push(item);
       }
    }
    
    T pop(){
        if(!empty()){
            T value = super.get_tail()->data.pop();
            if(super.get_tail()->data.empty()){
                super.pop();
                size--;
            }
            return value;
        }
    }

    T popAt(int idx){
        if(idx < 0 || idx > size-1)
            throw std::logic_error("index > stack.size");
        Node<Stack<T>>* curr = super.get_tail();
        Node<Stack<T>>* prev = NULL;
        for(int i=0;i<idx-1;i++){
            prev = curr;
            curr = curr->next;
        }
        int value = curr->data.pop();
        if(curr->data.empty()){
            Node<Stack<T>>* tmp = curr;
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
    Stack<Stack<T>> super;
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
        size = 0;
    }
    Queue(T d){
        head = tail = NULL;
        size = 0;
        push(d);
    }
    Queue(const Queue<T>& cpy){
        head = tail = NULL;
        Node<T>* tmp = cpy.head;
        while(tmp != NULL){
            push(tmp->data);
            tmp = tmp->next;
        } 
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
        if(tail)
            tail->next = tmp;
        tail = tmp;
        if(!head)
            head = tail;
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

    Node<T>* get_head(){return head;}
    Node<T>* get_tail(){return tail;}
    
    void set_head(Node<T>* h){head = h;}
    void set_tail(Node<T>* t){tail = t;}

private:
    Node<T>* head;
    Node<T>* tail;
    int size;
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
class QueueViaStack{
public:
    void push(const int& item){
        s1.push(item);
    }
    int pop(){
        if(s2.empty())
            transfer();
        int val = s2.pop();
        return val;
    }
    void transfer(){
        while(!s1.empty()){
           s2.push(s1.pop());
        }
    }
private:
    Stack<int> s1, s2;
};

class SortedStack{
public:
    void push(const int& item){
        if(main.empty()){
            main.push(item);
        }else{
            //O(N) to insert!
             Stack<int> tmp;
             while(main.peek() < item && !main.empty()){
                 tmp.push(main.pop());
             }
             main.push(item);
             while(!tmp.empty()){
                main.push(tmp.pop());
             }
        }
    }
    int pop(){
        return main.pop();
    }    
private:
    Stack<int> main;
};

struct Animal{
    Animal(std::string n, bool dog){
        name = n;
        is_dog = dog;
    }
    std::string name;
    bool is_dog;
    int age;
};

class AnimalShelter{
public:
    AnimalShelter(){
        count = 0;
    }
    void push(Animal& pet){
        pet.age = count++;
        if(pet.is_dog){
            dogs.push(pet);
        }else{
            cats.push(pet);
        }
    }
    Animal dequeueAny(){
        int dog_age = dogs.peek().age;
        int cat_age = cats.peek().age;
        if(dog_age < cat_age){
            return dogs.pop();
        }else{
            return cats.pop();
        }
    }    
    Animal dequeuePet(bool is_dog){
        if(is_dog)
            return dogs.pop();
        else
            return cats.pop();
    } 

private:
    Queue<Animal> cats; 
    Queue<Animal> dogs;
    int count;
};