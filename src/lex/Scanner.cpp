#include "Scanner.h"

#include <functional>

#include "ScannerUtils.h"
#include "../common/Utils.h"

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

int matchAnyOf(StrView str, Vec<Str> &vecValues) {
    for (Str &candidate: vecValues) {
        if (str.starts_with(candidate)) {
            return candidate.length();
        }
    }
    return 0;
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

int matchAnnotation(StrView str) {
    if (str[0] != '@') {
        return 0;
    }

    StrView remainder = str.substr(1);
    int lenId = matchIdentifier(remainder);
    return lenId == 0 ? 0 : 1 + lenId;
}

namespace {
    Vec<Str> _operators = {
        "==", "=", "+", "-", "*", "/", "%",
        ",", "!", "?", "&&", "||",
        ".", "<", ">", ";", ":"
    };
    Vec<Str> _parens = {"{", "}", "[", "]", "(", ")"};
    Vec<Str> _reservedWords = {"fun", "package"};
}

int matchOperator(StrView str) {
    return matchAnyOf(str, _operators);
}

int matchParens(StrView str) {
    return matchAnyOf(str, _parens);
}

int matchReserved(StrView str) {
    int matchLen = matchIdentifier(str);
    if (!matchLen) {
        return 0;
    }

    int matchReserved = matchAnyOf(str, _reservedWords);
    return matchReserved == matchLen
               ? matchReserved
               : 0;
}

int matchString(StrView str) {
    char first = str[0];
    if (first != '"' && first != '\'') {
        return 0;
    }
    for (int i = 1; i < str.length(); i++) {
        if (str[i] == first) {
            return i + 1;
        }
    }

    return 0;
}

int matchNumber(StrView str) {
    return matchAll(str, Char_isDigit);
}

int matchComment(StrView str) {
    if (str[0] != '/') return 0;
    if (str.length() < 2) return 0;
    if (str[1] != '*' || str[1] != '/') {return 0;}
    bool isLineComment = str[0] == '/';
    if (isLineComment) {
        int eolnPos = utils::indexOf(str, '\n');
        if (eolnPos == -1) {
            return str.length();
        }
        return eolnPos;
    }
    //multi line comments are not yet resolved
    return 0;
}

struct LexerRule {
    TokenKind kind;
    TokenMatcherFunc tokenMatcher;
};

Vec<LexerRule> setLexerRules() {
    Vec<LexerRule> result;
    result.push_back({TokenKind::Spaces, matchSpaces});
    result.push_back({TokenKind::Eoln, matchEoln});
    result.push_back({TokenKind::Comment, matchComment});

    result.push_back({TokenKind::String, matchString});
    result.push_back({TokenKind::Reserved, matchReserved});
    result.push_back({TokenKind::Annotation, matchAnnotation});
    result.push_back({TokenKind::Identifier, matchIdentifier});
    result.push_back({TokenKind::Parens, matchParens});
    result.push_back({TokenKind::Operator, matchOperator});
    result.push_back({TokenKind::Number, matchNumber});
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

Token Scanner::peek() const {
    StrView str = _code.substr(_pos);
    if (str.empty()) {
        return Token{"", _pos, TokenKind::EndOfFile};
    }

    Vec<LexerRule> &rules = lexerRules;
    for (auto &rule: rules) {
        int matchLen = rule.tokenMatcher(str);
        if (!matchLen) {
            continue;
        }
        Str tokenText{str.substr(0, matchLen)};
        Token token{tokenText, _pos, rule.kind};
        return token;
    }

    return {ScannerUtils::getErrorOut(str), _pos, TokenKind::Error};
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

bool Scanner::advanceMatch(const Func<bool(Token)> &matchToken) {
    skipSpaces(*this);
    auto currentToken = peek();
    bool isMatching = matchToken(currentToken);
    if (isMatching) {
        scannerSkipToken(*this, currentToken);
    }
    return isMatching;
}
