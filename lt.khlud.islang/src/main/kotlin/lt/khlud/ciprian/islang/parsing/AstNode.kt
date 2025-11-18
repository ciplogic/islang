package lt.khlud.ciprian.islang.parsing

import lt.khlud.ciprian.islang.lexing.entities.Token

data class AstNode(
    var token : Token,
    var nodeType: AstNodeType
) {
    var parentNode: AstNode? = null
    val children: ArrayList<AstNode> = arrayListOf()
}