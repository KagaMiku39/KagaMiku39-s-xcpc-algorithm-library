#include <bits/stdc++.h>

using namespace std;

void solve() {   
    int n;
    cin >> n;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }

    int sum = 0;
    for (int i = 1; i <= n; i ++) {
        if (!a[i]) {
            cout << "NO\n";
            return;
        }
        sum += a[i];
    }

    cout << (sum >= 2 * n - 2 ? "YES\n" : "NO\n");
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