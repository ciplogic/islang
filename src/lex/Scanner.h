#pragma once

#include "../common/SimLang.h"

enum class TokenKind {
    None,
    Error,
    String,
    Number,
    Identifier,
    Operator,
    Reserved,
    Spaces,
    Eoln,
    EndOfFile,
    Comment,
};

struct Token {
    Str text;
    TokenKind kind;
};

bool skipSpacesAndComments(const Token& token);

struct Scanner {
    int _pos{};
    StrView _code{};
    Func<bool(Token)> shouldSkipToken = skipSpacesAndComments;

    void setCode(StrView code);

    Token peek() const;
    bool advanceText(const Str& tokenText);

    bool advanceMatch(Func<bool(Token)> matchToken);
};
