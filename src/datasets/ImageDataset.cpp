#include <string>

#include <spdlog/spdlog.h>

#include "datasets/ImageDataset.h"
#include "preprocessing/image_preprocessing.h"
#include "utils/io_utils.h"


namespace datasets{
    
    ImageDataset::ImageDataset(const std::string& dataset_dir){
        spdlog::info("Getting Dataset info from path: " + dataset_dir);

        io_utils::validateDatasetDirectory(dataset_dir);
        spdlog::info("Dataset path validated");
        m_paths = io_utils::preparePaths(dataset_dir, io_utils::ImageExtension::JPG);
        spdlog::info("Dataset initialized with " + std::to_string(m_paths.size()) + " item");
    }


    torch::data::Example<> ImageDataset::get(size_t idx){
        if(idx >= m_paths.size()){
            throw std::out_of_range("Index out of range, take a look at get(size_t idx) in ImageDataset.cpp");
        }

        return preprocessing::pipeline(m_paths[idx]);
    }

    torch::optional<size_t> ImageDataset::size() const {
        return m_paths.size();
    }
}