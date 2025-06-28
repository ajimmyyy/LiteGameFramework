//
// Created by jimmy on 2025/6/26.
//
#include "../../include/Platform/FileSystem.h"
#include <fstream>
#include <sstream>
#include <filesystem>

std::string FileSystem::basePath = "";

std::string FileSystem::ReadTextFile(const std::string& path) {
    std::ifstream file(ResolvePath(path));
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + path);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

std::vector<char> FileSystem::ReadBinaryFile(const std::string& path) {
    std::ifstream file(ResolvePath(path), std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + path);
    }

    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    file.seekg(0);

    std::vector<char> data(size);
    file.read(data.data(), size);
    return data;
}

bool FileSystem::Exists(const std::string& path) {
    return std::filesystem::exists(ResolvePath(path));
}

std::vector<std::string> FileSystem::ListFiles(const std::string& directory) {
    std::vector<std::string> files;
    for (const auto& entry : std::filesystem::directory_iterator(ResolvePath(directory))) {
        files.push_back(entry.path().string());
    }
    return files;
}

void FileSystem::SetBasePath(const std::string& base) {
    basePath = base;
}

std::string FileSystem::ResolvePath(const std::string& relative) {
    if (basePath.empty())
        return relative;
    return basePath + "/" + relative;
}
