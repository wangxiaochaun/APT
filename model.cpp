//
// Created by wangxc on 18-11-15.
//

#include "model.h"
#include "Matrix.h"
#include <fstream>

model::model(cv::Mat input)
{
    this->theta = 8;
    this->phi = 48;
    this->s = std::vector<float>(8);
	this->input = input;
}

model::model(int theta, int phi, cv::Mat input)
{
    this->theta = theta;
    this->phi = phi;
    this->s = std::vector<float>(8);
	this->input = input;
}

float model::autoregression(const int row, const int col)
{    
    int range = (sqrt(phi + 1) + 1) / 2 - 1;

    // 初始化向量x
    std::vector<float> x = init_single_x(row, col, range);
    cv::Mat x_mat = cv::Mat(x);
    // 打印x
    // std::cout << "x: " << std::endl;
    std::ofstream f;
    f.open("x.txt", std::ios::out);
    for (int i = 0; i < x_mat.rows; i++) {
        for (int j = 0; j < x_mat.cols; j++) {
            f << x_mat.at<float>(i, j) << "\t";
        }
        f << std::endl;
    }
    f.close();
    // 初始化矩阵X
    std::vector<std::vector<float> > X = init_X(row, col, range);
    Matrix matrix;
    cv::Mat X_mat = matrix.vector2Mat(X, CV_32F);
    // 打印X
    // std::cout << "X: " << std::endl;
    f.open("X.txt", std::ios::out);
    for (int i = 0; i < X_mat.rows; i++) {
        for (int j = 0; j < X_mat.cols; j++) {
            f << X_mat.at<float>(i, j) << "\t";
        }
        f << std::endl;
    }
    f.close();
    // 估计自回归系数s
    cv::Mat s_mat = (X_mat.t() * X_mat).inv() * X_mat.t() * x_mat;
    // 打印s
    f.open("s.txt", std::ios::out);
    for (int i = 0; i < s_mat.rows; i++)
    {
        for (int j = 0; j < s_mat.cols; j++)
        {
            f << s_mat.at<float>(i, j) << "\t";
        }
        f << std::endl;
    }
    // 计算d
    std::vector<float> Omega = init_single_x(row, col, 1); // 取8-邻域
    // 打印Omega
    f.open("Omega.txt", std::ios::out);
    for (auto item : Omega) {
        f << item << std::endl;
    }
    f.close();
    cv::Mat Omega_mat = cv::Mat(Omega);
    float d = input.at<float>(row, col) - Omega_mat.dot(s_mat);

    return d;
}

cv::Mat model::get_error_map()
{
	cv::Mat error_map = cv::Mat(input.rows - 8, input.cols - 8, CV_32F);
    cv::imshow("error_map", error_map);
    //std::cout << error_map.rows << "," << error_map.cols << std::endl;
    for (int i = 0; i < error_map.rows; i++)
    {
        for (int j = 0; j < error_map.cols; j++)
        {
            //std::cout << "Processing: (" << i << "," << j << ")" << std::endl;
            error_map.at<float>(i, j) = fabs(autoregression(i + 4, j + 4));
		}
    }

    //Post-processing
    // Firstly, "clean" the error map with a Gaussian filter for the purpose of
    // removing some isolated small "noise".
    //cv::GaussianBlur(error_map, error_map, cv::Size(3, 3), 0);
    // The "gamma%" most salient regions are detected to be used for excluding
    // The associated parts in the error map (FFS model)\


    return error_map;
}

std::vector<std::vector<float> > model::init_X(const int row, const int col, int range)
{
    int small_range = 1; //8-邻域
    //std::cout << "Range: " << range << std::endl;
    //std::cout << "init_X: (" << center.x << "," << center.y << ")" << std::endl;
    std::vector<std::vector<float> > X;
    for (int i = row - range; i <= row + range; i++)
    {
        for (int j = col - range; j <= col + range; j++)
        {
            if (!(i == row && j == col))
            {
                X.push_back(init_single_x(i, j, small_range));
            }
        }
    }
    return X;
}

std::vector<float> model::init_single_x(const int row, const int col, int range)
{
    //std::cout << "Range: " << range << std::endl;
    std::vector<float> x;
    for (int i = row - range; i <= row + range; i++)
    {
        for (int j = col - range; j <= col + range; j++)
        {
            if (!(i == row && j == col))
                x.push_back(input.at<float>(i, j));
        }
    }
    return x;
}