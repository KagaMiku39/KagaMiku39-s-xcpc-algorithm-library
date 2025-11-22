#include <bits/stdc++.h>

using namespace std;

constexpr int mod = 2, maxn = 1e6 + 1;

int v2[maxn];

void solve() {
    int n, k;
    cin >> n >> k;
    
    for (int i = 0; i < n; i ++) {
        // cout << (((n - 1) & i) == i ? k : 0) << " \n"[i == n - 1];
        cout << (v2[n - 1] - v2[i] - v2[n - 1 - i] ? 0 : k) << " \n"[i == n - 1];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;

    for (int i = 0; i < maxn; i ++) {
        int j = 2;
        while (i / j) {
            v2[i] += i / j;
            j *= 2;
        }
        // v2[i] = i - bitset<27>{u32(i)}.count();
    }

    // for (int i = 1; i < maxn; i ++) {
    //     v2[i] = v2[i - 1]; 
    //     int j = i;
    //     while (j && j % 2 == 0) {
    //         v2[i] ++;
    //         j /= 2;
    //     }
    // }

    while (t --) {
        solve();
    }

    return 0;
}