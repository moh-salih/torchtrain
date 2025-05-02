
#include <chrono>
#include <format>
#include <filesystem>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>


#include "utils/io_utils.h"

namespace logger{
    void init(){
        std::string filePath = (io_utils::dataPath() / "intermediate" / (io_utils::getCurrentDateTimeString() + ".log")).string();
        auto fileLogger = spdlog::basic_logger_mt("file_logger", filePath);
        spdlog::set_default_logger(fileLogger);
        spdlog::set_level(spdlog::level::debug);
        spdlog::set_pattern("[%H:%M:%S] [%^%l%$] %v");
    }
}