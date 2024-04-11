cmake_minimum_required(VERSION 3.27)
project(lab1_lexem_analisator)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab1_lexem_analisator main.cpp
        LexicalAnalyzer.cpp
        LexicalAnalyzer.h
        CheckOrder.cpp
        CheckOrder.h
)
