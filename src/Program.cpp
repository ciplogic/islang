#include <iostream>

#include "common/SimLang.h"
#include "common/Utils.h"
#include "lex/Scanner.h"

using namespace utils;

void scanKtFile(const Str &fileName) {
    Str fileContent = io::readAllFile(fileName);
    Scanner scanner;
    scanner.setCode(fileContent);
    printLn(fileName);
    printLn("Tokens:");
    while (true) {
        auto token = scanner.peek();
        if (token.kind == TokenKind::Error) {
            printLn("\nError: '$0'", {token.text});
            return;
        }
        if (token.kind == TokenKind::Eoln) {
            scanner.advanceText(token.text);
            continue;
        }
        if (token.kind == TokenKind::EndOfFile) {
            return;
        }

        print("$0 ", {token.text});
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
