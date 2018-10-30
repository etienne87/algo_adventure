#include <ctime> 
#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>
#include "sort.h"
#include "sort_exos.h"

int main(int argc, char* argv[]){
    srand(0);
    std::cout<<"Sort Exo Demo"<<std::endl;

    int alen = 10;
    int blen = 10;
    int total = alen+blen;
    // Exo.1
    std::vector<int> A(total, 0);         
    fill_rand_vec<int>(&A[0], alen, 100);
    std::vector<int> B(blen);
    fill_rand_vec<int>(&B[0], blen, 100);

    quicksort<int>(&A[0], 0, alen-1);
    quicksort<int>(&B[0], 0, blen-1);

    std::string msg1("A:");
    std::string msg2("B:");
    print_vec_wrapp<int>(msg1, &A[0], alen);
    print_vec_wrapp<int>(msg2, &B[0], blen);

    sorted_merge<int>(&A[0], &B[0], alen, blen, total);

    std::string msg3("A+B:");
    print_vec_wrapp<int>(msg3, &A[0], total);
   /*  if( !std::is_sorted(vec.begin(), vec.end())) {
        std::cout<<"FAIL"<<std::endl;

        int show_size = std::min((int)vec.size(), 100);
        std::string msg1("unordered");
        std::string msg2("ordered");
        print_vec_wrapp<int>(msg1, &cpy[0], show_size);
        print_vec_wrapp<int>(msg2, &vec[0], show_size);

    }else{
        std::cout<<"SUCCESS - Mev/s: "<<mevs<<" runtime: "<<runtime<<" for "<<m_items<<" Melems"<<std::endl;
    }     */
}
