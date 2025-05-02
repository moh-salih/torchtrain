#include "models/MLP.h"

/*

Digit classification (0–9) using MNIST-like data (28×28 grayscale images)

Input size: 28 x 28 = 784

Output classes: 10

Type: Multiclass classification

| Component        | Value                        |
|------------------|------------------------------|
| Input            | 784-dim vector               |
| Hidden layers    | 256 → 128                    |
| Output           | 10 (one per class)           |
| Activation       | ReLU                         |
| Loss             | `torch::nn::CrossEntropyLoss`|
| Optimizer        | Adam / SGD                   |
| Epochs           | 5–20                         |
| Accuracy         | ~97% on MNIST (if trained well) |

*/

namespace models{
    
    MLP::MLP() {
        fc1 = register_module("fc1", torch::nn::Linear(784, 256)); // Input → Hidden
        fc2 = register_module("fc2", torch::nn::Linear(256, 128)); // Hidden → Hidden
        fc3 = register_module("fc3", torch::nn::Linear(128, 10));  // Hidden → Output
    }

    torch::Tensor MLP::forward(torch::Tensor x) {
        x = x.view({x.size(0), 784}); // Flatten [B, 1, 28, 28] → [B, 784]
        x = torch::relu(fc1->forward(x));
        x = torch::relu(fc2->forward(x));
        x = fc3->forward(x);
        return x; // no softmax here → use CrossEntropyLoss
    }
}
