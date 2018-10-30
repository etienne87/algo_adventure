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

int main(int argc, char* argv[]){
    srand(0);
    std::cout<<"Arrays Demo"<<std::endl;

    std::string filename = "/home/eperot/Pictures/bowsette.jpg";
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
        exit(0); 
}