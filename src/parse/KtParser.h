#pragma once
#include "../common/TResult.h"
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

TResult<KtAstNode> parse(Scanner &scanner);
TResult<KtAstNode> parseCode(const Str &code);
