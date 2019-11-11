#ifndef TMRG_MIN_PERIOD_H
#define TMRG_MIN_PERIOD_H

#include <iostream>
#include <stack>

using namespace std;

class MinPeriod {
public:
    static void activate_task();
private:
    static int min_period(const int *array, const int &size);
    constexpr static void find_dividers(stack<int> &dividers, const int &size);
    inline static void print_dividers(stack<int> dividers);
};

#endif // TMRG_MIN_PERIOD_H
