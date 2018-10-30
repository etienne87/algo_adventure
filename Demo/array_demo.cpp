#include <ctime> 
#include <iostream>
#include <vector>
#include <time.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
//#include "arrays.h"

typedef unsigned char uint8;

//todo: put this into arrays.h
void rot90_inplace(cv::Mat& image){
    int N = image.cols;
    for(int y=0;y<N/2;y++){
        for(int x=0;x<N/2;x++){
            //circular shift 4 times:
            int y2 = N-1-y;
            int x2 = N-1-x;
            
            uint8 tmp = image.at<uint8>(y, x);

            image.at<uint8>(y,x) = image.at<uint8>(x,y2); // y2,x -> x,y
            image.at<uint8>(x,y2) = image.at<uint8>(y2,x2); // x2,y2 -> y2,x
            image.at<uint8>(y2,x2) = image.at<uint8>(x2,y); // y,x2 -> x2, y2
            image.at<uint8>(x2, y) = tmp; //x,y -> y, x2
        }
    }
}

//mohammed sayz: this code is fucky
bool one_edit_away(std::string& a, std::string& b){
    int diffsize = a.size() - b.size();
    if(diffsize == 0){
        int edits = 0;
        for(int i=0;i<a.size();i++){
            if(a[i] != b[i])
                edits++;
            if(edits > 1)
                return false;
        }
        return true;
    }
    else{
        int edits = 0;
        std::string bigger, smaller;
        if(diffsize > 0){
            bigger = a;
            smaller = b;
        }else{
            bigger = b;
            smaller = a;
        }
        int nedits = 0;
        int bigger_idx = 0;
        for(int smaller_idx=0;smaller_idx<smaller.size();smaller_idx++){
            if(bigger[bigger_idx] != smaller[smaller_idx]){
                if(bigger_idx == bigger.size())
                    return false;
                if(bigger[bigger_idx+1] == smaller[smaller_idx])
                    edits++;
            }
            if(edits > 1)
                return false;
        }
        return true;
    }
}

int main(int argc, char* argv[]){
    srand(0);
    std::cout<<"Arrays Demo"<<std::endl;

    /* std::string filename = "/home/eperot/Pictures/bowsette.jpg";
    if(argc > 1)
        filename = argv[1];

    cv::Mat image, gray, small;
    image = cv::imread(filename, CV_LOAD_IMAGE_COLOR);   // Read the file
    cv::cvtColor(image, gray, CV_BGR2GRAY);
    cv::resize(gray, small, cv::Size(256,256), 0.0, 0.0, cv::INTER_AREA);
    
    cv::Mat cpy = small.clone();
    rot90_inplace(cpy);

    cv::namedWindow("Display", cv::WINDOW_AUTOSIZE);
    cv::imshow("Display", small);
    cv::imshow("Rot90", cpy);
    int key = cv::waitKey();
    if(key == 27)
        exit(0);  */

    std::string a("pale"); 
    std::string b("ple");
    std::cout<<a<<";"<<b<<" - one edit away? "<<one_edit_away(a, b)<<std::endl;

    a = "pales";
    b = "pale";
    std::cout<<a<<";"<<b<<" - one edit away? "<<one_edit_away(a, b)<<std::endl;

    a = "pale";
    b = "bale";
    std::cout<<a<<";"<<b<<" - one edit away? "<<one_edit_away(a, b)<<std::endl;

    a = "pale";
    b = "bake";
    std::cout<<a<<";"<<b<<" - one edit away? "<<one_edit_away(a, b)<<std::endl;
}