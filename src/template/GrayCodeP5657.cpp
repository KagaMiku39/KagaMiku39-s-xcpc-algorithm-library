#include <bits/stdc++.h>

using namespace std;

using u64 = unsigned long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    u64 k;
    cin >> k;

    k ^= k >> 1;

    while (n --) {
        cout << (k >> n & 1);
    }
    
    cout << '\n';

    // int n;
    // u64 g;
    // cin >> n >> g;

    // u64 b = g;
    // for (int i = 1; i < n; i ++) {
    //     b ^= g >> i;
    // }
    
    // while (n --) {
    //     cout << (b >> n & 1);
    // }
    
    // cout << '\n';

    return 0;
}