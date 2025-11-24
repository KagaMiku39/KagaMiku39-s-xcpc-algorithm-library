#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

constexpr int mod = 1e9 + 7;

void solve() {   
    i64 n;
    cin >> n;

    n %= mod;

    int k;
    cin >> k;

    if (k == 1) {
        cout << n << '\n'; 
        return;
    }
    
    int pos = 0;
    vector<int> f(6 * k + 1);
    f[1] = 1 % k;
    f[2] = 1 % k;
    for (int i = 3; i <= 6 * k; i ++) {
        f[i] = (f[i - 1] + f[i - 2]) % k;
        if (!f[i]) {
            if (pos) {
                cout << (pos + (i - pos) * (n - 1) % mod) % mod << '\n';
                return; 
            } else {
                pos = i;
            }      
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