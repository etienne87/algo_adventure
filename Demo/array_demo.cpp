#include <ctime> 
#include <iostream>
#include <vector>
#include <time.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
//#include "arrays.h"



int main(int argc, char* argv[]){
    srand(0);
    std::cout<<"Sort Demo"<<std::endl;

    std::string filename = "/home/eperot/Pictures/lena.png";
    if(argc > 1)
        filename = argv[1];

    cv::Mat image;
    image = cv::imread(filename, CV_LOAD_IMAGE_COLOR);   // Read the file

    cv::namedWindow("Display", cv::WINDOW_AUTOSIZE);
    cv::imshow("Display", image);
    cv::waitKey();
}