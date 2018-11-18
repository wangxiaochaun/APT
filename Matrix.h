//
// Created by wangxc on 18-11-15.
//

#ifndef EXERCISE_MATRIX_H
#define EXERCISE_MATRIX_H

#include <vector>
#include <opencv2/opencv.hpp>

class Matrix {
public:
    cv::Mat vector2Mat(std::vector<std::vector<float> > src, int type);
};


#endif //EXERCISE_MATRIX_H
