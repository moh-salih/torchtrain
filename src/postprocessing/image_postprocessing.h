#ifndef POSTPROCESSING_IMAGE__POSTPROCESSING_H
#define POSTPROCESSING_IMAGE__POSTPROCESSING_H

#include <torch/torch.h>
#include <opencv2/opencv.hpp>

namespace postprocessing {

    // Convert tensor back to OpenCV Mat
    cv::Mat tensorToMat(const torch::Tensor& tensor);
    
    // Denormalize (scale back to [0,255])
    cv::Mat denormalize(const cv::Mat& image, float scale=255.0f);
    
    // Convert RGB → BGR
    cv::Mat toBGR(const cv::Mat& image);
    
    // Resize to original dimensions (if needed)
    cv::Mat resize(const cv::Mat& image, const cv::Size& size);
    
    // Full pipeline to convert tensor → displayable image
    cv::Mat pipeline(const torch::Tensor& tensor, const cv::Size& original_size, bool convert_to_bgr = true);

} // namespace postprocessing

#endif // POSTPROCESSING_IMAGE__POSTPROCESSING_H