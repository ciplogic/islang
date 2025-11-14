#include <iostream>

#include "common/SimLang.h"
#include "common/Utils.h"

int main() {
    Str basePath = "C:\\oss\\konsole-main";
    Str extension = ".kt";
    Vec<Str> files = io::filesInDir(basePath, extension);
    std::cout << "Hello World!\n";
    return 0;
}
