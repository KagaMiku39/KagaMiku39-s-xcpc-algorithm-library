#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

using i128 = __int128;

ostream& operator << (ostream &os, i128 x) {
    if (x < 0) {
        os << '-';
        x = -x;
    }
    if (x > 9) {
        os << i128(x / 10);
    }
    os << (char)('0' + (x % 10));
    return os;
}

istream& operator >> (istream &is, i128 &x) {
    string s;
    is >> s;
    x = 0;
    for (char &ch: s) {
        if (isdigit(ch)) {
            x = x * 10 + (ch - '0');
        }
    }
    if (s[0] == '-') {
        x = -x;
    }
    return is;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    
    return 0;
}