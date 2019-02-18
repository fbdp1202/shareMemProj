// `pkg-config --cflags --libs opencv`

#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <opencv2/highgui.hpp>

const std::size_t INIT_BUFFER_SIZE = 50000;

int main(){
    // ifstream fileImg(stdin, ios::binary);
    // fileImg.seekg(0, std::ios::end);
    // int bufferLength = fileImg.tellg();
    // fileImg.seekg(0, std::ios::beg);

    // if (fileImg.fail())
    // {
    //     cout << "Failed to read image" << endl;
    //     cin.get();
    //     return -1;
    // }
    //Read image data into char array

    int bufferLength = 0;
    std::cin >> bufferLength;
    std::cout << bufferLength << std::endl;
    char *buffer = new char[bufferLength];


    try
    {
        // on some systems you may need to reopen stdin in binary mode
        // this is supposed to be reasonably portable
        std::freopen(nullptr, "rb", stdin);

        if(std::ferror(stdin))
            throw std::runtime_error(std::strerror(errno));

        std::size_t len;
        std::array<char, INIT_BUFFER_SIZE> buf;

        // somewhere to store the data
        std::vector<char> input;

        // use std::fread and remember to only use as many bytes as are returned
        // according to len
        while((len = std::fread(buf.data(), sizeof(buf[0]), buf.size(), stdin)) > 0)
        {
            // whoopsie
            if(std::ferror(stdin) && !std::feof(stdin))
                throw std::runtime_error(std::strerror(errno));

            // use {buf.data(), buf.data() + len} here
            input.insert(input.end(), buf.data(), buf.data() + len); // append to vector
        }
	    cv::Mat matImg;
	    char *buffer = reinterpret_cast<char*>(input.data());
	    matImg = cv::imdecode(cv::Mat(1, len, CV_8UC1, buffer), CV_LOAD_IMAGE_UNCHANGED);
        // use input vector here
    	cv::imwrite("output.jpg", matImg);

    }
    catch(std::exception const& e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }
    // cin >> buffer;
    // cout << bufferLength << endl;

    //Decode data into Mat 

    //Create Window and display it
    // cv::namedWindow("Image from Char Array", CV_WINDOW_AUTOSIZE);
    // if (!(matImg.empty()))
    // {
    //     cv::imshow("Image from Char Array", matImg);
    // }
    // cv::waitKey(0);
}