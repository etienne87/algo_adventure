#include <iostream>
#include <cstdlib> 
#include <cstring>

struct Node
{
    Node(int d=0){
        data = d;
    }
    Node* next;
    int data;
};


class List{
public:
    List(int d=0){
        head = new Node(d);
    }
    ~List(){
        Node* curr = head;
        while(curr){
            Node* tmp = curr;
            curr = curr->next;
            delete tmp;
        }
    }
    Node* tail(){
        Node* tmp = head;
        while(tmp->next != NULL){
            tmp = tmp->next;
        }
        return tmp;
    }
    void append(int d){
        Node* tmp = tail();
        tmp->next = new Node(d);
    }

    friend std::ostream& operator<<(std::ostream& os, List const& tc) {
        Node* tmp = tc.head;
        while(tmp != NULL){
            os<<tmp->data<<" ";
            tmp = tmp->next;
        } 
        return os;
    }
    Node* get_head(){return head;}
private:
    Node* head;
    int data;
};


List build_random_list(int size, int maximum=100){
    List list(rand()%maximum);
    for(int i=0;i<size-1;++i){
        list.append(rand()%maximum);
    }
    return list;
}