#pragma once

#include "../common/SimLang.h"

enum class TokenKind {
    None,
    String,
    Number,
    Identifier,
    Operator,
    Reserved,
    Spaces,
    Eoln,
};

struct Token {
    Str text;
    TokenKind kind;
};

struct Scanner {
    int _pos {};
    StrView _code {};

    void setCode(StrView code);
};

