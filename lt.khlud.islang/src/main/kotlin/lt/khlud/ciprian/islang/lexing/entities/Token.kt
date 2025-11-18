package lt.khlud.ciprian.islang.lexing.entities

data class Token(val text: String, val tokenKind: TokenKind, val pos: Int)
