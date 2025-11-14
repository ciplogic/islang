#include "Scanner.h"

#include <functional>

using TokenMatcherFunc = Func<int(StrView)>;

struct LexerRule {
    TokenKind kind;
    TokenMatcherFunc tokenMatcher;
};

bool Char_isSpace(char c) {
    return c == ' ' || c == '\t';
}

bool Char_isEoln(char c) {
    return c == '\n' || c == '\r';
}

int matchAll(StrView str, const Func<bool(char)> &tokenMatcher) {
    std::size_t length = str.length();
    for (int i = 0; i < length; i++) {
        if (tokenMatcher(str[i])) {
            return i;
        }
    }
    return length;
}

int match(StrView str, const Func<bool(char)> &tokeFirst, const Func<bool(char)> &tokenMatcher) {
    if (!tokeFirst(str[0])) {
        return 0;
    }
    std::size_t length = str.length();
    for (int i = 1; i < length; i++) {
        if (tokenMatcher(str[i])) {
            return i;
        }
    }
    return length;
}

int matchSpaces(StrView str) {
    return matchAll(str, Char_isSpace);
}

int matchEoln(StrView str) {
    return matchAll(str, Char_isEoln);
}

Vec<LexerRule> setLexerRules() {
    Vec<LexerRule> result;
    result.push_back({TokenKind::Spaces, matchSpaces});
    result.push_back({TokenKind::Eoln, matchEoln});
    return result;
}


namespace {
    Vec<LexerRule> lexerRules = setLexerRules();
}

void Scanner::setCode(StrView code) {
    _code = code;
    _pos = 0;
}
