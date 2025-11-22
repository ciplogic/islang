package lt.khlud.ciprian.islang.parsing.parens

import lt.khlud.ciprian.islang.common.Res.error
import lt.khlud.ciprian.islang.common.Res.ok
import lt.khlud.ciprian.islang.common.TResult
import lt.khlud.ciprian.islang.lexing.Scanner
import lt.khlud.ciprian.islang.lexing.ScannerEofMode
import lt.khlud.ciprian.islang.lexing.entities.Token


fun scanFileAsParenTree(scanner: Scanner): TResult<RowParenAstNode> {
    val linesOfTokens = scanInMultiLines(scanner)
    if (!linesOfTokens.hasValue()) {
        return linesOfTokens.error()
    }

    var result = parseListToRowParen(linesOfTokens.value!!)

    return ok(result)
}

fun scanInMultiLines(scanner: Scanner) : TResult<ArrayList<ArrayList<Token>>>{

    val linesOfTokens = ArrayList<ArrayList<Token>>()
    do {
        val tokenRows = scanner.getTokensUpToEoln()
        if (!tokenRows.hasValue()) {
            return tokenRows.error()
        }
        val tokensVec = tokenRows.value!!
        if (tokensVec.isEmpty())
            continue
        linesOfTokens.add(tokensVec)

        if (scanner.isEof() != ScannerEofMode.HasMoreTokens)
        {
            break
        }
    } while (true)
    return ok(linesOfTokens)
}

fun parseListToRowParen(linesOfTokens: ArrayList<ArrayList<Token>>): RowParenAstNode {
    val result = RowParenAstNode(RowParenAstNodeKind.Program)
    for(rowTokens in linesOfTokens){
        var hasParenTokens = (hasOpenOrCloseTokens(rowTokens))
        if (!hasParenTokens){
            addSimpleTokensToResult(result, rowTokens)
            continue
        }
    }

    return result
}

fun addSimpleTokensToResult(
    result: RowParenAstNode,
    rowTokens: ArrayList<Token>
) {
    var rowAstNode = RowParenAstNode(RowParenAstNodeKind.RowTokens)
    for(tok in rowTokens){
        rowAstNode.children.add(RowParenAstNode(RowParenAstNodeKind.Terminal, tok))
    }
    result.children.add(rowAstNode)
}

val openingTokens =arrayListOf("(", "[", "{")

val closingTokens =arrayListOf(")", "]", "}")

private fun isOpenToken(token: Token) : Boolean {
    return openingTokens.contains(token.text)
}
private fun hasOpenTokens(tokens: List<Token>) : Boolean {
    for(tok in tokens) {
        if (isOpenToken(tok)){
            return true
        }
    }
    return false
}

private fun isClosedToken(token: Token) : Boolean {
    return closingTokens.contains(token.text)
}

private fun hasCloseTokens(tokens: List<Token>) : Boolean {
    for(tok in tokens) {
        if (isClosedToken(tok)){
            return true
        }
    }
    return false
}

private fun hasOpenOrCloseTokens(tokens: List<Token>) : Boolean {
    return hasOpenTokens(tokens) || hasCloseTokens(tokens)
}