#include <bits/stdc++.h>

using namespace std;

template<typename T>
bool cmin(T &a, const T &b) {
    return a > b ? a = b, true : false;
}

void solve() {
    int n, m;
    cin >> n >> m;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }

    vector<int> b(m + 1);
    for (int i = 1; i <= m; i ++) {
        cin >> b[i];
    }

    vector<int> pre(n + 1);
    for (int i = 1, j = 1; i <= n; i ++) {
        pre[i] = pre[i - 1];
        if (j <= m && a[i] >= b[j]) {
            pre[i] ++;
            j ++;
        }
    }

    vector<int> suf(n + 2);
    for (int i = n, j = m; i; i --) {
        suf[i] = suf[i + 1];
        if (j >= 1 && a[i] >= b[j]) {
            suf[i] ++;
            j --;
        }
    }
    
    if (pre[n] == m) {
        cout << "0\n";
        return;
    }

    int ans = INT_MAX;
    for (int i = 1; i <= n + 1; i ++) {
        if (pre[i - 1] + suf[i] == m - 1) {
            cmin(ans, b[pre[i - 1] + 1]);
        }
    }

    cout << (ans == INT_MAX ? -1 : ans) << '\n';
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