#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n && n) {
        int d;
        vector<int> a;
        auto dfs = [&](auto &self, int u) -> bool {
            if (u > d) {
                return a[d] == n;
            }
            for (int i = u - 1; i; i --) {
                int t = a[u - 1] + a[i];
                if (t > n) {
                    continue;
                }
                a[u] = t;
                for (int j = u + 1; j <= d; j ++) {
                    t *= 2;
                }
                if (t < n) {
                    return false;
                }
                if (self(self, u + 1)) {
                    return true;
                }
            }
            return false;
        };
        for (d = 1; ; d ++) {
            a.assign(d + 1, 0);
            a[1] = 1;
            if (dfs(dfs, 2)) {
                break;
            }
        }
        for (int i = 1; i <= d; i ++) {
            cout << a[i] << " \n"[i == d];
        }
    }

    return 0;
}