#include <iostream>
#include <unordered_map>
#include <utility>

using std::unordered_map;
using std::pair;

template<class T>
void fill_vector(T* array, int size, T high=100){
    for(int i=0;i<size;++i){
        array[i] = rand()%high;
    }
}

template<class T>
void unique_cpu(T* src, T* inv, int& num_uniques, int size, bool sorted=false){
    num_uniques = 0;
    if(sorted){
        inv[0] = 0;
        for(int i=1;i<size-1;i++){
            if(src[i-1] != src[i]){
                num_uniques++;
            }
            inv[i] = num_uniques;
        }
    }else{
        unordered_map<T,int> mmap;
        for(int i=0;i<size;i++){
            T val = src[i];
            auto it = mmap.find(val);
            int uniq_index = 0;
            if( it == mmap.end()){
                mmap.insert(pair<T,int>(val,num_uniques));
                uniq_index = num_uniques;
                num_uniques++;
            }else{
                uniq_index = it->second;
            }
            inv[i] = uniq_index;
        }
    }
}
