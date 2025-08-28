#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    i64 n;
    cin >> n;

    while (n) {
        if (n == 1) {
            cout << "1\n";
            return 0;
        }
        if (n == 2) {
            cout << "2\n";
            return 0;
        }
        i64 a = 1, b = 2, c = 3;
        while (c < n) {
            a = b;
            b = c;
            c = a + b;
        }
        if (c == n) {
            cout << n << '\n';
            return 0;
        }
        n -= b;
    }

    return 0;
}