#include <algorithm>
#include <cctype>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <ctime>

#include "utils/io_utils.h"


namespace fs = std::filesystem;

namespace io_utils{


    ImageExtension toImageExtension(const std::string& extensionString){
        if(extensionString.empty()){
            throw std::runtime_error("Invalid extension");
        }
        
        std::string extension = extensionString;
        if(extension[0] == '.'){
            extension.erase(0, 1);
        }

        std::transform(extension.cbegin(), extension.cend(), extension.begin(),[](unsigned int c){ return std::tolower(c); });

        if(extension == "png")
            return ImageExtension::PNG;
        else if(extension == "jpg")
            return ImageExtension::JPG;
        else if(extension == "jpeg")
            return ImageExtension::JPEG;
        else{
            throw std::runtime_error("An issue happend in extension matching, take a look at utils::toImageExtension()!");
        }      

        return ImageExtension::PNG; // This is never accessed, and was added just to scilense some compiler warnings
    }

    void validateDatasetDirectory(const std::string& path){
        if(!fs::exists(path)){
            throw std::runtime_error("Dataset path is not correct: " + path);
        }
    }

    static std::vector<std::string> scanDirectory(const std::string& dirPath, ImageExtension extension) {
        std::vector<std::string> paths;
        for (const auto& entry : fs::directory_iterator(dirPath)) {
            const auto& path = entry.path();
            if (fs::is_regular_file(path) && io_utils::toImageExtension(path.extension().string()) == extension) {
                paths.push_back(path.string());
            }
        }
        return paths;
    }

    static void scanDirectoryRecursive(const std::string& dirPath, ImageExtension extension, std::vector<std::string>& outputPaths) {
        for (const auto& entry : fs::directory_iterator(dirPath)) {
            const auto& path = entry.path();
            if (fs::is_directory(path)) {
                scanDirectoryRecursive(path.string(), extension, outputPaths);
            } 
            else if (fs::is_regular_file(path) && io_utils::toImageExtension(path.extension().string()) == extension) {
                outputPaths.push_back(path.string());
            }
        }
    }

    std::vector<std::string> preparePaths(const std::string& datasetDir, ImageExtension extension) {
        if (!fs::exists(datasetDir)) {
            throw std::runtime_error("Directory does not exist: " + datasetDir);
        }
        return scanDirectory(datasetDir, extension);
    }

    std::vector<std::string> preparePathsRecursive(const std::string& datasetDir, ImageExtension extension) {
        std::vector<std::string> paths;
        if (!fs::exists(datasetDir)) {
            throw std::runtime_error("Directory does not exist: " + datasetDir);
        }
        scanDirectoryRecursive(datasetDir, extension, paths);
        return paths;
    }

    std::filesystem::path rootPath(){
        return fs::path(__FILE__).parent_path().parent_path().parent_path();
    }

    std::filesystem::path dataPath(){
        return io_utils::rootPath() / "data";
    }

    std::filesystem::path datasetsPath(){
        return io_utils::rootPath() / "data" / "datasets";
    }

    
        
    std::string getCurrentDateString() {
        auto now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);

        std::tm local_tm{};
    #ifdef _WIN32
        localtime_s(&local_tm, &now_c);
    #else
        localtime_r(&now_c, &local_tm);
    #endif

        char buffer[80];
        strftime(buffer, sizeof(buffer), "%d_%m_%Y", &local_tm);
        return std::string(buffer);

    }
    
    std::string getCurrentDateTimeString() {
        std::time_t now_c = std::time(nullptr);
        std::tm local_tm{};
    #if defined(_WIN32)
        localtime_s(&local_tm, &now_c);
    #else
        localtime_r(&now_c, &local_tm);
    #endif
    
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%d_%m_%Y__%H_%M_%S", &local_tm);
        return std::string(buffer);
    }
}
