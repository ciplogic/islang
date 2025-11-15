#include <iostream>

#include "common/SimLang.h"
#include "common/Utils.h"
#include "lex/Scanner.h"

void scanKtFile(const Str &fileName) {
    Str fileContent = io::readAllFile(fileName);
    Scanner scanner;
    scanner.setCode(fileContent);
    std::cout << "File name: " << fileName << std::endl;
    std::cout << "Tokens: " << std::endl;
    while (true) {
        auto token = scanner.peek();
        if (token.kind == TokenKind::Error) {
            std::cout << "\nError: " << token.text << std::endl;
            return;
        }
        if (token.kind == TokenKind::Eoln) {
            scanner.advanceText(token.text);
            continue;
        }
        if (token.kind == TokenKind::EndOfFile) {
            return;
        }

        std::cout << "('" << token.text <<
                "'," << (int) token.kind
                << "),";
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

    return 0;
}
