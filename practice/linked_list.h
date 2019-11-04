#ifndef TMRG_LINKED_LIST_H
#define TMRG_LINKED_LIST_H

class LinkedList {
public:
    explicit LinkedList(struct Node *head, const char *linked_list_name) : head(head),
                                                                           linked_list_name(linked_list_name) {
        list_size = 0;
    };
    void push(const short &number);
    const void pop();
    void reverse_list();
    void print_vertically();
    void print_horizontally();
    static void activate_task();

    const char *get_linked_list_name() const {
        return linked_list_name;
    }

    int list_size;

    int get_list_size() const {
        return list_size;
    }

    Node *get_head() const {
        return head;
    }

private:
    struct Node *head;
    const char *linked_list_name;
    static int find_digits_length(short number);
    static void print_horizontal_lines(const short &digits_length);
};

struct Node {
    short data;
    struct Node *next_node;
};

#endif // TMRG_LINKED_LIST_H
