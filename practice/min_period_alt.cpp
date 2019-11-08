#include "min_period_alt.h"
#include <iostream>

using namespace std;

int MinPeriodAlt::min_period_alt(const int *array, const int &size) { // TODO - Implement this with a linked list.
    return 0;
}

void MinPeriodAlt::activate_task() {
    int min_period_array[] = {2, 2, 2, 1, 2, 2, 2, 3, 3, 4, 1, 2, 3, 4, 5};
    int size = (sizeof(min_period_array) / sizeof(*min_period_array));
    cout << min_period_alt(min_period_array, size) << endl;
}
