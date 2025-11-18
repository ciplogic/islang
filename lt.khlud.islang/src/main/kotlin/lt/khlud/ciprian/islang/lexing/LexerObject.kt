package lt.khlud.ciprian.islang.lexing

import lt.khlud.ciprian.islang.common.StringView
import lt.khlud.ciprian.islang.lexing.entities.LexerRule
import lt.khlud.ciprian.islang.lexing.entities.TokenKind

object LexerObject {
    val Rules: List<LexerRule> = buildRules()

    private fun buildRules(): List<LexerRule> {
        val result = ArrayList<LexerRule>()
        result.add(LexerRule(TokenKind.Spaces, { matchSpaces(it) }))
        result.add(LexerRule(TokenKind.EndOfLine, { matchEoln(it) }))
        result.add(LexerRule(TokenKind.Reserved, { matchReservedWords(it) }))

        result.add(LexerRule(TokenKind.Id, { matchIdentifier(it) }))
        result.add(LexerRule(TokenKind.Str, { matchString(it) }))
        result.add(LexerRule(TokenKind.Ops, { matchOp(it) }))
        result.add(LexerRule(TokenKind.Number, { matchNumber(it) }))
        result.add(LexerRule(TokenKind.Paren, {  matchParen(it) }))
        return result
    }
}

fun matchLenIf(text: StringView, matchFirst: (Char) -> Boolean, matchRest: (Char) -> Boolean): Int {
    val first = text[0]
    if (!matchFirst(first)) {
        return 0
    }

    for (i in 1..<text.length) {
        val rest = text[i]
        if (!matchRest(rest)) {
            return i;
        }
    }
    return text.length
}

fun matchExactOne(text: StringView, word: String): Boolean {
    if (text[0] != word[0]) return false;
    if (text.length < word.length) {
        return false
    }
    for (i in 1..<word.length){
        if (text[i]!=word[i]){
            return false
        }
    }
    return true
}

fun matchExactAny(text: StringView, words: List<String>): Int {
    for (word in words) {
        if (matchExactOne(text, word)) {
            return word.length
        }
    }
    return 0
}

fun matchLenAll(text: StringView, matchFirst: (Char) -> Boolean) = matchLenIf(text, matchFirst, matchFirst)

