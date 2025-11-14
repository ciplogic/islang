#include <iostream>

#include "common/SimLang.h"
#include "common/Utils.h"
#include "lex/Scanner.h"

void scanKtFile(const Str &fileName) {
    Str fileContent = io::readAllFile(fileName);
    Scanner scanner;
    scanner.setCode(fileContent);
    std::cout << "File name: " << fileName << std::endl;
    while (true) {
        auto token = scanner.peek();
        if (token.kind == TokenKind::Error) {
            std::cout << "Error: " << token.text << std::endl;
            return;
        }
        if (token.kind == TokenKind::Eoln) {
            return;
        }

        std::cout << "Token: ('" << token.text <<
                "'," << (int) token.kind
                << ')'
                << std::endl;
        scanner.advanceText(token.text);
    }
}

int main() {
    Str basePath = "C:\\oss\\konsole-main";
    Str extension = ".kt";
    Vec<Str> files = io::filesInDir(basePath, extension);
    for (Str &file: files) {
        scanKtFile(file);
    }

    std::cout << "Hello World!\n";
    return 0;
}
