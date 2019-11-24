#ifndef TMRG_LINKED_LIST_H
#define TMRG_LINKED_LIST_H

#include "../global/console_coloring.h"
#include "../math/operation.h"
#include "linked_list.h"
#include <iostream>
#include <sstream>
#include <string>

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

    ~LinkedList();
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
    void merge_sort(struct Node<T> **head_references);
    void clear_list();
    bool is_empty();
    void activate_task();

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
    static constexpr u_int64_t find_element_length(const string &s); // Overloaded.
    static inline u_int64_t stringify_double(double &data);
    static constexpr void print_width(const u_int64_t &data_length);
    constexpr void print_search_result(u_int64_t *result_indices, const u_int64_t &indices_count);
    struct Node<T> *merge(struct Node<T> *alpha, struct Node<T> *beta);
    void split(struct Node<T> *source, struct Node<T> **front_reference, struct Node<T> **back_reference);
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
constexpr u_int64_t LinkedList<T>::find_element_length(const string &s) {
    ConsoleColoring::yellow('S'); // Printing as.
    return s.length() + 2;
}

template<typename T>
inline u_int64_t LinkedList<T>::stringify_double(double &data) {
    ConsoleColoring::yellow('D'); // Printing as.
    ostringstream convert;
    convert << data;
    return convert.str().length() + 2;
}

template<typename T>
constexpr void LinkedList<T>::print_width(const u_int64_t &data_length) {
    cout << ' ';
    for (int i = 0; i < data_length; ++i)
        cout << '-';
}

