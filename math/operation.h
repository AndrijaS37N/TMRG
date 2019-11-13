#ifndef TMRG_OPERATION_H
#define TMRG_OPERATION_H

#include "../global/console_coloring.h"

class Operation {
public:
    template<typename T>
    static T abs(T &numeric_value);
};

template<typename T>
T Operation::abs(T &numeric_value) {
    try {
        if (is_arithmetic<T>::value)
            return (numeric_value < 0) ? -numeric_value : numeric_value;
        else
            throw "Operation::abs reports that a non arithmetic value was passed.";
    } catch (const char *thrown) {
        ConsoleColoring::red(thrown);
        return 0;
    }
}

#endif // TMRG_OPERATION_H
