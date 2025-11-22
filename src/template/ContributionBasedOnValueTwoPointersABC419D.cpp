#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

using i64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    i64 m;
    cin >> m;

    int c;
    cin >> c;

    vector<i64> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }

    sort(next(begin(a)), end(a));

    vector<pair<i64, int>> vec{{-1, -1}};
    for (int i = 1; i <= n; i ++) {
        auto &[val, cnt] = vec.back();
        if (val == a[i]) {
            cnt ++;
        } else {
            vec.emplace_back(a[i], 1);
        }
    }
    
    i64 ans = 0, pre = 0;
    for (int i = 1, j = 1; i < ssize(vec); i ++) {
        while (pre < c) {
            pre += vec[j].second;
            j = j % (ssize(vec) - 1) + 1;
        }
        if (i == 1) {
            ans += (m - vec.back().first + vec[1].first) * pre;
        } else {
            ans += (vec[i].first - vec[i - 1].first) * pre;
        }
        pre -= vec[i].second;
    }

    cout << ans << '\n';
    
    return 0;
}