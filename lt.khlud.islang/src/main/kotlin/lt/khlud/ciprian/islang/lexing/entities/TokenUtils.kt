package lt.khlud.ciprian.islang.lexing.entities

object TokenUtils {
    val Empty = Token("", TokenKind.None, 0)
    val Eof = Token("", TokenKind.EndOfFile, 0)
}