#include "include/point.h"
#include <cmath>

double point::length() const {
    return sqrt(x * x + y * y);
}

double point::sqlength() const {
    return x * x + y * y;
}

point point::operator + () const {
    return point(-y, x);
}

point point::operator - () const {
    return point(-x, -y);
}

point point::operator + (const point &other) const {
    return point(x + other.x, y + other.y);
}
point point::operator - (const point &other) const {
    return point(x - other.x, y - other.y);
}
point point::operator * (const double &other) const {
    return point(x * other, y * other);
}

point point::operator / (const double &other) const {
    return point(x / other, y / other);
}

point &point::operator += (const point &other) {
    return *this = *this + other;
}

point &point::operator -= (const point &other) {
    return *this = *this - other;
}

point &point::operator *= (const double &other) {
    return *this = *this * other;
}

point &point::operator /= (const double &other) {
    return *this = *this / other;
}

double point::operator | (const point &other) const {
    return x * other.x + y * other.y;
}

double point::operator & (const point &other) const {
    return x * other.y - y * other.x;
}

point rotate(const point &a, const point& center, double angle) {
    point vec(center, a);
    double sin = sinf(angle);
    double cos = cosf(angle);
    vec.x = vec.x * cos + vec.y * sin;
    vec.y = vec.x * -sin + vec.y * cos;
    return vec;
}

double distance(const point &a, const point &b) {
    return point(a, b).length();
}

