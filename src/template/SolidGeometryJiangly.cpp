#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

using Real = double;

struct Point {
    Real x = 0;
    Real y = 0;
    Real z = 0;
};

Point operator+(const Point &a, const Point &b) {
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}

Point operator-(const Point &a, const Point &b) {
    return {a.x - b.x, a.y - b.y, a.z - b.z};
}

Point operator*(const Point &a, Real b) {
    return {a.x * b, a.y * b, a.z * b};
}

Point operator/(const Point &a, Real b) {
    return {a.x / b, a.y / b, a.z / b};
}

Real length(const Point &a) {
    return std::hypot(a.x, a.y, a.z);
}

Point normalize(const Point &a) {
    Real l = length(a);
    return {a.x / l, a.y / l, a.z / l};
}

Real getAng(Real a, Real b, Real c) {
    return std::acos((a * a + b * b - c * c) / 2 / a / b);
}

std::ostream &operator<<(std::ostream &os, const Point &a) {
    return os << "(" << a.x << ", " << a.y << ", " << a.z << ")";
}

Real dot(const Point &a, const Point &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Point cross(const Point &a, const Point &b) {
    return {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    
    
    return 0;
}