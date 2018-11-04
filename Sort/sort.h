#include <iostream>
#include <cstdlib> 
#include <cstring>
#include <functional>

template<class T>
void fill_rand_vec(T* array, int size, T maximum=100){
    for(int i=0;i<size;++i){
        array[i] = rand()%maximum;
    }
}

template<class T>
void print_vec(T* array, int size){
    std::cout<<"[";
    for(int i=0;i<size;++i){
        std::cout<<array[i];
        if(i < size-1)
            std::cout<<",";
    }
    std::cout<<"] ";
}

template<class T>
void print_vec_wrapp(std::string& msg, T* array, int size){
    std::cout<<msg<<" ";
    print_vec(array, size);
    std::cout<<std::endl;
}

template<class T>
bool is_sorted(T* array, int size){
    for(int i=0;i<size-1;++i){
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
void merge(T* array, T* helper, int left, int middle, int right){
    for(int i=left;i<right;i++)
        helper[i] = array[i]; 

    int index = left;
    int l = left;
    int r = middle;
    while(l < middle && r < right){
        if(helper[l] <= helper[r]){
            array[index++] = helper[l];
            l++;
        }else{
            array[index++] = helper[r];
            r++;
        }
    }
    // copy remaining left, right is already correctly placed
    for(int i=l;i<middle;i++)
        array[index++] = helper[i];
} 

template<class T>
void mergesort(T* array, T* helper, int left, int right){
    if(left < right-1){
        int middle = (left + right)/2;
        mergesort(array, helper, left, middle);
        mergesort(array, helper, middle, right);
        merge(array, helper, left, middle, right); 
    }
}

template<class T>
int cast_int(T& element, int param=0){
    return (int)element;
}

template<class T>
void countsort(T* array, T* helper, int* count, int k, int size, int(*extract_key)(T& element, int param)=cast_int, int key_param=0){
    std::memset(count, 0, k*sizeof(int));
    std::memcpy(helper, array, size*sizeof(T));
    //histogram
    for(int i=0;i<size;i++){
        int key = extract_key(helper[i], key_param);
        count[key]++;
    }   
    //cumsum
    int total = 0;
    for(int i=0;i<k;i++){
        int old_count = count[i];
        count[i] = total;
        total += old_count;  
    }
    //reorder
    for(int i=0;i<size;i++){
        T x = helper[i];
        int key = extract_key(x, key_param);
        int* cx = &count[key];
        array[*cx] = x;
        (*cx)++;
    } 
}


template<class T>
int get_byte(T& element, int num_byte){
    int out = (unsigned char)(element>>(num_byte*8));
    return out;
}

void radixsort(int* array, int size){
    int* helper = new int[size];
    int count[256]; 
    for(int i=0;i<4;i++){
        countsort<int>(array, helper, count, 256, size, get_byte, i);
    }
}


template<class T>
int binary_search(T* array, int size, int d){
    int low = 0;
    int high = size;
    T mid = 0;
    int middle = 0;
    while(low < high){
        middle = (low+high)/2;
        mid = array[middle];
        if(mid == d){
            return middle;
        }else if(mid > d){
            high = middle - 1;
        }else if(mid < d){
            low = middle + 1;
        }
    }
    return -1;
}