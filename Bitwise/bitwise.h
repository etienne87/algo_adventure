#include <iostream>
#include <cstdlib> 
#include <cstring>
#include <unordered_set>
#include <unordered_map>
#include <list>
#include <vector>
#include <deque>
#include <string>
#include <cmath>

using std::vector;


int insert(int N, int M, int i, int j){
    int d = j-i;
    int o = (~0 >> (32-j)) << i; // create 1 by moving by 32 
    return (N & ~o) | (M << i);
}

void print_binary(int N, int nbits=32){
    int k = N;
    for(int i=0;i<nbits;i++){
        int bit = k & (1<<(nbits - 1 - i));
        std::cout<<(bit>0);
    }
    std::cout<<std::endl;
}

int flip_to_win(int N){
    vector<int> seq;
    int c=0;
    for(int i=0;i<32;i++){
        int bit = (N & (1<<i))>0;
        if(bit){
            c++;
        }else if(c > 0){
            seq.push_back(c);
            c = 0;
        }
    }
    int max = 0;
    for(int i=0;i<seq.size()-1;i++){
        int c = seq[i] + seq[i+1] + 1;
        if( c > max )
            max = c;
    }
    return max;
}

int count_set_bits(int N){
    int c=0;
    for(int i=0;i<32;i++)
        c += N & (1>>i);
    return c;
}

int count_toflip_bits(int N){
    int c=0;
    for(int i=0;i<32;i++)
        c += (N ^ (1<<i))==0;
    return c;
}

int pairwise_swap(int N){
    int mask_even = 0b10101010101010101010101010101010;
    int mask_odd = mask_even>>1;
    int odd_part = ((N & mask_odd)<<1)&mask_even;
    int odd_even = ((N & mask_even)>>1)&mask_odd;
    return odd_part | odd_even;
}