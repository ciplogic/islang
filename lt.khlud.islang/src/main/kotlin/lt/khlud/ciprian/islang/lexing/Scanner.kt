package lt.khlud.ciprian.islang.lexing

import lt.khlud.ciprian.islang.common.Res
import lt.khlud.ciprian.islang.common.Res.error
import lt.khlud.ciprian.islang.common.Res.ok
import lt.khlud.ciprian.islang.common.StringView
import lt.khlud.ciprian.islang.common.TResult
import lt.khlud.ciprian.islang.lexing.entities.Token
import lt.khlud.ciprian.islang.lexing.entities.TokenKind
import lt.khlud.ciprian.islang.lexing.entities.TokenUtils

class Scanner(var text: StringView) {
    var pos = 0
    var shouldSkipToken: (token: Token) -> Boolean = { skipSpacesAndComments(it) }

    fun skipToken(): TResult<Token> {
        var result = peek()
        if (result.hasValue()) {
            text = text.slice(result.value!!.text.length)
            pos += result.value.text.length
        }
        return result
    }

    fun advance(expected: String): Boolean {
        var result = skipToken()

        while (result.hasValue() && shouldSkipToken(result.value!!)) {
            skipToken()
            result = peek();
        }

        if (!result.hasValue()) {
            return false
        }
        var isMatching = result.value!!.text == expected
        if (isMatching) {
            pos += result.value.text.length
        }

        return isMatching
    }

    fun peek(): TResult<Token> {

        if (text.length == 0) {
            return Res.ok(TokenUtils.Eof)
        }
        val rules = LexerObject.Rules
        for (rule in rules) {
            val matchLen = rule.match(text)
            if (matchLen == 0) {
                continue
            }
            val tokenSlice = text.slice(0, matchLen)

            val token = Token(tokenSlice.toString(), rule.tokenKind, pos)
            return Res.ok(token)
        }

        var remainder = text.toString()
        if (remainder.length > 200) {
            remainder = remainder.take(200)
        }

        return Res.error("Cannot parse: $remainder")
    }

    fun getTokensUpToEoln(shouldSkip: Boolean = true): TResult<ArrayList<Token>> {
        val result = arrayListOf<Token>()
        do {
            val token = peek()
            if (!token.hasValue()) {
                return token.error()
            }
            skipToken()
            val tokenKind: TokenKind? = token.value!!.tokenKind
            val isEndToken: Boolean =
                (tokenKind === TokenKind.EndOfLine || tokenKind === TokenKind.EndOfFile)
            if (isEndToken) {
                return ok(result)
            } else {
                result.add(token.value)
            }

        } while (true)
    }

    override fun toString(): String {
        return text.slice(pos).toString()
    }
}

private fun skipSpacesAndComments(token: Token): Boolean {
    return when (token.tokenKind) {
        TokenKind.Spaces, TokenKind.Comment -> true
        else -> false
    }
}

fun Scanner.skipEmptyLines(): TResult<Boolean> {
    while (true) {
        var current = this.peek()
        if (!current.hasValue()) {
            return ok(false)
        }
        if (skipSpacesAndComments(current.value!!)) {
            this.skipToken()
            continue
        }
        if (current.value!!.tokenKind == TokenKind.EndOfLine) {
            skipToken()
            continue
        }

        return ok(true)

    }
}