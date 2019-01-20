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