#include <iostream>
#include <cstdlib> 
#include <cstring>

template<class T>
void sorted_merge(T* A, T* B, int alen, int blen, int total_alen){
    int l = alen-1;
    int r = blen-1;
    int idx = total_alen-1;
    while(l >= 0 && r >= 0){
        if(A[l] >= B[r]){
            A[idx--] = A[l];
            l--;
        }else{
            A[idx--] = B[r];
            r--;
        }
    }
}