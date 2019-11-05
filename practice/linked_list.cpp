#include "../global/console_coloring.h"
#include "linked_list.h"
#include <iostream>
#include <string>

using namespace std;

void LinkedList::push(const short &number) {
    struct Node *new_node = new Node; // TODO -> Is this OK not to delete?
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

const void LinkedList::pop() {
    if (head == nullptr)
        ConsoleColoring::yellow("Element not popped! Linked list has been emptied.");
    else {
        cout << "Element popped!" << endl;
        head = head->next_node;
        list_size--;
    }
}

void LinkedList::reverse_list() {
    ConsoleColoring::blue("Reversing the list."); // Let's write down the example. The list is 4, 3, 2, 1.
    struct Node *previous, *current, *next;
    previous = nullptr;
    current = head; // The head is 4.
    while (current != nullptr) { // The key here is to make a swap.
        next = current->next_node;                                          // | next = 3      | next = 2      | next = 1      | next = nullptr
        current->next_node = previous;                                      // | 3 = 4         | 2 = 3         | 1 = 3         | nullptr = 2
        previous = current; // This one is useful for the last iteration.   // | previous = 4  | previous = 3  | previous = 2  | previous = 1
        current = next; // Until current is nullptr.                        // | 4 = 3         | 3 = 2         | 2 = 1         | 1 = nullptr     -> This will be the breaking condition.
    }
    head = previous; // Here is where to use that previous buffer Node.
}

struct Node *LinkedList::get_element(const unsigned short &index) {
    struct Node *current = head;
    int counter = 0;
    while (current != nullptr) {
        if (counter == index)
            return current;
        counter++;
        current = current->next_node;
    }
    ConsoleColoring::red("SIGABRT");
    assert(0);
}

struct Node *LinkedList::get_tail() {
    struct Node *current = head;
    while (current) {
        current = current->next_node;
        if (current->next_node == nullptr)
            return current;
    }
    ConsoleColoring::red("SIGABRT");
    assert(0);
}

void LinkedList::insert_at(struct Node *new_node, const unsigned short &index) { // 1, 2, 3, 4, nullptr
    struct Node *current = head;                                                 // c, n, 3, 4, nullptr
    struct Node *previous = nullptr;                                             // p, c, n, 4, nullptr
    int counter = 0;
    while (current) { // TODO -> WIP; First index and last index insertion.
        if (counter == index) {
            previous->next_node = new_node;
            new_node->next_node = current;
            break;
        }
        previous = current;
        current = current->next_node;
        counter++;
    }
    ConsoleColoring::blue("New element inserted.");
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
    cout << '\n';
    cout << "Added 4 new elements." << endl;

    for (short j = 1; j <= 4; ++j)
        lls.push(j);

    cout << "Head: " << lls.get_head()->data << endl;
    lls.print_horizontally();
    lls.reverse_list();
    lls.print_horizontally();
    cout << "Element at index 2: " << lls.get_element(2)->data << endl;
    cout << "Tail: " << lls.get_tail()->data << endl;

    // TODO -> WIP
    struct Node *n = new Node; // TODO -> Is this OK not to delete? Explain.
    n->data = 100;
    lls.insert_at(n, 4);
    lls.print_horizontally();
}
