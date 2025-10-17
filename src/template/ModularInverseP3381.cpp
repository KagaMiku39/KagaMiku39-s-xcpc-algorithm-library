#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, mod;
    cin >> n >> mod;

    vector<int> inv(n + 1);
    inv[1] = 1;
    for (int i = 2; i <= n; i ++) {
        inv[i] = (-i64(mod / i) * inv[mod % i] % mod + mod) % mod;
    }

    for (int i = 1; i <= n; i ++) {
        cout << inv[i] << '\n';
    }

    // for (int i = 1; i <= n; i ++) {
    //     int x = 0, y = 0;
    //     auto exgcd = [&](int a, int b, int &x, int &y) {
    //         int xx = 0, yy = 1;
    //         x = 1, y = 0;
    //         while (b) {
    //             int q = a / b;
    //             tie(a, b) = make_tuple(b, a % b);
    //             tie(x, xx) = make_tuple(xx, x - q * xx);
    //             tie(y, yy) = make_tuple(yy, y - q * yy);
    //         }
    //         return a;
    //     };
    //     exgcd(i, mod, x, y);
    //     x = (x + mod) % mod;
    //     cout << x << '\n';  
    // }

    return 0;
}