#include <ctime> 
#include <iostream>
#include <vector>
#include <time.h>
#include "lists.h"


int main(int argc, char* argv[]){
    srand(0);
    std::cout<<"Lists Demo"<<std::endl;
    int exo = 0;

    if(argc > 1)
        exo = atoi(argv[1]);

    auto list = List(4);    
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

    //list.delete_nodes(4);

    if(exo == 1){
        remove_duplicates(list); 
        std::cout<<"2.1 duplicate removal: "<<list<<std::endl;
    }else if(exo == 2){
        int klast = kth_last(list, 3);
        std::cout<<"2.2 kth last: "<<klast<<std::endl;
    }else if(exo == 3){
        Node* node = list.get_head();
        node = node->next->next;

        delete_middle_node(node);
        std::cout<<"2.3 middle node removal: "<<list<<std::endl;
    }else if(exo == 7){
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

        b_end->next = NULL; //avoid delete twice
    }else if(exo == 4){
        auto list2 = List(4);
        list2.fill_randomly(10, 30);

        std::cout<<"2.4 before partition: "<<list2<<std::endl;

        partition(list2, 10);

        std::cout<<"2.4 after partition: "<<list2<<std::endl;
    }else if(exo == 5){
        auto a = List(2);
        a.append(2);a.append(3);

        auto b = List(7);
        b.append(8);b.append(9);

        int c = sum_lists(a, b);

        std::cout<<"2.5: 223 + 789: "<<c<<" gt : "<<223+789<<std::endl;
    }else if(exo == 6){
        auto pal = List(4);
        pal.append(3);
        pal.append(2);
        pal.append(3);
        pal.append(4);

        bool tmp = is_palindrome(pal);
        std::cout<<"should be palindrome: "<<tmp<<std::endl;

        /* auto pal2 = List(4);
        pal2.append(7);
        pal2.append(9);
        tmp = is_palindrome(pal2);
        std::cout<<"should not be palindrome: "<<tmp<<std::endl; */
    }



    std::cout<<"fin"<<std::endl;
}
