#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using i128 = __int128;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    i64 a, b;
    cin >> a >> b;

    if (a > b) {
        swap(a, b);
    }

    i64 k = b - a;

    i128 lhs = (i128(2 * a) - k) * (i128(2 * a) - k), rhs = (i128(2 * a + 2) - k) * (i128(2 * a + 2) - k), mid = 5 * (i128)k * k;

    cout << (lhs <= mid && mid < rhs ? "0\n" : "1\n");
    
    return 0;
}
