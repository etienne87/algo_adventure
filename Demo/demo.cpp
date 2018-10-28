
#include <ctime> 
#include <iostream>
#include <vector>
#include <time.h>
#include "sort.h"


void sort(std::vector<int>& vec, std::string& method, int k){
  if(method=="quicksort"){
    std::cout<<"qsort"<<std::endl;
    quicksort<int>(&vec[0], 0, vec.size()-1);
  }else if(method=="mergesort"){
    std::cout<<"mergesort"<<std::endl;
    std::vector<int> tmp(vec.size(), -1);
    mergesort<int>(&vec[0], &tmp[0], 0, vec.size());
  }else if(method=="countsort"){
    std::cout<<"countsort"<<std::endl;
    std::vector<int> tmp(vec.size(), -1);
    std::vector<int> count(k, 0);
    countsort<int>(&vec[0], &tmp[0], &count[0], k, vec.size());
  }else if(method=="radixsort"){
    std::cout<<"radixsort"<<std::endl;
    radixsort(&vec[0], vec.size());
  }else if(method=="bubblesort"){
    std::cout<<"bubblesort"<<std::endl;
    bubblesort<int>(&vec[0], vec.size());
  }
}

int main(int argc, char* argv[]){
  srand(0);
  std::cout<<"Sort Demo"<<std::endl;

  int k = 100;
  int array_size = 10;
  std::string method = "radixsort";
  if(argc > 1)
    array_size = atoi(argv[1]);
  if(argc > 2)
    k = atoi(argv[2]);
  if(argc > 3)
    method = argv[3];

  // initialize array
  std::vector<int> vec(array_size);         
  fill_rand_vec<int>(&vec[0], vec.size(), k);
  std::vector<int> cpy(array_size);
  std::memcpy(&cpy[0], &vec[0], vec.size()*4);
  
  clock_t t = clock();
  sort(vec, method, k);
  t = clock() - t;
  float m_items = (float)array_size/1000000.0;
  float runtime = ((float)t)/CLOCKS_PER_SEC;
  float mevs = m_items/runtime; 

  if( !is_sorted<int>(&vec[0], vec.size())){
    std::cout<<"FAIL"<<std::endl;

    int show_size = std::min((int)vec.size(), 100);
    std::string msg1("unordered");
    std::string msg2("ordered");
    print_vec_wrapp<int>(msg1, &cpy[0], show_size);
    print_vec_wrapp<int>(msg2, &vec[0], show_size);

  }else{
    std::cout<<"SUCCESS - Mev/s: "<<mevs<<" runtime: "<<runtime<<" for "<<m_items<<" Melems"<<std::endl;
  }    
}
