#include "Utils.h"

#include <filesystem>
#include <fstream>

Vec<Str> io::filesInDir(const Str &path, const Str &extension) {
    Vec<Str> result;
    for (const auto &entry: std::filesystem::directory_iterator(path)) {
        Str fullFileName = entry.path().string();
        if (entry.is_regular_file()) {
            if (fullFileName.ends_with(extension)) {
                result.push_back(fullFileName);
            }
            continue;
        }
        if (entry.is_directory()) {
            Vec<Str> childFiles = filesInDir(fullFileName, extension);
            addAll(result, childFiles);
        }
    }
    return result;
}

Str io::readAllFile(const Str &fullFileName) {
    std::ifstream inputFile(fullFileName.c_str(), std::ios::in);
    if (inputFile.is_open()) {
        return {
            (std::istreambuf_iterator<char>(inputFile)),
            std::istreambuf_iterator<char>()
        };
    }
    return "";
}

Vec<Str> readFileLines(const std::string &filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        return {};
    }

    Vec<Str> lines;
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    return lines;
}
