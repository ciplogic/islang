package lt.khlud.ciprian.islang.lexing.entities

import lt.khlud.ciprian.islang.common.StringView

data class LexerRule(
    val tokenKind: TokenKind,
    val match: (StringView) -> Int
)