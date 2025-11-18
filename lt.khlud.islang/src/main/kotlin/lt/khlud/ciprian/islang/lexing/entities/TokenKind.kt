package lt.khlud.ciprian.islang.lexing.entities

enum class TokenKind {
    None,
    Str,
    Id,
    Ops,
    Paren,
    Spaces,
    EndOfLine,
    Number,
    Reserved,
    Comment,
    EndOfFile
}