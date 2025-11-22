package lt.khlud.ciprian.islang.parsing.parens

import lt.khlud.ciprian.islang.common.Res.error
import lt.khlud.ciprian.islang.common.Res.ok
import lt.khlud.ciprian.islang.common.TResult
import lt.khlud.ciprian.islang.lexing.Scanner
import lt.khlud.ciprian.islang.lexing.ScannerEofMode
import lt.khlud.ciprian.islang.lexing.entities.Token

public enum class RowParenAstNodeKind {
    Terminal,
    Program,
    ParenBlock,
    RowTokens
}
