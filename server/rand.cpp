#include "include/rand.h"

#include <cstdlib>
#include <utility>
int get_rand(int a, int b) {
    if (b < a) {
        std::swap(a, b);
    }
    if (b - a != 0) {
        return rand() % (b - a) + a;
    } else {
        return a;
    }
}
