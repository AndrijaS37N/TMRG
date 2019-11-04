#include "../global/console_coloring.h"
#include "min_period.h"
#include <vector>
#include <unistd.h>

using namespace std;

int MinPeriod::min_period(const int *array, const int &size) {
    if (array == nullptr or size < 1)
        return 0;

    stack<int> dividers;
    find_dividers(dividers, size);
    cout << "Dividers size: " << dividers.size() << endl;
    cout << "Dividers list: ";
    print_dividers(dividers);
    usleep(1000 * 1000);

    vector<vector<int>> vectors;
    vector<int> sub_vector;
    int component_size;
    bool are_same = true;
    int counter;

    while (!dividers.empty()) {
        component_size = size / dividers.top();
        counter = 0;
        for (int i = 0; i < dividers.top(); i++) {
            for (int k = 0; k < component_size; k++) {
                sub_vector.push_back(array[counter]);
                counter++;
            }
            vectors.push_back(sub_vector);
            are_same &= vectors[0] == vectors[i];
            sub_vector.clear();
        }

        if (!are_same) {
            vectors.clear();
            dividers.pop();
            are_same = true;
            continue;
        } else {
            cout << endl << "Loop result: ";
            return component_size;
        }
    }

    cout << endl << "Default result: ";
    return size;
}

void MinPeriod::find_dividers(stack<int> &dividers, const int &size) {
    for (int i = 1; i <= size; i++)
        if (size % i == 0)
            dividers.push(i);
}

void MinPeriod::print_dividers(stack<int> dividers) {
    while (!dividers.empty()) {
        cout << dividers.top() << ' ';
        dividers.pop();
    }
    cout << endl;
}

void MinPeriod::activate_task() { // Test cases are below.
    ConsoleColoring::cyan("Minimal Period Task");
    // int min_period_array[] = {2, 5, 3, 4, 6, 7, 8, 8, 4};
    // int min_period_array[] = {2, 5, 3, 4, 2, 5, 3, 4};
    // int min_period_array[] = {1, 1, 1, 1, 1, 1};
    // int min_period_array[] = {1, 2, 3, 1, 2, 3};
    // int min_period_array[] = {2, 2, 2, 1, 2, 2, 2};
    // int min_period_array[] = {2, 2, 2, 1, 2, 2, 2, 3, 3, 4, 1, 2, 4};
    // int min_period_array[] = {2, 5, 2, 0, 0, 0, 0, 2, 5, 2};
    cout << endl;
    int min_period_array[] = {2, 2, 2, 1, 2, 2, 2, 3, 3, 4, 1, 2, 3, 4, 5};
    int size = (sizeof(min_period_array) / sizeof(*min_period_array));
    cout << min_period(min_period_array, size) << endl;
}
