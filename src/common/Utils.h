#pragma once
#include "SimLang.h"

template<class T>
struct Nullable {
    T value{};
    bool isEmpty{};
};

template<class T>
Nullable<T> nullable(const T &value) {
    return {value, false};
}

template<class T>
Nullable<T> null() {
    return {{}, false};
}


template<class T>
struct TResult {
    T value{};
    Str errorMessage;
};


template<class T>
void addAll(Vec<T>& dest, Vec<T>& src) {
    for (T& i : src) {
        dest.push_back(i);
    }
}
namespace io {
    Vec<Str> filesInDir(const Str &dirName, const Str &extension);
    Str readAllFile(const Str &fullFileName);
}
