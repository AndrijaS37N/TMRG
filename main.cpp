#include "tasks/min_period.h"
#include "tasks/min_period_alt.h"
#include "structures/linked_list.h"
#include <unistd.h>
#include <thread>

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

        // These are all the same max size.
        cout << numeric_limits<u_int64_t>::max() << endl;
        cout << numeric_limits<uint_least64_t>::max() << endl;
        cout << numeric_limits<unsigned long long int>::max() << endl;

        cout << endl;
        MinPeriod::activate_task();

        /*
         * Local, global, static variables short notes: http://faculty.cs.niu.edu/~freedman/241/241notes/241var2.htm.
         */

        LinkedList<double> lls(nullptr, "Linked List Structure");
        lls.activate_task();
        cout << endl;
    }

    MinPeriodAlt min_period_alt_task;
    min_period_alt_task.activate_task();

    // TODO -> Read more news about Concepts, a C++20 feature. Also, more on Modules, Ranges and Coroutine structures.

    return 0;
}