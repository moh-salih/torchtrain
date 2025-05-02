#include <iostream>

#include <torch/torch.h>
#include <spdlog/spdlog.h>

#include "utils/io_utils.h"
#include "utils/logger.h"
#include "datasets/ImageDataset.h"
#include  "preprocessing/image_preprocessing.h"
#include "postprocessing/image_postprocessing.h"
#include "models/MLP.h"

const std::string datasetPath = (io_utils::datasetsPath() / "fake_faces").string();

const size_t BATCH_SIZE = 10;

int main() {
    logger::init();

    try{
        spdlog::info("Inistanciating dataset");

        auto dataset = datasets::ImageDataset(datasetPath).map(torch::data::transforms::Stack<>());

        spdlog::info("Initializing Data Loader");
        auto dataloader = torch::data::make_data_loader(std::move(dataset), torch::data::DataLoaderOptions().batch_size(BATCH_SIZE));

        spdlog::info("Iterating Over Dataset");
        for(auto& batch: *dataloader){
            
        }

    }catch(const std::exception& e){
        spdlog::error(e.what());
    }catch(...){
        spdlog::error("Unknow exception");
    }


    return 0;
}
