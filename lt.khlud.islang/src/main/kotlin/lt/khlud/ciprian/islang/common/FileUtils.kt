package lt.khlud.ciprian.islang.common

import java.io.BufferedReader
import java.io.File

object FileUtils {
    fun readAllText(fileName: String): String {
        val bufferedReader: BufferedReader = File(fileName).bufferedReader()
        val inputString = bufferedReader.use { it.readText() }
        return inputString
    }

    fun filesInDirectory(dirName: String, extension: String = ""): List<String> {
        val result = arrayListOf<String>()
        populateDirectory(dirName, extension, result)
        return result
    }

    private fun populateDirectory(dirName: String, extension: String, outList: MutableList<String>) {
        val folder = File(dirName)
        val listOfFiles = folder.listFiles() ?: return

        for (file in listOfFiles) {
            if (!file.isFile()) {
                populateDirectory("$dirName/${file.name}", extension, outList)
                continue
            }

            if (file.name.endsWith(extension)) {
                outList.add("$dirName/${file.name}")
            }
        }
    }
}