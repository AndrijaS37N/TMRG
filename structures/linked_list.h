#ifndef TMRG_LINKED_LIST_H
#define TMRG_LINKED_LIST_H

#include "../global/console_coloring.h"
#include "../math/operation.h"
#include "linked_list.h"
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>

using namespace std;

template<typename T>
struct Node {
    T data;
    struct Node *next_node;
};

template<typename T>
class LinkedList {
public:
    explicit LinkedList(struct Node<T> *head, const char *linked_list_name) : head(head),
                                                                              linked_list_name(linked_list_name) {
        list_size = 0;
        size_type = typeid(u_int64_t).name();
        data_type = typeid(T).name();
    }

    void push(const T &data);
    const void pop();
    void reverse_list();
    constexpr void print_vertically();
    constexpr void print_horizontally() const;
    constexpr struct Node<T> *get_element(const u_int64_t &index) const;
    constexpr struct Node<T> *get_tail() const;
    void insert_at(struct Node<T> *insert_node, const u_int64_t &index);
    void replace_with(struct Node<T> *replace_node, const u_int64_t &index);
    void search_elements(const T data);
    static void activate_task();

    constexpr const char *get_linked_list_name() const {
        return linked_list_name;
    }

    constexpr u_int64_t get_list_size() const {
        return list_size;
    }

    constexpr struct Node<T> *get_head() const {
        return head;
    }

    constexpr const char *get_size_type() const {
        return size_type;
    }

    constexpr const char *get_data_type() const {
        return data_type;
    }

private:
    const char *data_type;
    const char *size_type;
    u_int64_t list_size;
    struct Node<T> *head;
    const char *linked_list_name;
    inline u_int64_t find_element_length(double data);
    static inline u_int64_t stringify_double(double &data);
    static constexpr u_int64_t find_element_length(const string &s); // Overloaded.
    static constexpr void print_width(const u_int64_t &data_length);
    constexpr void print_search_result(u_int64_t *result_indices, const u_int64_t &indices_count);
    ~LinkedList();
};

template<typename T>
constexpr void LinkedList<T>::print_vertically() {
    cout << "Vertical view:";
    u_int64_t element_length = 0;
    struct Node<T> *current = head;
    while (current) {
        cout << '\n';
        element_length = find_element_length(current->data);
        print_width(element_length);
        cout << '\n';
        cout << "| " << current->data << " |";
        cout << '\n';
        print_width(element_length);
        cout << '\n';
        cout << "  |";
        cout << '\n';
        cout << "  V";
        current = current->next_node;
    }
    cout << endl << "nullptr" << endl;
}

template<typename T>
constexpr void LinkedList<T>::print_horizontally() const {
    cout << "Horizontal view: ";
    struct Node<T> *current = head;
    while (current) {
        cout << "[ " << current->data << " ] -> ";
        current = current->next_node;
    }
    cout << "nullptr" << endl;
}

template<typename T>
inline u_int64_t LinkedList<T>::find_element_length(double number) {
    if (!Operation::check_integer(number)) // If this is a floating point number or a somewhat big number.
        return stringify_double(number);
    if (*data_type == 'c')
        return 3;
    ConsoleColoring::yellow('I'); // Printing as.
    int64_t integer = (int64_t) number;
    u_int64_t length;
    if (integer > 0) {
        for (length = 0; integer > 0; length++)
            integer = integer / 10;
        length += 2;
    } else {
        integer = Operation::abs(integer);
        for (length = 0; integer > 0; length++)
            integer = integer / 10;
        length += 3;
    }
    return length;
}

template<typename T>
inline u_int64_t LinkedList<T>::stringify_double(double &data) {
    ConsoleColoring::yellow('D'); // Printing as.
    ostringstream convert;
    convert << data;
    return convert.str().length() + 2;
}

template<typename T>
constexpr u_int64_t LinkedList<T>::find_element_length(const string &s) {
    ConsoleColoring::yellow('S'); // Printing as.
    return s.length() + 2;
}

template<typename T>
constexpr void LinkedList<T>::print_width(const u_int64_t &data_length) {
    cout << ' ';
    for (int i = 0; i < data_length; ++i)
        cout << '-';
}

template<typename T>
void LinkedList<T>::push(const T &data) {
    struct Node<T> *new_node = new Node<T>;
    if (new_node == nullptr) // Always false?
        ConsoleColoring::red("Memory allocation failed.");
    else {
        new_node->data = data;
        new_node->next_node = head;
        head = new_node;
        list_size++;
    }
}

