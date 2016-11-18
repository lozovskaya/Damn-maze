#include "include/line.h"
#include "include/point.h"


segment::segment():
    begin(0, 0),
    end(0, 0)
{}

segment::segment(const point &a, const point &b):
    begin(a),
    end(b)
{}

vector segment::vec() const {
    return end - begin;
}

bool segment::operator & (const segment &other) const {
    return (vector(other.begin, begin) & other.vec()) * (vector(other.begin, end)  & other.vec()) <= 0
        && (vector(begin, other.begin) & vec()) * (vector(begin, other.end)  & vec()) <= 0;
}

double segment::len() const {
    return distance(begin, end);
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
