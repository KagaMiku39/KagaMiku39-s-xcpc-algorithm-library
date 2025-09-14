#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

void solve() {   
    int a, b;
    cin >> a >> b;

    if (a < b) {
        swap(a, b);
    }
    
    i64 val = 1ll * a * a - 1ll * b * b;

    cout << (val - 1) / 2 + max(val / 4 - 1, 0ll) << '\n';
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