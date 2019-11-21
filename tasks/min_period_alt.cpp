#include <iostream>
#include "min_period_alt.h"
#include "../structures/linked_list.h"

using namespace std;

int MinPeriodAlt::min_period_alt(const int *array, const int &size,
                                 LinkedList<int> &lls) { // TODO - Implement this with a linked list.
    cout << "Pushing into the list." << endl;
    for (int i = 0; i < size; ++i)
        lls.push(array[i]);

    lls.print_vertically();
    cout << '\n';
    lls.print_horizontally();
    cout << '\n';

    struct Node<int> *current = lls.get_head();
    int *tmp = find_dividers(size);
    int index = 0;
    while (tmp[index])
        index++;

    const int &tmp_size = index;
    bool period_completed = false;

    cout << "Result: ";
    for (int j = 0; j < tmp_size; ++j) {
        int jump_index = tmp[j];
        if (jump_index == size)
            break;
        while (jump_index < size) {
            if (current->data != (lls.get_element(jump_index))->data)
                break;
            else
                period_completed = true;
            current = current->next_node;
            jump_index++;
        }
        if (period_completed)
            return tmp[j];
        else
            continue;
    }

    free(tmp);
    return size; // Default result.
}

void MinPeriodAlt::activate_task() {
    int min_period_array[] = {2, 2, 2};
    int size = (sizeof(min_period_array) / sizeof(*min_period_array));
    LinkedList<int> lls(nullptr, "Min Period Alt Linked List");
    ConsoleColoring::cyan(lls.get_linked_list_name());
    cout << '\n';
    cout << min_period_alt(min_period_array, size, lls) << endl;
    cout << '\n';
}

int *MinPeriodAlt::find_dividers(const int &size) {
    int capacity = 2; // Prime numbers have at least two.
    int *tmp = (int *) malloc(sizeof(int) * capacity);
    int j = 0;
    for (int i = 1; i <= size; i++) {
        if (size % i == 0) {
            if (capacity < i) {
                capacity++;
                tmp = (int *) realloc(tmp, (sizeof(int) * capacity));
            }
            tmp[j] = i;
            j++;
        }
    }
    return tmp;
}
