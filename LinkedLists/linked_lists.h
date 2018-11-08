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

//swap and remove after instead!
void delete_middle_node(Node* node){
    Node* tmp = node;
    while(tmp && tmp->next->next){
        tmp->data = tmp->next->data;
        tmp = tmp->next;
    }
    delete tmp->next;
    tmp->next = NULL;
}

bool intersection(List& a, List& b){
    int len_a = a.get_size();
    int len_b = b.get_size();

    List* a_, *b_;
    if(len_a > len_b){
        a_ = &a;
        b_ = &b;
    }else{
        a_ = &b;
        b_ = &a;
        int tmp = len_b;
        len_b = len_a;
        len_a = tmp;
    }

    Node* aptr = a_->get_head();
    for(int i=0;i<len_a-len_b;i++){
        aptr = aptr->next;
    }
    Node* bptr = b_->get_head();
    for(int i=0;i<len_b;i++){
        if(aptr == bptr)
            return true;
        aptr = aptr->next;
        bptr = bptr->next;
    }
    
    return false;
}

void partition(List& list, int x){
    int size = list.get_size();
    Node* head = NULL;
    Node* tail = list.get_tail();

    Node* prev = NULL;
    Node* curr = list.get_head();
    for(int i=0;i<size;i++){
        if(curr->data >= x){
            if(!prev){
                head = curr->next;
            }else{
                prev->next = curr->next; //detach
            }
            tail->next = curr;
            tail = tail->next;
            tail->next = NULL;

            curr = prev->next;
        }else{
            prev = curr;
            curr = curr->next;
        }
    }
    if(head)
        list.set_head(head);
}

//could just translate & then do the op
int sum_lists(List& a, List& b){
    int sum = 0;
    Node* ah = a.get_head();
    Node* bh = b.get_head();
    int asize = a.get_size();
    int bsize = b.get_size();
    int diff = asize-bsize;

    Node* a_, *b_;
    int big, small;
    if(diff>0){
        a_ = ah;
        b_ = bh;
        big = asize;
        small = bsize;
    }else{
        b_ = ah;
        a_ = bh;
        big = bsize;
        small = asize;
    }
    for(int i=0;i<abs(diff);i++){
        sum *= 10;
        sum += a_->data;
        a_ = a_->next;
    }
    for(int i=0;i<small;i++){
        sum *= 10;
        sum += a_->data + b_->data;
        a_ = a_->next;
        b_ = b_->next;
    }
    
    return sum;
}

bool is_palindrome(List& list){
    Node* curr = list.get_head();
    
    Node* head = NULL;
    while(curr){
        Node* tmp = new Node(curr->data);
        tmp->next = head;
        head = tmp;
        curr = curr->next; 
    }

    bool check = true;
   
    curr = list.get_head();
    Node* rev = head;
    while(curr){
        if(rev->data != curr->data)
            check = false;
        rev = rev->next;
        curr = curr->next;
    }  

    //delete reverse
    curr = head;
    while(curr){
        Node* tmp = curr;
        curr = curr->next;
        delete tmp;
    } 
    return check;
}

//honestly, solve this shit with an hash-table...the 0(1) Memory solution i do not get it :-(
int detect_loop(List& list){
    Node* ptr1 = list.get_head();
    Node* ptr2 = list.get_head();

    int k = 2;

    int idx = 0;
    while(ptr1 != ptr2 && ptr1 && ptr2){
        
        ptr1 = ptr1->next;
        ptr2 = ptr2->next->next;
    }

}