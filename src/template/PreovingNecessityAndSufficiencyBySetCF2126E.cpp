#include <bits/stdc++.h>

using namespace std;

void solve() {   
    int n;
    cin >> n;

    vector<int> p(n + 1), s(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> p[i];
    }
    for (int i = 1; i <= n; i ++) {
        cin >> s[i];
    }

    for (int i = 1; i < n; i ++) {
        if (p[i] < p[i + 1] || p[i] % p[i + 1]) {
            cout << "No\n";
            return;
        }
    }
    
    for (int i = 1; i < n; i ++) {
        if (s[i] > s[i + 1] || s[i + 1] % s[i]) {
            cout << "No\n";
            return;
        }
    }

    if (s[1] != p[n]) {
        cout << "No\n";
        return;
    }

    for (int i = 1; i < n; i ++) {
        if (gcd(p[i], s[i + 1]) != p[n]) {
            cout << "No\n";
            return;
        }
    }

    cout << "Yes\n";
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