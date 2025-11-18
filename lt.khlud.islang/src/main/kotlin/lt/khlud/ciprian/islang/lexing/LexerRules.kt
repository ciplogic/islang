package lt.khlud.ciprian.islang.lexing

import lt.khlud.ciprian.islang.common.StringView


fun matchSpaces(text: StringView): Int = matchLenAll(text, { it == ' ' || it == '\t' })
fun matchEoln(text: StringView): Int = matchLenAll(text, { it == '\n' || it == '\r' })

val operators = arrayListOf<String>(
    "..<", "..",
    ".", ",",
    "<", ">",
    "||", "&&",
    "==",
    "+", "-", "*", "/", "%",
    "!", "?.", "?",
    "!=",
    ":", ";", "="
)
fun matchOp(text: StringView): Int {
    return matchExactAny(text, operators)
}

val parens = arrayListOf<String>("(", ")", "{", "}", "[", "]")
fun matchParen(text: StringView): Int {
    return matchExactAny(text, parens)
}

fun isIdAlpha(ch: Char): Boolean = ((ch >= 'a') && (ch <= 'z')) || ((ch >= 'A') && (ch <= 'Z')) || (ch == '_')

fun isNumeric(ch: Char): Boolean = (ch >= '0') && (ch <= '9')

val reservedWords = arrayListOf<String>(
    "abstract",
    "as",
    "assert",
    "break",
    "class",
    "continue",
    "data",
    "do",
    "else",
    "enum",
    "expect",
    "false",
    "for",
    "fun",
    "get",
    "if",
    "interface",
    "inner",
    "lateinit",
    "object",
    "open",
    "operator",
    "out",
    "override",
    "package",
    "private",
    "protected",
    "receiver",
    "return",
    "sealed",
    "set",
    "super",
    "tailrec",
    "this",
    "throw",
    "true",
    "try",
    "type",
    "val",
    "var",
    "when",
    "while",
    "yield",
)

fun matchReservedWords(text: StringView) : Int {
    val matchLen = matchIdentifier(text)
    if (matchLen==0){
        return 0
    }
    val matchReservedLen = matchExactAny(text, reservedWords)
    if (matchReservedLen != matchLen){
        return 0
    }
    return matchReservedLen
}

fun matchIdentifier(text: StringView): Int = matchLenIf(text, { isIdAlpha(it) }, { isIdAlpha(it) || isNumeric(it) })

fun matchString(text: StringView): Int {
    var firstCh = text[0]
    val matchesFirst = (firstCh == '"') || (firstCh == '\'')
    if (!matchesFirst) {
        return 0
    }
    var isEscaped = false;
    for (i in 1..<text.length) {
        if (isEscaped){
            isEscaped = false
            continue
        }
        if (text[i] == '\\'){
            isEscaped = true;
            continue
        }
        if (text[i] == firstCh){
            return i+1;
        }
    }

    return 0
}

fun matchNumber(text: StringView): Int = matchLenAll(text, { isNumeric(it) })
