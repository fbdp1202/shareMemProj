#include <opencv2/highgui.hpp>
#include <iostream>
using namespace cv;

int main( int argc, char** argv ) {
  
  Mat image;
  image = imread("image.jpg");
  
  if(! image.data ) {
      std::cout <<  "Could not open or find the image" << std::endl ;
      return -1;
    }
  
  imwrite("output.jpg",image);
  return 0;
}