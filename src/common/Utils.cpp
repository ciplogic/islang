#include "Utils.h"

#include <filesystem>
#include <fstream>
#include <iostream>

int indexOf(const Str &s, char c) {
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == c) {
            return i;
        }
    }
    return -1;
}

int utils::indexOf(StrView s, char c) {
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == c) {
            return i;
        }
    }
    return -1;
}

Str strFmt(const Str &fmt, std::initializer_list<Str> args) {
    Str result = fmt;
    int pos = 0;
    Str key;
    for (const Str &arg: args) {
        key.clear();
        key += '$';
        key += std::to_string(pos);
        result = result.replace(fmt.find(key), key.length(), arg);
        pos++;
    }
    return result;
}

Vec<Str> io::filesInDir(const Str &path, const Str &extension) {
    std::filesystem::directory_entry p(path);
    if (!p.exists()) {
        return {};
    }
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

std::string replaceString(std::string str, const std::string &oldStr, const std::string &newStr) {
    size_t pos = 0;
    while ((pos = str.find(oldStr)) != std::string::npos) {
        str.replace(pos, oldStr.size(), newStr);
    }
    return str;
}

Str utils::strFmt(const Str &fmt, std::initializer_list<Str> args) {
    Str result = fmt;
    int pos = 0;
    Str key;
    for (const Str &arg: args) {
        key.clear();
        key += '$';
        key += std::to_string(pos);
        result = replaceString(result, key, arg);
        pos++;
    }
    return result;
}


Str utils::strJoin(const Str &sep, const std::vector<Str> &args) {
    Str result;
    bool first = true;
    for (const auto &arg: args) {
        if (first) {
            first = false;
        } else {
            result += sep;
        }
        result += arg;
    }
    return result;
}

void utils::print(const Str &s) {
    std::cout << s;
}

void utils::printLn(const Str &s) {
    std::cout << s << "\n";
}

void utils::print(const Str &fmt, std::initializer_list<Str> args) {
    utils::print(utils::strFmt(fmt, args));
}

void utils::printLn(const Str &fmt, std::initializer_list<Str> args) {
    utils::printLn(utils::strFmt(fmt, args));
}
