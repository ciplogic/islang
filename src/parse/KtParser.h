#pragma once
#include "../lex/Scanner.h"

enum class AstNodeType {
    Terminal,
    Program,
};

struct KtAstNode {
    Token token;
    AstNodeType type;
    Vec<KtAstNode> children;
};

struct KtParser {
    Scanner scanner{};
};
