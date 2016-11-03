#ifndef LINE_H
#define LINE_H
#include "point.h"

class line {
    point normal;
    double free;

  public:
    line();
    line(const point &a, const point &b);
    double dist(const point &a);

};
#endif // LINE_H
