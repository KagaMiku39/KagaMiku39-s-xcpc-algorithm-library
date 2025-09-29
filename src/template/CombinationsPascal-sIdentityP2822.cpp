#include <bits/stdc++.h>

using namespace std;

constexpr int maxn = 2e3 + 1, maxm = maxn;

int mod;

int comb[maxn][maxm], pre[maxn][maxm];

void solve() {
    int n, m;
    cin >> n >> m;
    
    cout << pre[n][min(n, m)] << '\n';   
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t >> mod;

    for (int i = 0; i < maxn; i ++) {
        comb[i][0] = 1 % mod;
    }
    
    comb[1][1] = 1 % mod;
    for (int i = 2; i < maxn; i ++) {
        for (int j = 1; j <= i; j ++) {
            comb[i][j] = (1ll * comb[i - 1][j - 1] + comb[i - 1][j]) % mod;
        }
    }

    pre[0][0] = !comb[0][0];
    for (int i = 1; i < maxn; i ++) {
        pre[i][0] = !comb[i][0] + pre[i - 1][0];
    }
    
    for (int i = 1; i < maxn; i ++) {
        for (int j = 1; j <= i; j ++) {
            pre[i][j] = !comb[i][j] + pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1];
        }
        pre[i][i] += pre[i - 1][i - 1];
    }

    while (t --) {
        solve();
    }
    
    return 0;
}