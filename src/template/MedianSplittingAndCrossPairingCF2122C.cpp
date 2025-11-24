#include <bits/stdc++.h>

using namespace std;

void solve() {   
    int n;
    cin >> n;

    vector<int> x(n + 1), y(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> x[i] >> y[i];
    }

    vector<int> id(n + 1);

    iota(begin(id), end(id), 0);

    sort(next(begin(id)), end(id), [&](const int &a, const int &b) {
        return x[a] < x[b];
    });

    sort(next(begin(id)), next(begin(id), n / 2 + 1), [&](const int &a, const int &b) {
        return y[a] < y[b];
    });

    sort(next(begin(id), n / 2 + 1), end(id), [&](const int &a, const int &b) {
        return y[a] < y[b];
    });

    for (int i = 1; i <= n / 2; i ++) {
        int j = id[i], k = id[n - i + 1];
        cout << j << ' ' << k << '\n';
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