#ifndef DATASETS_IMAGE__DATASET_H
#define DATASETS_IMAGE__DATASET_H
#include <torch/torch.h>

namespace datasets{
    
    class ImageDataset: public torch::data::Dataset<ImageDataset>{
    public:
        ImageDataset(const std::string& dataset_dir);
        
        torch::data::Example<> get(size_t idx) override;
        torch::optional<size_t> size() const override;
    
        private:
        std::vector<std::string> m_paths;
    };
}

#endif // DATASETS_IMAGE__DATASET_H