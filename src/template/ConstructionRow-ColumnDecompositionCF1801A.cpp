#include <bits/stdc++.h>

using namespace std;

void solve() {   
    int n, m;
    cin >> n >> m;

    cout << n * m << '\n';
    
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < m; j ++) {
            cout << (i << 8 ^ j) << " \n"[j == m - 1];
        }
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