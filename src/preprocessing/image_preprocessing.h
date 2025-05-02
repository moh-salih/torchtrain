#ifndef PREPROCESSING_IMAGE__PREPROCESSING_H
#define PREPROCESSING_IMAGE__PREPROCESSING_H

#include <filesystem>

#include <torch/torch.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>


namespace preprocessing{
    
    void validateImagePath(const std::string& path);

    cv::Mat loadImage(const std::string& path, int flags=cv::IMREAD_COLOR);

    cv::Mat resize(const cv::Mat& image, const cv::Size& size);

    cv::Mat toRGB(const cv::Mat& image);

    cv::Mat toBGR(const cv::Mat& image);

    cv::Mat normalize(const cv::Mat& image, float scale=1.0/255.0);

    torch::Tensor toTensor(const cv::Mat& image, int channels=3);

    torch::data::Example<> pipeline(const std::string& path);
}


#endif // PREPROCESSING_IMAGE__PREPROCESSING_H