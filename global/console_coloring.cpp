#include "console_coloring.h"
#include <iostream>

void ConsoleColoring::cyan(const char *special) {
    std::cout << "\033[1;36m" << special << "\033[0m\n";
}

void ConsoleColoring::blue(const char *info) {
    std::cout << "\033[0;34m" << info << "\033[0m\n";
}

void ConsoleColoring::yellow(const char *warning) {
    std::cout << "\033[0;33m" << warning << "\033[0m\n";
}

void ConsoleColoring::red(const char *error) {
    std::cout << "\033[0;31m" << error << "\033[0m\n";
}