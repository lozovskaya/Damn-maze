#ifndef POINT_H
#define POINT_H

#include <cmath>

struct point {
    double x, y;
    point():
        x(0),
        y(0)
        {}
    point(int x_, int y_):
        x(x_),
        y(y_)
        {}
    point(point begin, point end):
        x(end.x - begin.x),
        y(end.y - begin.y)
        {}

    double length() const;

    double sqlength() const;

    point operator - () const;
    point operator + () const;

    point operator + (const point &other) const;
    point operator - (const point &other) const;
    point operator * (const double &other) const;

    point operator / (const double &other) const;

    point &operator += (const point &other);

    point &operator -= (const point &other);

    point &operator *= (const double &other);

    point &operator /= (const double &other);

    double operator | (const point &other) const;
    
    double operator & (const point &other) const;
};

point rotate(const point &a, const point& center, double angle);

double distance(const point &a, const point &b);

typedef point vect;

#endif // POINT_H
