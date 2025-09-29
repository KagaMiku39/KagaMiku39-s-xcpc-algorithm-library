#include <bits/stdc++.h>

using namespace std;

constexpr int maxsz = 5001;

int mod;

int comb[maxsz][maxsz];

void solve() {
    int n;
    cin >> n;

    int sum = 0;
    vector<int> c(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> c[i];
        sum += c[i];
    }
    
    int ans = 1;
    for (int i = 1; i <= n; i ++) {
        ans = 1ll * ans * comb[sum][c[i]] % mod;
        sum -= c[i];
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; 
    cin >> t >> mod;

    for (int i = 0; i < maxsz; i ++) {
        comb[i][0] = 1 % mod;
    }
    
    comb[1][1] = 1 % mod;
    for (int i = 2; i < maxsz; i ++) {
        for (int j = 1; j <= i; j ++) {
            comb[i][j] = (1ll * comb[i - 1][j - 1] + comb[i - 1][j]) % mod;
        }
    }
    
    while (t --) {
        solve();
    }
    
    return 0;
}