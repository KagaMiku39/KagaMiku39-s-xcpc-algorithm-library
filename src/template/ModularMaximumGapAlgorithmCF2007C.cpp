#include <bits/stdc++.h>

using namespace std;

template<typename T>
bool cmax(T &a, const T &b) {
    return a < b ? a = b, true : false;
}

void solve() {   
    int n, a, b;
    cin >> n >> a >> b;

    int g = gcd(a, b);
    vector<int> c(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> c[i];
        c[i] %= g;
    }

    sort(next(begin(c)), end(c));
    

    int mx = 0;
    for (int i = 1; i < n; i ++) {
        cmax(mx, c[i + 1] - c[i]);
    }
    cmax(mx, c[1] + g - c[n]);

    cout << g - mx << '\n';
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