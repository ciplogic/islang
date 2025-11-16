#include "KtParser.h"

#include "../common/Utils.h"
#include "../common/VecLinq.h"

namespace {
    TResult<bool> parsePackage(Scanner &scanner, KtAstNode &program_node) {
        Vec<Token> tokens = scanner.getTokensUpToEoln().value;
        Vec<Str> tokenNames = select<Token, Str>(
            tokens,
            []( const auto &token) {
                return token.text;
            });
        Str packageName = utils::strJoin("", tokenNames);
        return {true};
    }

    TResult<bool> advanceParseGlobal(Scanner &scanner, KtAstNode &programNode) {
        TResult<bool> result = {true};

        if (scanner.advanceText("package")) {
            result = parsePackage(scanner, programNode);
            if (!result) {
                return result;
            }
        }
        return result;
    }
}

TResult<KtAstNode> parse(Scanner &scanner) {
    KtAstNode program{
        {{}, 0, TokenKind::None},
        AstNodeType::Program,
        {}
    };
    auto parseGlobal = advanceParseGlobal(scanner, program);

    return ok(program);
}

TResult<KtAstNode> parseCode(const Str &code) {
    Scanner scanner;
    scanner.setCode(code);
    return parse(scanner);
}
