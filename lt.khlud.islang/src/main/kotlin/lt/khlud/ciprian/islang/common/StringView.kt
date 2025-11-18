package lt.khlud.ciprian.islang.common

data class StringView(val text: String, val start: Int, val length: Int) {
    fun slice(startCut: Int) = StringView(text, start + startCut, length - startCut)
    fun slice(startCut: Int, len: Int) = StringView(text, start + startCut, len)

    override fun toString(): String =
        text.substring(start, start + length)

    operator fun get(i: Int): Char = text[start + i]
}

fun String.toView(): StringView =
    StringView(this, 0, this.length)

fun List<String>.joinTexts(separator: String): String {
    var first = true
    val stringBuilder = StringBuilder()
    for (item in this) {
        if (first) {
            first = false
        } else {
            stringBuilder.append(separator)
        }
        stringBuilder.append(item)
    }
    return stringBuilder.toString()
}
