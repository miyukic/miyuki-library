/*
clang++ -Wall -Wextra -O2 -std=c++2a main.cpp StopWatch.cpp
*/
#include <Windows.h>
#include <iostream>
#include "StopWatch.hpp"
using namespace myk::lib::util;

int main() {
    StopWatch sw;
    sw.start();
    Sleep(5000);
    sw.stop();
    auto result = sw.result();
    std::cout << sw.result() << std::endl;
}
