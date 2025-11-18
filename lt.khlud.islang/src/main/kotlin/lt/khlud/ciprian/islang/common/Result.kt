package lt.khlud.ciprian.islang.common

object Res{
    fun<T> ok(value: T) = TResult<T>(value, null)
    fun <T> error(errorMessage: String) = TResult<T>(null, errorMessage);
    fun <T, TFrom> TResult<TFrom>.error() = error<T>(this.errorMessage!!)
}
