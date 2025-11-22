package lt.khlud.ciprian.islang.parsing

import lt.khlud.ciprian.islang.common.Res.error
import lt.khlud.ciprian.islang.common.Res.ok
import lt.khlud.ciprian.islang.common.TResult
import lt.khlud.ciprian.islang.common.joinTexts
import lt.khlud.ciprian.islang.lexing.Scanner
import lt.khlud.ciprian.islang.lexing.skipEmptyLines

fun parseKotlinFile(fileName: String, scanner: Scanner): TResult<KotlinFileDeclarations> {
    val result = KotlinFileDeclarations()
    scanner.skipEmptyLines()
    var isPackage = scanner.advance("package");
    var rowTokens = scanner.getTokensUpToEoln()
    if (rowTokens.isError()) return rowTokens.error()

    var packageName = rowTokens.value!!.map { it.text }.joinTexts("")
    result.packageName = packageName


    return ok(result)
}

class KotlinFileDeclarations {
    var packageName = ""
    val imports = arrayListOf<String>()


}

