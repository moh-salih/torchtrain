# torchtrain

**torchtrain**  
Minimal C++ starter for training deep learning models with [LibTorch](https://pytorch.org/cppdocs/).  
Includes MLP, custom datasets, OpenCV, spdlog, and CMake setup.

## Features
- Modular C++ structure (models, datasets, utils)
- MLP model and custom `ImageDataset`
- Image preprocessing with OpenCV
- Logging with spdlog
- Easy CMake build system

## Build

```bash
mkdir build && cd build
cmake ..
cmake --build .```
