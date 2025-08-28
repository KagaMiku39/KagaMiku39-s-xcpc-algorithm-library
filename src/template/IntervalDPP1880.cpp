#include <bits/stdc++.h>

using namespace std;

template<typename T>
bool cmin(T &a, const T &b) {
    return a > b ? a = b, true : false;
}

template<typename T>
bool cmax(T &a, const T &b) {
    return a < b ? a = b, true : false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(2 * n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i + n] = a[i];
    }
    
    vector<int> pre(2 * n + 1);
    for (int i = 1; i <= 2 * n; i++) {
        pre[i] = pre[i - 1] + a[i];
    }
    
    vector<vector<int>> f(2 * n + 1, vector<int>(2 * n + 1, INT_MAX)), g(2 * n + 1, vector<int>(2 * n + 1));
    for (int i = 1; i <= 2 * n; i++) {
        f[i][i] = 0;
        g[i][i] = 0;
    }

    for (int len = 2; len <= n; len++) {
        for (int i = 1; i + len - 1 <= 2 * n; i++) {
            int j = i + len - 1, sum = pre[j] - pre[i - 1];
            for (int k = i; k < j; k++) {
                cmin(f[i][j], f[i][k] + f[k + 1][j] + sum);
                cmax(g[i][j], g[i][k] + g[k + 1][j] + sum);
            }
        }
    }

    int mi = INT_MAX, mx = 0;
    for (int i = 1; i <= n; i++) {
        cmin(mi, f[i][i + n - 1]);
        cmax(mx, g[i][i + n - 1]);
    }

    cout << mi << '\n' << mx << '\n';

    return 0;
}