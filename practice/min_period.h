#ifndef TMRG_MIN_PERIOD_H
#define TMRG_MIN_PERIOD_H

#include <iostream>
#include <stack>

class MinPeriod {
private:
    static int min_period(const int *array, const int &size);
    static void find_dividers(std::stack<int> &dividers, const int &size);
    static void print_dividers(std::stack<int> dividers);
public:
    static void activate_task();
};

#endif // TMRG_MIN_PERIOD_H
