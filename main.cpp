#include "practice/min_period.h"
#include <thread>
#include <unistd.h>

using namespace std; // Using std namespace for faster practising.

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
    // Neglect this part for now.
    std::thread angles(call_from_thread);
    angles.join();
    usleep(1000 * 1000);
    cout << endl;

    /*
    * Minimal period in a integer array task.
    */

    MinPeriod::activate_task();

    /*
    * Trees - WIP.
    */

    return 0;
}