//
// Created by wangxc on 18-11-15.
//

#ifndef APT_MODEL_H
#define APT_MODEL_H

#include <opencv2/opencv.hpp>
#include <vector>
#include "Matrix.h"

class model {
public:
    model(cv::Mat input);
    model(int theta, int phi, cv::Mat input);
    float autoregression(const int row, const int col);
    cv::Mat get_error_map();
    std::vector<float> get_s(){return s;}
	cv::Mat get_input() { return input; }
private:
    cv::Mat input;
    int theta, phi;
    std::vector<float> s;

    std::vector<std::vector<float> > init_X(const int row, const int col, int range);
    std::vector<float> init_single_x(const int row, const int col, int range);
};


#endif //APT_MODEL_H
