#ifndef TMRG_OPERATION_H
#define TMRG_OPERATION_H

#include "../global/console_coloring.h"
#include <math.h>

const atomic_int64_t number_printing_edge = 1000000;

class Operation { // TODO -> Make a custom floor functions.
public:
    template<typename T>
    static T abs(const T &numeric_value);
    template<typename T>
    static bool check_integer(const T &numeric_value);
};

template<typename T>
T Operation::abs(const T &numeric_value) {
    try {
        if (is_arithmetic<T>::value)
            return (numeric_value < 0) ? -numeric_value : numeric_value;
        else
            throw "Operation::abs reports that something went wrong.";
    } catch (const char *thrown) {
        ConsoleColoring::red(thrown);
        return 0;
    }
}

template<typename T>
bool Operation::check_integer(const T &numeric_value) {
    if (numeric_value >= number_printing_edge)
        return false;
    auto alpha = floor(Operation::abs(numeric_value));
    auto beta = Operation::abs(numeric_value);
    return alpha == beta;
}

#endif // TMRG_OPERATION_H
