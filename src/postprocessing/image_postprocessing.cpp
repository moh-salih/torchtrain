#include "postprocessing/image_postprocessing.h"

namespace postprocessing {
    cv::Mat tensorToMat(const torch::Tensor& tensor) {
        torch::Tensor local = tensor.squeeze().detach().cpu();
        if (local.dim() != 3) {
            throw std::runtime_error("Expected 3D tensor [C,H,W]");
        }
    
        local = local.permute({1, 2, 0}).contiguous();  // [H, W, C]
    
        int height = local.size(0);
        int width = local.size(1);
        int channels = local.size(2);
    
        return cv::Mat(height, width, CV_32FC(channels), local.data_ptr()).clone(); 
    }
        
    cv::Mat denormalize(const cv::Mat& image, float scale) {
        cv::Mat denormalized;
        image.convertTo(denormalized, CV_8U, scale);
        return denormalized;
    }

    cv::Mat toBGR(const cv::Mat& image) {
        cv::Mat bgr;
        cv::cvtColor(image, bgr, cv::COLOR_RGB2BGR);
        return bgr;
    }

    cv::Mat resize(const cv::Mat& image, const cv::Size& size) {
        cv::Mat resized;
        cv::resize(image, resized, size);
        return resized;
    }

    cv::Mat pipeline(const torch::Tensor& tensor, const cv::Size& original_size, bool convert_to_bgr) {
        // 1. Convert tensor to Mat
        cv::Mat image = tensorToMat(tensor);
        
        // 2. Denormalize (scale back to 0-255)
        image = denormalize(image);
        
        // 3. Convert RGB → BGR if needed
        if (convert_to_bgr) {
            image = toBGR(image);
        }
        
        // 4. Resize to original dimensions
        if (original_size != cv::Size()) {
            image = resize(image, original_size);
        }
        
        return image;
    }

} // namespace postprocessing