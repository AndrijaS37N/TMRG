#include "practice/min_period.h"
#include "practice/linked_list.h"
#include <thread>
#include <unistd.h>

#define TASK_SWITCH 0

using namespace std;

/*
  Using std namespace for faster practising.
  Neglect the call_from_thread function or the first couple of lines in main().
*/

struct Alpha {
    const char *alpha_name;
};

struct Beta {
    const char *beta_name;
};

struct Gamma {
    const char *gamma_name;
};

void call_from_thread() {
    struct Alpha alpha{};
    struct Beta beta{};
    struct Gamma gamma{};
    alpha.alpha_name = "Alpha";
    beta.beta_name = "Beta";
    gamma.gamma_name = "Gamma";
    std::cout << alpha.alpha_name << '\n';
    std::cout << beta.beta_name << '\n';
    std::cout << gamma.gamma_name << '\n';
}

int main() {
    if (TASK_SWITCH) {
        cout << endl;
        std::thread angles(call_from_thread);
        angles.join();
        usleep(1000 * 1000);

        /*
         * Minimal period in a integer array task.
        */

        cout << endl;
        MinPeriod::activate_task();

        /*
         * Linked list custom structure made.
        */
    }

    cout << endl;
    LinkedList::activate_task();

    // TODO -> 👨‍🚀

    return 0;
}