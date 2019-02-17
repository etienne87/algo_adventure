#include <ctime> 
#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>
#include "recursion.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using std::get;
typedef unsigned char uint8;

cv::Mat paint_fill_show_screen(vector<vector<int>>& groups, 
                            unordered_map<int,int>& map, 
                            vector<color>& colormaps){
    int height = groups.size();
    int width = groups[0].size();
    cv::Mat image(height, width, CV_8UC3);
    for(int y=0;y<height;y++){
        uint8* ptr = image.ptr<uint8>(y);
        for(int x=0;x<width;x++){
            int src = get_group(map, groups[y][x]);
            auto rgb = colormaps[src];
            *(ptr++) = get<0>(rgb);
            *(ptr++) = get<1>(rgb);
            *(ptr++) = get<2>(rgb);
        }
    }
    return image;
}

int main(int argc, char* argv[]){
    srand(0);
    std::cout<<"Recursion Demo"<<std::endl;
    int exo = 0;
    if(argc > 1)
        exo = atoi(argv[1]);

    if(exo == 0){
        std::cout<<"Climb Stairs"<<std::endl;
        vector<int> ways{ 1, 2, 3 }; 
        int n = climb_stairs(10, ways);
        std::cout<<n<<" ways to climb 100 stairs"<<std::endl;
    }
    if(exo == 1){
        std::cout<<"Robot Grid Path Planning"<<std::endl;
        int n = 6;
        vector<vector<bool>> grid(n);
        grid[0] = vector<bool>({0, 0, 1, 0, 0, 0});
        grid[1] = vector<bool>({1, 0, 0, 1, 0, 0});
        grid[2] = vector<bool>({0, 1, 0, 1, 0, 0});
        grid[3] = vector<bool>({0, 1, 0, 1, 0, 0});
        grid[4] = vector<bool>({0, 1, 0, 1, 1, 1});
        grid[5] = vector<bool>({0, 1, 0, 0, 0, 0});

        auto path = robot_grid(grid);
        for(auto it: path){
            for(auto jt: it)
                std::cout<<jt<<" ";
            std::cout<<std::endl;
        }
    }
    if(exo == 2){
        std::cout<<"Magic Index"<<std::endl;
        vector<int> array(100);
        array[0] = 1;
        for(int i=1;i<100;i++){
            if(i > array[i-1] && array[i-1] != i-1)
                array[i] = i;
            else
                array[i] = array[i-1] + rand()%2 + 1; // assures distinct numbers
        }

        for(auto it: array)
            std::cout<<it<<" ";
        std::cout<<std::endl;

        int i = magic_index(array);
        std::cout<<"magic index: "<<i<<" "<<array[i]<<std::endl;
    }
    if(exo == 3){
        std::cout<<"The Power Set"<<std::endl;
        vector<int> array(5);
        for(int i=0;i<array.size();i++){
            array[i] = i;
        }
        auto subsets = power_set(array);
        int gtsize = 1<<5;
        std::cout<<"num subsets: "<<subsets.size()<< " "<<gtsize<<std::endl;
        for(auto subset: subsets){
            for(auto item: subset){
                std::cout<<item<<" ";
            }
            std::cout<<std::endl;
        }
    }
    if(exo == 4){
        std::cout<<"Hanoi Tower"<<std::endl;
        stack<int> s1, s2, s3;
        int n = 20;
        for(int i=0;i<n;i++)
            s1.push(i);
        move_n_items(s1, s3, s2, n);
        for(int i=0;i<n;i++){
            std::cout<<pop(s3)<<std::endl;
        }
    }
    if(exo == 5){
        std::cout<<"Permute_with_or_without_dups"<<std::endl;
        string chars = "abbd";
        permute_dups(chars, true);
    }
    if(exo == 7){
        std::cout<<"Parens"<<std::endl;
        parens(3);
    }
    if(exo == 8){
        //initialize a small image with random numbers 1-10
        std::cout<<"Paint Fill"<<std::endl;
        vector<vector<int>> groups;
        unordered_map<int,int> map;
        vector<color> colormaps;
        for(int i=0;i<10;i++){
            int r = rand()%255;
            int g = rand()%255;
            int b = rand()%255;
            colormaps.push_back(color(r,g,b));
        }
        int height = 256;
        int width = 256;
        groups.resize(height);
        for(int y=0;y<height;y++){
            groups[y].resize(width);
            for(int x=0;x<width;x++){
                groups[y][x] = rand()%10;
            }
        }
        cv::Mat image = paint_fill_show_screen(groups, map, colormaps);
        cv::imshow("image", image);
        cv::waitKey();
    }
    if(exo == 9){
        std::cout<<"Coins"<<std::endl;    
        vector<int> ways = {25, 10, 5, 1};
        int ncents = 6;
        int64_t n = makechange(ncents, ways, 0);
        std::cout<<n<<" ways to give "<<ncents<<" cents"<<std::endl;
    }
    if(exo == 10){
        std::cout<<"NQueens"<<std::endl;
        int N = 4;
        vector<int> buffer;
        nqueens(N, buffer);
    }
    if(exo == 11){
        std::cout<<"Stack of Boxes"<<std::endl;
        vector<dims> whd;
        srand(0);
        for(int i=0;i<50;i++){
            int w = rand()%(i+1);
            int h = rand()%(i+1);
            int d = rand()%(i+1);
            whd.push_back(make_tuple(w,h,d));
            std::cout<<"#"<<i<<" "<<w<<";"<<h<<";"<<d<<std::endl;
        }
        vector<vector<int>> memo;
        int maximum_height = stack_of_boxes(whd, memo);
        std::cout<<"maximum height found: "<<maximum_height<<std::endl;
    }
    if(exo == 12){
        std::cout<<"Boolean Expression"<<std::endl;
        string expr1 = "1^0|0|1";
        string expr2 = "0&0&0&1^1|0";
        unordered_map<string, int> hash;
        //int a = count_eval(expr1, false, hash);
        //hash.clear();
        int b = count_eval(expr2, true, hash);
        //std::cout<<"expr1: "<<expr1<<": " <<a<<" ways"<<std::endl;
        std::cout<<"expr2: "<<expr2<<": " <<b<<" ways"<<std::endl;
    }
}
