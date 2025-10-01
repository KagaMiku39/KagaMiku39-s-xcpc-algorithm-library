#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n;
    cin >> n;

    cout << 3 + (n - 3) * 2 << '\n';
    cout << "1 2 " << n << '\n';
    cout << "2 1 " << n << '\n';
    cout << "3 1 " << n - 1 << '\n';
    for (int i = 4; i <= n; i ++) {
        cout << i << " 1 " << n - i + 2 << '\n';
        cout << i << ' ' << n - i + 3 << ' ' << n << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t --) {
        solve();
    }

    return 0;
}