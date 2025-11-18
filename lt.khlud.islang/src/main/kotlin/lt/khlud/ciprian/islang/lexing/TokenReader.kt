package lt.khlud.ciprian.islang.lexing

class TokenReader (val scanner: Scanner) {
    var pos = 0
    var peek = scanner.advance()

}