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

namespace utils {
    int indexOf(const Str &s, char c);
    int indexOf(StrView s, char c);
    Str strFmt(const Str &fmt, std::initializer_list<Str> args);
    Str strJoin(const Str &sep, const std::vector<Str> &args);

    void print(const Str &s);
    void printLn(const Str &s);
    void print(const Str &fmt, std::initializer_list<Str> args);
    void printLn(const Str &fmt, std::initializer_list<Str> args);
}

namespace io {
    Vec<Str> filesInDir(const Str &dirName, const Str &extension);
    Str readAllFile(const Str &fullFileName);
}
