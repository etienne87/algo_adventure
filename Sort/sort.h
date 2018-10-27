#include <iostream>
#include <cstdlib> 

template<class T>
void fill_rand_vec(T* array, int size, T maximum=100){
  for(int i=0;i<size;++i){
    array[i] = rand()%maximum;
  }
}

template<class T>
void print_vec(T* array, int size){
  std::cout<<"[";
  for(int i=0;i<size-1;++i){
    std::cout<<array[i]<<",";
  }
  std::cout<<array[size-1]<<"] ";
}

template<class T>
bool is_sorted(T* array, int size){
    for(int i=0;i<size-2;++i){
        if(array[i] > array[i+1])
            return false;
    }
    return true;
}

template<class T>
void swap(T* array, int i, int j){
    int tmp = array[j];
    array[j] = array[i];
    array[i] = tmp;
}

template<class T>
int partition(T* array, int left, int right){
    int pivot = array[(left+right)/2];
    while(left <= right){
        while(array[left] < pivot) left++;
        while(array[right] > pivot) right--;
        if(left <= right){
            swap<T>(array, left, right);
            left++;
            right--;
        }      
    }
    return left;
}

template<class T>
void quicksort(T* array, int left, int right){
    int index = partition<T>(array, left, right);
    if(left < index-1)
        quicksort<T>(array, left, index-1);
    if(index < right)
        quicksort<T>(array, index, right);
}

template<class T>
void mergesort(T* array, T* helper, int left, int right){
    if(left < right){
        int middle = (left+right)/2
        mergesort(array, helper, left, middle);
        mergesort(array, helper, middle+1, right);
        merge(array, helper, left, middle, right);
    }
}

