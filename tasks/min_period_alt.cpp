#include <iostream>
#include "min_period_alt.h"
#include "../structures/linked_list.h"

using namespace std;

int MinPeriodAlt::min_period_alt(const int *array, const int &size, LinkedList<int> &lls) { // TODO - Implement this with a linked list.
    for (int i = 0; i < size; ++i) {
        lls.push(array[i]);
    }
    lls.print_vertically();
    cout << '\n';
    lls.print_horizontally();
    cout << '\n';
    return 37;
}

void MinPeriodAlt::activate_task() {
    int min_period_array[] = {2, 2, 2, 1, 2, 2, 2, 3, 3, 4, 1, 2, 3, 4, 5};
    int size = (sizeof(min_period_array) / sizeof(*min_period_array));
    LinkedList<int> lls(nullptr, "Min Period Alt Linked List");
    ConsoleColoring::cyan(lls.get_linked_list_name());
    cout << '\n';
    cout << min_period_alt(min_period_array, size, lls) << endl;
    cout << '\n';
}
