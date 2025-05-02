#ifndef MODELS_MLP_H
#define MODELS_MLP_H

#include <torch/torch.h>


namespace models{
    struct MLP : torch::nn::Module {
        MLP();
    
        torch::Tensor forward(torch::Tensor x);
    
    private:
        torch::nn::Linear fc1{nullptr}, fc2{nullptr}, fc3{nullptr};
    };    
}
#endif // MODELS_MLP_H
