#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    i64 n, k;
    while (cin >> n >> k) {
        if (!n && !k) {
            break;
        }
        cout << ((n - 1) % (k + 1) ? "Tang\n" : "Jiang\n");
    }

    return 0;
}