//
// Created by Maria on 13.05.2024.
//
#include "utils.h"
#include <filesystem>
#include <string>

void mkDirIfMiss(const std::string &dirName) {
    if (!std::filesystem::is_directory(dirName) || !std::filesystem::exists(dirName)) {
        std::filesystem::create_directory(dirName);
    }
}
