#include <bits/stdc++.h>

using namespace std;

constexpr int maxn = 101, maxsz = maxn * maxn * maxn;

bitset<maxsz> dp[maxn]; 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> a[i] >> b[i];
    }

    dp[0][0] = true;
    for (int i = 1; i <= n; i ++) {
        for (int j = a[i]; j <= b[i]; j ++) {
            dp[i] |= dp[i - 1] << (j * j);
        }
    }

    cout << dp[n].count() << '\n';
    
    return 0;
}