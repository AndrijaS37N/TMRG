#ifndef TMRG_MIN_PERIOD_ALT_H
#define TMRG_MIN_PERIOD_ALT_H

#include "../structures/linked_list.h"

class MinPeriodAlt {
public:
    static void activate_task();
private:
    static int min_period_alt(const int *array, const int &size, LinkedList<int> &lls);
    static int *find_dividers(const int &size);
};

#endif // TMRG_MIN_PERIOD_ALT_H
