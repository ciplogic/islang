#pragma once

#include <vector>
#include <string>
#include <functional>

template<class T>
using Vec = std::vector<T>;

using Str = std::string;
using StrView = std::string_view;

template<class T>
using Func = std::function<T>;
