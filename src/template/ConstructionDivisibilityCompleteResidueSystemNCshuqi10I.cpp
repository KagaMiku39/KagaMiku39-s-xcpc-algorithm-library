#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    if (gcd(n, m) != 1) {
        cout << "NO\n";
        return 0;
    }

    cout << "YES\n";    

    int r = 0, c = 0, tagr = 1;
    vector<vector<i64>> ans(n, vector<i64>(m));
    for (int i = 0; i < n; i ++) {
        int tagc = 1;
        for (int j = 0; j < m; j ++) {
            i64 k = 1ll * i * m + j + 1;
            ans[r][c] = k;
            c = ((c + k * tagc) % m + m) % m;
            tagc *= -1;
        }
        r = ((r + tagr * (i + 1ll) * m) % n + n) % n;
        tagr *= -1;
    }

    for (auto &i: ans) {
        for (i64 &j: i) {
            cout << j << " \n"[j == i.back()];
        }
    }
    
    return 0;
}