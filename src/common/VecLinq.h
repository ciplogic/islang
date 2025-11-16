#pragma once

#include <vector>
#include <functional>

#include "SimLang.h"

template<class TSrc, class TDest>
Vec<TDest> select(const Vec<TSrc> &items, Func<TDest(TSrc)> mapper) {
    Vec<TDest> result;
    for (auto &item: items) {
        result.push_back(mapper(item));
    }
    return result;
}

template<class T>
bool contains(const Vec<T> &items, Func<bool(T)> conditionFunc) {
    for (const T &item: items) {
        if (conditionFunc(item)) {
            return true;
        }
    }
    return false;
}
