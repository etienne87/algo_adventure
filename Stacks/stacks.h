#include <iostream>
#include <cstdlib> 
#include <cstring>
#include <unordered_set>
#include <list>

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
    Node* get_head(){
        return head;
    }
    void set_head(Node* tmp){
        head = tmp;
    }
    Node* get_tail(){
        Node* tmp = head;
        while(tmp->next != NULL){
            tmp = tmp->next;
        }
        return tmp;
    }
    void append(int d){
        Node* tmp = get_tail();
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
    
    int get_size(){
        int count = 0;
        Node* tmp = head;
        while(tmp){
            tmp = tmp->next;
            count++;
        }
        return count;
    }

    void fill_randomly(int size, int maximum){
        data = rand()%maximum;
        for(int i=0;i<size-1;i++){
            this->append(rand()%maximum);
        }
    }

    void arange(int size){
        data = 0;
        for(int i=1;i<size;i++){
            this->append(i);
        }
    }

    void delete_nodes(int d){
        Node* prev = NULL;
        Node* curr = head;
        while(curr){
            if(curr->data == d){
                if(prev == NULL){
                    head = head->next;
                    delete curr;
                    curr = head;
                }else if(curr->next == NULL){
                    delete curr;
                    prev->next = NULL;
                    curr = NULL;
                }else{
                    prev->next = curr->next;
                    delete curr;
                    curr = prev->next;
                }
            }else{
                prev = curr;
                curr = curr->next;
            } 
        }
    }
private:
    Node* head;
    int data;
};
