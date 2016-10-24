#ifndef RAND_H
#define RAND_H

#include <cstdlib>


int get_rand(int a, int b) {
    if (b < a) {
        std::swap(a, b);
    }
    return rand() % (b - a) + a;
}

#endif // RAND_H
