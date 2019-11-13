#ifndef TMRG_CONSOLE_COLORING_H
#define TMRG_CONSOLE_COLORING_H

#include <iostream>

namespace ConsoleColoring {
    template<typename T>
    void cyan(const T &special);
    template <typename T>
    void blue(const T &info);
    template <typename T>
    void yellow(const T &warning);
    template <typename T>
    void red(const T &error);
}

template <typename T>
void ConsoleColoring::cyan(const T &special) {
    std::cout << "\033[1;36m" << special << "\033[0m\n";
}

template <typename T>
void ConsoleColoring::blue(const T &info) {
    std::cout << "\033[0;34m" << info << "\033[0m\n";
}

template <typename T>
void ConsoleColoring::yellow(const T &warning) {
    std::cout << "\033[0;33m" << warning << "\033[0m\n";
}

template <typename T>
void ConsoleColoring::red(const T &error) {
    std::cout << "\033[0;31m" << error << "\033[0m\n";
}

#endif // TMRG_CONSOLE_COLORING_H
