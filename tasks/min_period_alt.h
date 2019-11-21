#ifndef TMRG_MIN_PERIOD_ALT_H
#define TMRG_MIN_PERIOD_ALT_H

#include "../structures/linked_list.h"

class MinPeriodAlt {
public:
    void activate_task();
private:
    int min_period_alt(const int *array, const int &size, LinkedList<int> &lls);
    int *find_dividers(const int &size);
};

#endif // TMRG_MIN_PERIOD_ALT_H
