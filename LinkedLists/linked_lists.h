#include <iostream>
#include <cstdlib> 
#include <cstring>
#include <unordered_set>


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

void remove_duplicates(List& list){
    // if hash not allowed, then you need to sort first & then scan
    Node* prev = NULL;
    Node* curr = list.get_head();
    std::unordered_set<int> set;
    while(curr){
        if( set.find(curr->data) == set.end()){
            set.insert(curr->data);
            prev = curr;
            curr = curr->next;
        }else{  
            prev->next = curr->next;
            delete curr;
            curr = prev->next;
        }  
    }
}

int kth_last(List& list, int k){
    int idx = 0;
    Node* tmp = list.get_head();
    while(tmp->next != NULL){
        tmp = tmp->next;
        idx++;
    }
    idx -= k;
    tmp = list.get_head();
    for(int i=0;i<=idx;i++){
        tmp = tmp->next;
    }
    return tmp->data;
}

void delete_middle_node(Node* node){

}

void partition(List& list){

}

void sum_lists(List& list){

}

void is_palindrome(List& list){
    
}

int intersection(List& a, List& b){

}

int detect_loop(List& list){
    
}