#include <bits/stdc++.h>

using namespace std;

template<typename T>
bool cmin(T &a, const T &b) {
    return a > b ? a = b, true : false;
}

constexpr int maxn = 5000 + 1;

int mat[maxn][maxn];

void solve() {
    int n; 
    cin >> n;
    
    int g = 0;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        g = gcd(g, a[i]);
    }

    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        cnt += a[i] == g;
    }

    if (cnt) {
        cout << n - cnt << '\n';
        return;
    }

    vector<int> dp(maxn, n - 1);
    dp[0] = -1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < maxn; j++) {
            cmin(dp[mat[a[i]][j]], dp[j] + 1);
        }
    }

    cout << dp[g] + n - 1 << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 0; i < maxn; i++) {
        for (int j = 0; j < maxn; j++) {
            mat[i][j] = gcd(i, j);
        }
    }

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
