// `pkg-config --cflags --libs opencv`

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <opencv2/highgui.hpp>

const std::size_t INIT_BUFFER_SIZE = 50000;

int main(){
    int bufferLength = 0;
    std::cin >> bufferLength;
    std::cout << bufferLength << std::endl;
    char *buffer = new char[bufferLength+1];
    size_t bytes_read = 0;

    freopen(0, “rb”, stdin);
    bytes_read = read(0, buffer, bufferLength+1)
    std::cout << int(bytes_read) << std::endl;

    cv::Mat matImg;
    matImg = cv::imdecode(cv::Mat(1, bytes_read, CV_8UC1, buffer), CV_LOAD_IMAGE_UNCHANGED);
    // use input vector here
    cv::imwrite("output.jpg", matImg);

    return 0;
}