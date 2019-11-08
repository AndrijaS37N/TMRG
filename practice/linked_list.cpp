#include "../global/console_coloring.h"
#include "linked_list.h"
#include <iostream>
#include <string>

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
    struct Node *current = head;
    while (current) {
        cout << '\n';
        digits_length = find_digits_length(current->data);
        print_horizontal_lines(digits_length);
        cout << '\n';
        cout << "| " << current->data << " |";
        cout << '\n';
        print_horizontal_lines(digits_length);
        cout << '\n';
        cout << "  |";
        cout << '\n';
        cout << "  V";
        current = current->next_node;
    }
    cout << endl << "nullptr" << endl;
}

void LinkedList::print_horizontally() {
    cout << "Horizontal view: ";
    struct Node *current = head;
    while (current) {
        cout << "[ " << current->data << " ] -> ";
        current = current->next_node;
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
        head = head->next_node;
        list_size--;
        cout << "Element popped!" << endl;
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

void LinkedList::insert_at(struct Node *insert_node, const unsigned short &index) {
    struct Node *current = head;
    struct Node *previous = nullptr;
    int counter = 0;
    while (current) {
        if (counter == index) {
            if (previous == nullptr) { // For the first one.
                head = insert_node;
                insert_node->next_node = current;
                ConsoleColoring::blue("New element inserted.");
                return;
            } else { // For the ones in the middle.
                previous->next_node = insert_node;
                insert_node->next_node = current;
                ConsoleColoring::blue("New element inserted.");
                return;
            }
        }
        previous = current;
        current = current->next_node;
        counter++;
        if (counter == index && current == nullptr) { // For the last one.
            previous->next_node = insert_node;
            insert_node->next_node = current;
            ConsoleColoring::blue("New element inserted.");
            return;
        }
    }
    ConsoleColoring::red("New element not inserted.");
}

void LinkedList::replace_with(struct Node *replace_node, const unsigned short &index) {
    struct Node *current = head;
    struct Node *previous = nullptr;
    int counter = 0;
    while (current) {
        previous = current;
        current = current->next_node;
        if (counter == index) {
            previous->data = replace_node->data;
            replace_node->next_node = current;
            ConsoleColoring::blue("Element replaced.");
            return;
        }
        counter++;
    }
    ConsoleColoring::red("Element not replaced.");
}

LinkedList::~LinkedList() {
    struct Node *current = head;
    struct Node *previous = nullptr;
    int c = 0;
    while (current) {
        previous = current;
        current = current->next_node;
        delete previous;
        c++;
    }
    delete current; // This should at his point of execution be nullptr.
    ConsoleColoring::blue("Destructor finished deleting nodes.");
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

    // Failures.
    struct Node *insert_node = new Node;
    insert_node->data = 100;
    lls.insert_at(insert_node, lls.get_list_size() + 6);
    lls.print_horizontally();

    struct Node *replace_node = new Node;
    replace_node->data = -50;
    lls.replace_with(replace_node, 22);
    lls.print_horizontally();

    // Successes.
    insert_node->data = 100;
    lls.insert_at(insert_node, lls.get_list_size()); // Insert at the end. Queue in.
    lls.print_horizontally();

    replace_node->data = -50;
    lls.replace_with(replace_node, lls.get_list_size()); // Replace the last element.
    lls.print_horizontally();

}


