cmake_minimum_required(VERSION 4.0)
project(simac)

set(CMAKE_CXX_STANDARD 23)

# set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra -flto")
# set(CMAKE_EXE_LINKER_FLAGS "-flto")

add_executable(
        simac
        src/Program.cpp
        src/lex/Scanner.cpp
        src/lex/Scanner.h
        src/common/Utils.cpp
        src/common/Utils.h
        src/common/SimLang.h
        src/parse/KtParser.cpp
        src/parse/KtParser.h
        src/lex/ScannerUtils.cpp
        src/lex/ScannerUtils.h
)
