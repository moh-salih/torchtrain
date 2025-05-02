#include <spdlog/spdlog.h>

#include "preprocessing/image_preprocessing.h"

namespace fs = std::filesystem;

namespace preprocessing{
    
    void validateImagePath(const std::string& path){
        if(!fs::exists(path) || !fs::is_regular_file(path)) throw std::runtime_error("Invalid image path: " + path);
    }
    
    cv::Mat loadImage(const std::string& path, int flags){
        cv::Mat image = cv::imread(path, flags);
        if (image.empty()) throw std::runtime_error("Failed to load image: " + path);
        return image;
    }
    
    cv::Mat resize(const cv::Mat& image, const cv::Size& size){
        cv::Mat resized;
        cv::resize(image, resized, size);
        return resized;
    }
    
    
    cv::Mat toRGB(const cv::Mat& image){
        cv::Mat rgb;
        cv::cvtColor(image, rgb, cv::COLOR_BGR2RGB);
        return rgb;
    }
    
    
    cv::Mat toBGR(const cv::Mat& image){
        cv::Mat bgr;
        cv::cvtColor(image, bgr, cv::COLOR_RGB2BGR);
        return bgr;
    }
    
    
    cv::Mat normalize(const cv::Mat& image, float scale){
        cv::Mat normalized;
        image.convertTo(normalized, CV_32F, scale);
        return normalized;
    }
    
    
    torch::Tensor toTensor(const cv::Mat& image, int channels){
        torch::Tensor tensor = torch::from_blob(image.data, {image.rows, image.cols, channels}, torch::kFloat32);
        tensor = tensor.permute({2, 0, 1});
        return tensor.clone();
    }


    torch::data::Example<> pipeline(const std::string& path){
        // 1. Validate and load image
        preprocessing::validateImagePath(path);
        cv::Mat image = loadImage(path); // default is IMREAD_COLOR_BGR
        
        // 2. Convert BGR → RGB
        image = preprocessing::toRGB(image);
        
        // 3. Resize to fixed size (e.g., 224x224)
        image = preprocessing::resize(image, cv::Size(224, 224));
        
        // 4. Normalize (scale to [0,1])
        image = preprocessing::normalize(image); // default scale = 1/255
        
        // 5. Convert to torch::Tensor
        torch::Tensor imageTensor = preprocessing::toTensor(image);
        
        // 6. Create dummy label (until label logic is added)
        torch::Tensor labelTensor = torch::tensor(0, torch::kInt64);
        
        return {imageTensor, labelTensor};
    }
}