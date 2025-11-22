package lt.khlud.ciprian.islang.parsing.parens

import lt.khlud.ciprian.islang.lexing.entities.Token
import lt.khlud.ciprian.islang.lexing.entities.TokenUtils

data class RowParenAstNode(
    val kind : RowParenAstNodeKind,
    val token: Token = TokenUtils.Empty,
    val children: ArrayList<RowParenAstNode> = arrayListOf()
)