template<typename T>
const void LinkedList<T>::pop() {
    if (head == nullptr)
        ConsoleColoring::yellow("Element not popped! Linked list has been emptied.");
    else {
        head = head->next_node;
        list_size--;
        cout << "Element popped!" << endl;
    }
}

template<typename T>
void LinkedList<T>::reverse_list() {
    ConsoleColoring::blue("Reversing the list."); // Let's write down the example. The list is 4, 3, 2, 1.
    struct Node<T> *previous, *current, *next;
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

template<typename T>
constexpr struct Node<T> *LinkedList<T>::get_element(const u_int64_t &index) const {
    struct Node<T> *current = head;
    u_int64_t counter = 0;
    while (current != nullptr) {
        if (counter == index)
            return current;
        counter++;
        current = current->next_node;
    }
    ConsoleColoring::red("SIGABRT");
    assert(0);
}

template<typename T>
constexpr struct Node<T> *LinkedList<T>::get_tail() const {
    struct Node<T> *current = head;
    while (current) {
        current = current->next_node;
        if (current->next_node == nullptr)
            return current;
    }
    ConsoleColoring::red("SIGABRT");
    assert(0);
}

template<typename T>
void LinkedList<T>::insert_at(struct Node<T> *insert_node, const u_int64_t &index) {
    struct Node<T> *current = head;
    struct Node<T> *previous = nullptr;
    u_int64_t counter = 0;
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

template<typename T>
void LinkedList<T>::replace_with(struct Node<T> *replace_node, const u_int64_t &index) {
    struct Node<T> *current = head;
    struct Node<T> *previous = nullptr;
    u_int64_t counter = 0;
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

template<typename T>
void LinkedList<T>::search_elements(const T data) {
    ConsoleColoring::blue("Searching for the element.");
    ConsoleColoring::yellow(data);
    struct Node<T> *current = head;
    u_int64_t indices_count = 0;
    u_int64_t counter = 0;
    u_int64_t *result_indices = (u_int64_t *) malloc(sizeof(data));
    while (current) {
        if (current->data == data) {
            result_indices = (u_int64_t *) realloc(result_indices, sizeof(data) * indices_count);
            result_indices[indices_count] = counter;
            indices_count++;
        }
        current = current->next_node;
        counter++;
    }
    print_search_result(result_indices, indices_count);
    free(result_indices);
}

template<typename T>
constexpr void LinkedList<T>::print_search_result(u_int64_t *result_indices, const u_int64_t &indices_count) {
    cout << "Search result indices: ";
    for (auto i = 0; i < indices_count; ++i)
        cout << result_indices[i] << ' ';

    cout << '\n';
}

template<typename T>
LinkedList<T>::~LinkedList() {
    struct Node<T> *current = head;
    struct Node<T> *previous = nullptr;
    while (current) {
        previous = current;
        current = current->next_node;
        delete previous;
    }
    delete current; // This should at this point of execution be nullptr.
    ConsoleColoring::blue("Destructor finished deleting nodes.");
    cout << '\n';
}

template<typename T>
void LinkedList<T>::activate_task() {
    LinkedList lls(nullptr, "Linked List Structure");
    ConsoleColoring::cyan(lls.get_linked_list_name());
    cout << "Size: " << lls.get_size_type() << ' ' << "(u_int64_t)" << endl;
    cout << "Of type: " << lls.get_data_type() << endl;
    lls.push(14.202);
    lls.push(-43);
    lls.push(32767);
    lls.push('a');
    lls.push(000);
    lls.push(-1.121);
    lls.push('s');
    lls.push(2);
    lls.push(numeric_limits<double>::min());
    lls.push(numeric_limits<double>::max());
    lls.push(number_printing_edge); // External value defined in math/operation.h file.

    // For string types push inputs must be changed in the activate_task function. 👇
    // LinkedList<string>::activate_task();

    cout << '\n';
    lls.print_vertically();
    cout << '\n';
    lls.print_horizontally();
    cout << "Size: " << lls.get_list_size() << endl;

    const atomic_uint64_t list_size_variable = lls.get_list_size();
    for (int i = 0; i < list_size_variable + 4; ++i)
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
    struct Node<T> *insert_node = new Node<T>;
    insert_node->data = 100;
    lls.insert_at(insert_node, lls.get_list_size() + 6);
    lls.print_horizontally();

    struct Node<T> *replace_node = new Node<T>;
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

    // Search element 2 and find the indices of element 2 in the list.
    for (short j = 1; j <= 3; ++j)
        lls.push(2);

    lls.print_horizontally();
    lls.search_elements(2);
    lls.search_elements(-50);

    cout << '\n';
}

#endif // TMRG_LINKED_LIST_H
