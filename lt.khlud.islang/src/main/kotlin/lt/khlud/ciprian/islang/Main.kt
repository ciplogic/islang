//main file
package lt.khlud.ciprian.islang

import lt.khlud.ciprian.islang.common.FileUtils
import lt.khlud.ciprian.islang.common.toView
import lt.khlud.ciprian.islang.lexing.Scanner
import lt.khlud.ciprian.islang.parsing.parseKotlinFile

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
fun main() {
    val name = "Kotlin"
    //TIP Press <shortcut actionId="ShowIntentionActions"/> with your caret at the highlighted text
    // to see how IntelliJ IDEA suggests fixing it.
    println("Hello, " + name + "!")

    for (i in 1..5) {
        //TIP Press <shortcut actionId="Debug"/> to start debugging your code. We have set one <icon src="AllIcons.Debugger.Db_set_breakpoint"/> breakpoint
        // for you, but you can always add more by pressing <shortcut actionId="ToggleLineBreakpoint"/>.
        println("i = $i")
    }
    val filesInDir = FileUtils.filesInDirectory(".", ".kt")

    for (fileName in filesInDir) {
        var mainContent = FileUtils.readAllText(fileName)
        parseFile(fileName, mainContent)
    }

    return

}


private fun parseFile(fileName: String, mainContent: String) {
    var scanner = Scanner(mainContent.toView())
    var parsedFile = parseKotlinFile(fileName, scanner)
}