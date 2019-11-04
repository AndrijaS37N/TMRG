#include "../global/console_coloring.h"
#include "linked_list.h"
#include <iostream>
#include <vector>

using namespace std;

void LinkedList::push(const short &number) {
    struct Node *new_node = new Node;
    if (new_node == nullptr)
        ConsoleColoring::red("Memory allocation failed.");
    else {
        new_node->data = number;
        new_node->next_node = head;
        head = new_node;
        list_size++;
    }
}

void LinkedList::print_vertically() {
    cout << "Vertical view:";
    short digits_length;
    struct Node *current_node = head;
    vector<vector<string>> print_matrix;

    while (current_node) {
        cout << '\n';
        digits_length = find_digits_length(current_node->data);
        print_horizontal_lines(digits_length);
        cout << '\n';
        cout << "| " << current_node->data << " |";
        cout << '\n';
        print_horizontal_lines(digits_length);
        cout << '\n';
        cout << "  |";
        cout << '\n';
        cout << "  V";
        current_node = current_node->next_node;
    }
    cout << endl << "nullptr" << endl;
}

void LinkedList::print_horizontally() {
    cout << "Horizontal view: ";
    struct Node *current_node = head;
    vector<vector<string>> print_matrix;

    while (current_node) {
        cout << "[ " << current_node->data << " ] -> ";
        current_node = current_node->next_node;
    }
    cout << "nullptr" << endl;
}

int LinkedList::find_digits_length(short number) {
    int length;
    if (number > 0) {
        for (length = 0; number > 0; length++)
            number = number / 10;
        length += 2;
    } else {
        number = abs(number);
        for (length = 0; number > 0; length++)
            number = number / 10;
        length += 3;
    }

    return length;
}

void LinkedList::print_horizontal_lines(const short &digits_length) {
    cout << ' ';
    for (int i = 0; i < digits_length; ++i)
        cout << '-';
}

void LinkedList::activate_task() {
    LinkedList lls(nullptr, "Linked List Structure");
    ConsoleColoring::cyan(lls.get_linked_list_name());
    lls.push(14);
    lls.push(-43);
    lls.push(32767);
    lls.push(000);
    lls.push(-1);
    lls.push(2);
    cout << '\n';
    lls.print_vertically();
    cout << '\n';
    lls.print_horizontally();
    cout << "Size: " << lls.get_list_size() << endl;
    for (int i = 0; i < 8; ++i)
        lls.pop();
    lls.print_horizontally();
    lls.print_vertically();
    cout << "Size: " << lls.get_list_size() << endl;
    ConsoleColoring::red("Testing error logging.");
    ConsoleColoring::blue("Testing info logging.");
}

const void LinkedList::pop() {
    if (head == nullptr)
        ConsoleColoring::yellow("Element not popped! Linked list has been emptied.");
    else {
        cout << "Element popped!" << endl;
        head = head->next_node;
        list_size--;
    }
}