template<typename T>
void LinkedList<T>::push(const T &data) {
    struct Node<T> *new_node;
    try {
        new_node = new Node<T>;
        if (new_node == nullptr) // Memory allocation issues?
            throw;
        new_node->data = data;
        new_node->next_node = head;
        head = new_node;
        list_size++;
    } catch (...) {
        ConsoleColoring::red("Memory allocation failed? New node not pushed into the list.");
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
    current = head; // The head is 4.                                       Sketch for the example:
    while (current !=
           nullptr) { // The key here is to make a swap.         //  ----------------------------------------------------------------
        next = current->next_node;                                          // | next = 3      | next = 2      | next = 1      | next = nullptr |
        current->next_node = previous;                                      // | 3 = 4         | 2 = 3         | 1 = 3         | nullptr = 2    |
        previous = current; // This one is useful for the last iteration.   // | previous = 4  | previous = 3  | previous = 2  | previous = 1   |
        current = next; // Until current is nullptr.                        // | 4 = 3         | 3 = 2         | 2 = 1         | 1 = nullptr    | -> This will be the breaking condition.
    }                                                                       //  ----------------------------------------------------------------
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
                list_size++;
                return;
            } else { // For the ones in the middle.
                previous->next_node = insert_node;
                insert_node->next_node = current;
                ConsoleColoring::blue("New element inserted.");
                list_size++;
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
            list_size++;
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
struct Node<T> *LinkedList<T>::merge(Node<T> *alpha, Node<T> *beta) {
    struct Node<T> *result = nullptr;
    if (alpha == nullptr)
        return beta;
    else if (beta == nullptr)
        return alpha;
    if (alpha->data <= beta->data) {
        result = alpha;
        result->next_node = merge(alpha->next_node, beta);
    } else {
        result = beta;
        result->next_node = merge(alpha, beta->next_node);
    }
    return result;
}

template<typename T>
void LinkedList<T>::split(Node<T> *source, Node<T> **low_index, Node<T> **high_index) {
    struct Node<T> *fast;
    struct Node<T> *slow;
    slow = source;
    fast = source->next_node;
    // Jump two times for the fast one, and one time for the slow one. The slow one will roughly be in the middle of the list.
    while (fast != nullptr) {
        fast = fast->next_node;
        if (fast != nullptr) {
            slow = slow->next_node;
            fast = fast->next_node;
        }
    }
    *low_index = source;
    *high_index = slow->next_node;
    slow->next_node = nullptr;
}

template<typename T>
void LinkedList<T>::merge_sort(struct Node<T> **head_reference) {
    struct Node<T> *head_tmp = *head_reference;
    struct Node<T> *alpha;
    struct Node<T> *beta;
    if ((head_tmp == nullptr) || (head_tmp->next_node == nullptr))
        return;
    split(head_tmp, &alpha, &beta);
    // Recursive sort of the two branches.
    merge_sort(&alpha);
    merge_sort(&beta);
    // Merge the two sorted branches (lists) together.
    *head_reference = merge(alpha, beta);
}

template<typename T>
void LinkedList<T>::clear_list() {
    ConsoleColoring::yellow("Clearing the list.");
    const atomic_uint64_t list_size_variable = list_size; // No need to use the getter here.
    for (int i = 0; i < list_size_variable; ++i)
        pop();
}

template<typename T>
bool LinkedList<T>::is_empty() {
    return list_size == 0 && head == nullptr;
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
    ConsoleColoring::cyan(get_linked_list_name());
    cout << "Size: " << get_size_type() << ' ' << "(u_int64_t)" << endl;
    cout << "Of type: " << get_data_type() << endl;
    push(14.202);
    push(-43);
    push(32767);
    push('a');
    push(000);
    push(-1.121);
    push('s');
    push(2);
    push(numeric_limits<double>::min());
    push(numeric_limits<double>::max());
    extern const atomic_int64_t number_printing_edge; // 👈 This. Explanation: https://stackoverflow.com/questions/10422034/when-to-use-extern-in-c.
    push(number_printing_edge); // External value defined in math/operation.h file.

    // For string types push inputs must be changed in the activate_task function. 👇
    // LinkedList<string>::activate_task();

    cout << '\n';
    print_vertically();
    cout << '\n';
    print_horizontally();
    cout << "Size: " << get_list_size() << endl;

    const atomic_uint64_t list_size_variable = get_list_size();
    for (int i = 0; i < list_size_variable + 4; ++i)
        pop();

    print_horizontally();
    print_vertically();
    cout << "Size: " << get_list_size() << endl;
    cout << '\n';
    cout << "Added 4 new elements." << endl;

    for (short j = 1; j <= 4; ++j)
        push(j);

    cout << "Head: " << get_head()->data << endl;
    print_horizontally();
    reverse_list();
    print_horizontally();
    cout << "Element at index 2: " << get_element(2)->data << endl;
    cout << "Tail: " << get_tail()->data << endl;

    // Failures.
    struct Node<T> *insert_node = new Node<T>;
    insert_node->data = 100;
    insert_at(insert_node, get_list_size() + 6);
    print_horizontally();

    struct Node<T> *replace_node = new Node<T>;
    replace_node->data = -50;
    replace_with(replace_node, 22);
    print_horizontally();

    // Successes.
    insert_node->data = 100;
    insert_at(insert_node, get_list_size()); // Insert at the end. Queue in.
    print_horizontally();

    replace_node->data = -50;
    replace_with(replace_node, get_list_size() - 1); // Replace the last element.
    print_horizontally();

    // Search element 2 and find the indices of element 2 in the list.
    for (short j = 1; j <= 3; ++j)
        push(2);

    cout << "Size: " << get_list_size() << endl;

    print_horizontally();
    search_elements(2);
    search_elements(-50);

    cout << '\n';

    push(111);
    print_horizontally();
    ConsoleColoring::blue("Merge sort started.");
    merge_sort(&head);
    print_horizontally();
    cout << "Size: " << get_list_size() << endl;

    cout << '\n';

    clear_list();
    print_horizontally();
    cout << "Is the list empty: " << is_empty() << endl;

    cout << '\n';

    push(2);
    push(3);
    push(1);
    push(7);
    print_horizontally();
    ConsoleColoring::blue("Merge sort started.");
    merge_sort(&head);
    print_horizontally();

    cout << '\n';
}

#endif // TMRG_LINKED_LIST_H
