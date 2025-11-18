package lt.khlud.ciprian.islang.parsing

import lt.khlud.ciprian.islang.common.Res
import lt.khlud.ciprian.islang.common.TResult
import lt.khlud.ciprian.islang.lexing.Scanner
import lt.khlud.ciprian.islang.lexing.entities.Token
import lt.khlud.ciprian.islang.lexing.entities.TokenKind

val openParens = arrayListOf("(", "[", "{")

val closeParens = arrayListOf("(", "[", "{")

fun isOpenParen(operator: String): Boolean {
    return openParens.contains(operator)
}

fun isCloseParen(operator: String): Boolean {
    return openParens.contains(operator)
}

fun getRowTokens(scanner: Scanner): TResult<List<Token>> {
    var result = arrayListOf<Token>()
    while (true) {
        var token = scanner.advance()
        if (!token.hasValue()) {
            return Res.error(token.errorMessage!!)
        }
        val tokenKind = token.value?.tokenKind ?: TokenKind.None;
        if (tokenKind == TokenKind.Spaces) {
            continue
        }

        if (tokenKind == TokenKind.EndOfLine || tokenKind == TokenKind.None) {
            break
        }
        result.add(token.value!!)
    }
    return Res.ok(result)
}
