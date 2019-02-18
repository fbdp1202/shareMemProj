#include <opencv2/highgui.hpp>
#include <fstream>
#include <iostream>
using namespace std;

int main() {

    //Open image file to read from
    char imgPath[] = "./image.jpg";
    ifstream fileImg(imgPath, ios::binary);
    fileImg.seekg(0, std::ios::end);
    int bufferLength = fileImg.tellg();
    fileImg.seekg(0, std::ios::beg);

    if (fileImg.fail())
    {
        cout << "Failed to read image" << endl;
        cin.get();
        return -1;
    }

    //Read image data into char array
    char *buffer = new char[bufferLength];
    fileImg.read(buffer, bufferLength);

    //Decode data into Mat 
    cv::Mat matImg;
    matImg = cv::imdecode(cv::Mat(1, bufferLength, CV_8UC1, buffer), CV_LOAD_IMAGE_UNCHANGED);

    //Create Window and display it
    // cv::namedWindow("Image from Char Array", CV_WINDOW_AUTOSIZE);
    // if (!(matImg.empty()))
    // {
    //     cv::imshow("Image from Char Array", matImg);
    // }
    cv::imwrite("output.jpg", matImg);
    // cv::waitKey(0);

    delete[] buffer;

    return 0;
}