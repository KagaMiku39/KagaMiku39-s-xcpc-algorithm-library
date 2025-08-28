#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    i64 a, b, mod;
    cin >> a >> b >> mod;

    auto slowmul = [&](i64 a, i64 b) {
        i64 res = 0;
        while (b) {
            if (b & 1) {
                res = (res + a) % mod;
            }
            a = (a + a) % mod;
            b /= 2;
        }
        return res;
    };

    cout << slowmul(a, b) << '\n';
    
    return 0;
}