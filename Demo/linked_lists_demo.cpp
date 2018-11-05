#include <ctime> 
#include <iostream>
#include <vector>
#include <time.h>
#include "linked_lists.h"


int main(int argc, char* argv[]){
    srand(0);
    std::cout<<"LinkedLists Demo"<<std::endl;

    /*
    auto list = List(4);
    //list.arange(10);
    list.append(4);
    list.append(4);
    list.append(5);
    list.append(4);
    list.append(7);
    list.append(3);
    list.append(3);
    list.append(5);
    list.append(6);
    list.append(7); 
    
    std::cout<<"list: "<<list<<std::endl;

    //list.delete_nodes(4);
    remove_duplicates(list); 
    std::cout<<"2.1 duplicate removal: "<<list<<std::endl;

 
    int klast = kth_last(list, 3);
    std::cout<<"2.2 kth last: "<<klast<<std::endl;

    Node* node = list.get_head();
    node = node->next->next;

    delete_middle_node(node);
    std::cout<<"2.3 middle node removal: "<<list<<std::endl;

    List a = List(0);
    a.arange(10);
    List b = List(0);
    b.arange(5);

    //create intersection
    Node* a_end = a.get_tail();
    Node* b_end = b.get_tail();

    Node* tmp = new Node(11); 

    a_end->next = tmp;
    b_end->next = tmp;

    a.append(12);
    a.append(13);

    bool inter = intersection(a, b);
    std::cout<<"2.7 does intersect? "<<inter<<std::endl;

    std::cout<<"a: "<<a<<std::endl;
    b_end->next = NULL; //avoid delete twice
    */

 /*    auto list2 = List(4);
    list2.fill_randomly(10, 30);

    std::cout<<"2.4 before partition: "<<list2<<std::endl;

    partition(list2, 10);

    std::cout<<"2.4 after partition: "<<list2<<std::endl;
 */

    auto a = List(2);
    a.append(2);a.append(3);

    auto b = List(7);
    b.append(8);b.append(9);

    int c = sum_lists(a, b);

    std::cout<<"2.5: 223 + 789: "<<c<<" gt : "<<223+789<<std::endl;
}
