#include "include/line.h"
#include "include/point.h"


line::line(): 
    normal(1, 0),
    free(0)
{}

line::line(const point &a, const point &b):
    normal(+point(a, b)),
    free(-normal | a)
{}

double line::dist(const point &a) {
    return ((a | normal) + free) / normal.length();
}
