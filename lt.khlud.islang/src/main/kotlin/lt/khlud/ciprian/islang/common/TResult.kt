package lt.khlud.ciprian.islang.common

data class TResult<T>(val value: T?, val errorMessage: String?) {
    fun hasValue() = errorMessage == null
    fun isError() = errorMessage != null
}