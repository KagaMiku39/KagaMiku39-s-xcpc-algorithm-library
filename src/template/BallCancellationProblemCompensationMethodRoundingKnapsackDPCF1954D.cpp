#include <bits/stdc++.h>

using namespace std;

constexpr int mod = 998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int sum = 0;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
        sum += a[i];
    }

    vector<int> f(sum + 1);
    f[0] = 1;
    for (int i = 1; i <= n; i ++) {
        for (int j = sum; j >= a[i]; j --) {
            f[j] = (f[j] + f[j - a[i]]) % mod; 
        }
    }
    
    vector<vector<int>> g(n + 1, vector<int>(sum + 1));
    for (int i = 1; i <= n; i ++) {
        g[i][0] = 1;
        for (int j = 1; j <= sum; j ++) {
            if (j >= a[i]) {
                g[i][j] = (f[j] - g[i][j - a[i]]) % mod;
            } else {
                g[i][j] = f[j];
            }
        }
    }
    
    int ans = 0;
    for (int i = 1; i <= sum; i ++) {
        ans = (ans + 1ll * (i + 1) / 2 * f[i]) % mod; 
    }

    for (int i = 1; i <= n; i ++) {
        for (int j = 0; j < a[i]; j ++) {
            ans = (ans + 1ll * (a[i] - j) / 2 * g[i][j]) % mod;
        }
    }

    ans = (ans + mod) % mod;
    
    cout << ans << '\n';

    return 0;
}