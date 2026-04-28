#include <bits/stdc++.h>

using namespace std;

constexpr int maxn = 44 + 1;

int f[maxn];

void solve() {   
    int n, x, y;
    cin >> n >> x >> y;

    auto dfs = [&](auto &self) -> bool {
        if (n == 1) {
            return true;
        }
        if (y > f[n - 1] && y < f[n] + 1) {
            return false;
        }
        tie(x, y) = make_tuple(y - f[n] * (y > f[n]), x);
        n --;
        return self(self);
    };

    cout << (dfs(dfs) ? "Yes\n" : "No\n");
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    f[0] = 1;
    f[1] = 1;
    for (int i = 2; i < maxn; i ++) {
        f[i] = f[i - 1] + f[i - 2];
    }

    int t;
    cin >> t;

    while (t --) {
        solve();
    }

    return 0;
}