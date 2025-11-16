#pragma once
#include "SimLang.h"

template<class T>
struct TResult {
    T value{};
    Str errorMessage;

    explicit operator bool() const {
        return errorMessage.empty();
    }
    template <class TOut>
    TResult<TOut> err() {
        return {{}, errorMessage};
    }
};

template<class T>
TResult<T> ok(const T &value) {
    return {value, ""};
}


template<class T>
TResult<T> error(const Str &errorMessage) {
    return {{}, errorMessage};
}

template<class TSrc, class TDest>
TResult<TDest> error(const TResult<TSrc> &resultWithError) {
    return error<TDest>(resultWithError.errorMessage);
}
