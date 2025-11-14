#include "Scanner.h"

#include <functional>

using TokenMatcherFunc = Func<int(StrView)>;

bool Char_isSpace(char c) {
    return c == ' ' || c == '\t';
}

bool Char_isEoln(char c) {
    return c == '\n' || c == '\r';
}

bool Char_isAlpha(char c) {
    return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '_';
}

bool Char_isDigit(char c) {
    return c >= '0' && c <= '9';
}

int matchAll(StrView str, const Func<bool(char)> &tokenMatcher) {
    std::size_t length = str.length();
    for (int i = 0; i < length; i++) {
        if (!tokenMatcher(str[i])) {
            return i;
        }
    }
    return length;
}

int matchByFilter(StrView str, const Func<bool(char)> &matchFirst, const Func<bool(char)> &matchRest) {
    if (!matchFirst(str[0])) {
        return 0;
    }
    std::size_t length = str.length();
    for (int i = 1; i < length; i++) {
        if (!matchRest(str[i])) {
            return i;
        }
    }
    return length;
}

//Lexer rules

int matchSpaces(StrView str) {
    return matchAll(str, Char_isSpace);
}

int matchEoln(StrView str) {
    return matchAll(str, Char_isEoln);
}

int matchIdentifier(StrView str) {
    return matchByFilter(
        str,
        Char_isAlpha,
        [](char c)-> bool {
            return Char_isAlpha(c) || Char_isDigit(c);
        });
}


struct LexerRule {
    TokenKind kind;
    TokenMatcherFunc tokenMatcher;
};

Vec<LexerRule> setLexerRules() {
    Vec<LexerRule> result;
    result.push_back({TokenKind::Spaces, matchSpaces});
    result.push_back({TokenKind::Eoln, matchEoln});
    result.push_back({TokenKind::Identifier, matchIdentifier});
    return result;
}


namespace {
    Vec<LexerRule> lexerRules = setLexerRules();
}

bool skipSpacesAndComments(const Token &token) {
    switch (token.kind) {
        case TokenKind::Spaces:
        case TokenKind::Comment:
            return true;
        default:
            return false;
    }
}

void Scanner::setCode(StrView code) {
    _code = code;
    _pos = 0;
}

Str extractErrorMessage(StrView remainingText) {
    if (remainingText.length() > 200) {
        remainingText = remainingText.substr(0, 200);
    }
    return Str(remainingText);
}

Token Scanner::peek() const {
    StrView str = _code.substr(_pos);
    if (str.empty()) {
        return Token{extractErrorMessage(str), TokenKind::EndOfFile};
    }

    Vec<LexerRule> &rules = lexerRules;
    for (auto &rule: rules) {
        int matchLen = rule.tokenMatcher(str);
        if (!matchLen) {
            continue;
        }
        Str tokenText{str.substr(0, matchLen)};
        Token token{tokenText, rule.kind};
        return token;
    }

    return {extractErrorMessage(str), TokenKind::Error};
}

bool Scanner::advanceText(const Str &tokenText) {
    return advanceMatch([&](const Token &tk) { return tk.text == tokenText; });
}

namespace {
    void scannerSkipToken(Scanner &scanner, const Token &token) {
        scanner._pos += token.text.length();
    }

    void skipSpaces(Scanner &scanner) {
        do {
            Token token = scanner.peek();
            if (!scanner.shouldSkipToken(token)) {
                return;
            }
            scannerSkipToken(scanner, token);
        } while (true);
    }
}

bool Scanner::advanceMatch(Func<bool(Token)> matchToken) {
    skipSpaces(*this);
    auto currentToken = peek();
    bool isMatching = matchToken(currentToken);
    if (isMatching) {
        scannerSkipToken(*this, currentToken);
    }
    return isMatching;
}
