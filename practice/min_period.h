#ifndef TMRG_MIN_PERIOD_H
#define TMRG_MIN_PERIOD_H

#include <iostream>
#include <stack>

class MinPeriod {
public:
    static int min_period(const int *array, const int &size);
    static void find_dividers(std::stack<int> &dividers, const int &size);
    static void print_dividers(std::stack<int> dividers);
    static void activate_task();
};

#endif // TMRG_MIN_PERIOD_H
