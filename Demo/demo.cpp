
#include <ctime> 
#include <iostream>
#include <vector>
#include <time.h>
#include "sort.h"



void print_vec(std::vector<int>& tmp){
  for(int i=0;i<tmp.size();++i){
    std::cout<<tmp[i]<<",";
  }
  std::cout<<std::endl;
}

int main(int argc, char* argv[]){
  srand(0);
  std::cout<<"Sort Demo"<<std::endl;


  /* interesting example
  std::vector<int> vec;
  vec.push_back(20);
  vec.push_back(23);
  vec.push_back(7);
  vec.push_back(37);
  vec.push_back(3);
  //quicksort<int>(&vec[0], 0, vec.size()-1);
 */
  


  int array_size = atoi(argv[1]);
  clock_t t;

  std::vector<char> vec(array_size);         
  fill_rand_vec<char>(&vec[0], vec.size(), 100);

  // std::cout<<"unordered: "<<std::endl;
  // print_vec(vec);
  t = clock();
  quicksort<char>(&vec[0], 0, vec.size()-1);
  t = clock() - t;
  float runtime = ((float)t)/CLOCKS_PER_SEC;
  float mevs = (float)array_size/runtime;

  if( !is_sorted<char>(&vec[0], vec.size())){
    std::cout<<"FAIL"<<std::endl;
    exit(0);
  }else{
    std::cout<<"SUCCESS - Mev/s: "<<mevs<<std::endl;
  } 


  // Comparison with std::sort!

  /* fill_rand_vec<int>(vec, vec.size(), 100);
  t = clock();
  quicksort(&vec[0], 0, vec.size()-1);
  t = clock() - t;
  runtime = ((float)t)/CLOCKS_PER_SEC;
  mevs = (float)array_size/runtime;

  std::cout<<"STD::SORT - Mev/s: "<<mevs<<std::endl; */


}
