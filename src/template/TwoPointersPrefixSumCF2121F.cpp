#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

void solve() {   
    int n;
    cin >> n;

    i64 s;
    cin >> s;

    int x;
    cin >> x;

    vector<i64> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }

    i64 ans = 0;
    vector<i64> pre = a;
    map<i64, i64> mp;
    deque<int> dq;
    for (int i = 1, j = 0; i <= n; i ++) {
        while (ssize(dq) && a[i] > dq.back()) {
            dq.pop_back();
        }
        if (a[i] > x) {
            pre[i] = 0;
            j = i;
            mp.clear();
            continue;
        }
        if (a[i] == x) {
            while (j < i) {
                mp[pre[j]] ++;
                j ++;
            }
        }
        pre[i] += pre[i - 1];
        dq.emplace_back(a[i]);
        if (dq.front() == x) {
            ans += mp[pre[i] - s];
        }
    }

    cout << ans << '\n';
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