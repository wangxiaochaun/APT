//
// Created by wangxc on 18-11-15.
//

#include "Matrix.h"

cv::Mat Matrix::vector2Mat(std::vector<std::vector<float> > src, int type)
{
    cv::Mat temp(src.size(), src.at(0).size(), type);
    //std::cout << temp.rows << "\t" << temp.cols << std::endl;
    for (int i = 0; i < temp.rows; i++)
    {
        for (int j = 0; j < temp.cols; j++)
        {
            //std::cout << src.at(i).at(j);
            temp.at<float>(i, j) = src.at(i).at(j);
        }
    }
    return temp;
}
