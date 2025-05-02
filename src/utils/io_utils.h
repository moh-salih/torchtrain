#ifndef UTILS_IO__UTILS_H
#define UTILS_IO__UTILS_H
#include <vector>
#include <string>
#include <filesystem>


namespace io_utils{
    enum class ImageExtension{PNG, JPEG, JPG};
    
    ImageExtension toImageExtension(const std::string& extensionString);

    void validateDatasetDirectory(const std::string& path);

    std::vector<std::string> preparePaths(const std::string& datasetDir, ImageExtension extension = ImageExtension::PNG);

    std::vector<std::string> preparePathsRecursive(const std::string& datasetDir, ImageExtension extension = ImageExtension::PNG);

    std::filesystem::path rootPath();
    std::filesystem::path dataPath();
    std::filesystem::path datasetsPath();

    
    std::string getCurrentDateString();
    std::string getCurrentDateTimeString();
}
#endif // UTILS_IO__UTILS_H