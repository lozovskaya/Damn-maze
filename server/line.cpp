#include "include/line.h"
#include "include/point.h"


segment::segment():
    begin(0, 0),
    end(0, 0),
    len(0)
{}

segment::segment(const point &a, const point &b):
    begin(a),
    end(b),
    len(distance(a, b))
{}

point segment::vec() const {
    return end - begin;
}

bool segment::operator & (const segment &other) const
{
    return ((begin - other.begin) & other.vec()) * ((end - other.begin)  & other.vec()) <= 0
        && ((other.begin - begin) & vec()) * ((other.end - begin)  & vec()) <= 0;
}


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
