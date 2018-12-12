#include <ctime> 
#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>
#include <random>
#include "unique.h"
#include "sort.h"

using std::vector;

//write to a file results of one method
void benchmark(){

}

int main(int argc, char* argv[]){
    srand(0);
    std::cout<<"Unique Demo"<<std::endl;
    int size = 1e8;
    int high = 640*480;
    int rounds = 10;
    bool sorted = false;
    if(argc > 1)
        size = atoi(argv[1]);
    if(argc > 2)
        high = atoi(argv[2]);    
    if(argc > 3)
        rounds = atoi(argv[3]);    
    if(argc > 4)
        sorted = bool(atoi(argv[4]));

    vector<int> src(size);
    fill_vector<int>(&src[0], src.size(), high);
    vector<int> inv(size);
    std::random_device rd;
    std::mt19937 g(rd());
    unordered_map<int,int> mmap;
    mmap.reserve(size);

    int nuniq = 0;
    clock_t t = clock();
    for(int i=0;i<rounds;i++){ 
        if(sorted){
            clock_t t2 = clock();
            fill_vector<int>(&src[0], src.size(), high);
            t -= clock()-t2;
            //std::sort(src.begin(),src.end());  
            radixsort(&src[0], src.size());        
        }
        unique_cpu<int>(&src[0], &inv[0], mmap, nuniq, size, sorted);
    }
    t = clock() - t;
    float m_items = (float)size/1000000.0;
    float runtime = ((float)t)/CLOCKS_PER_SEC/rounds;
    float mevs = m_items/runtime;     
    std::cout<<"Mev/s: "<<mevs<<" runtime: "<<runtime<<" for "<<m_items<<" Melems"<<std::endl;
}
