#ifndef TMRG_OPERATION_H
#define TMRG_OPERATION_H

#include "../global/console_coloring.h"
#include <type_traits>
#include <sstream>
#include <string>
#include <math.h>
#include <utility>

class Operation {
public:
    template<typename T>
    static T abs(T &numeric_value);
};

template<typename T>
T Operation::abs(T &numeric_value) {
    try {
        if (numeric_value != NULL)
            return (numeric_value < 0) ? -numeric_value : numeric_value;
        else
            throw "Operation::abs reports that something went wrong.";
    } catch (const char *thrown) {
        ConsoleColoring::red(thrown);
        return 0;
    }
}

#endif // TMRG_OPERATION_H
