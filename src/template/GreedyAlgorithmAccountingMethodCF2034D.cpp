#include <bits/stdc++.h>

using namespace std;

void solve() {   
    int n;
    cin >> n;

    int c0 = 0, c1 = 0, c2 = 0;
    vector<int> a(n + 1);
    set<int> s[3];
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
        c0 += a[i] == 0;
        c1 += a[i] == 1;
        c2 += a[i] == 2;
        s[a[i]].emplace(i); 
    }

    vector<pair<int, int>> ans;
    for (int i = 1; i <= c0; i ++) {
        if (a[i] != 0) {
            if (a[i] == 2) {
                auto it = rbegin(s[1]);
                ans.emplace_back(i, *it);
                swap(a[i], a[*it]);
                s[2].erase(i);
                s[2].emplace(*it);
                s[1].erase(*it);
            }
            auto it = rbegin(s[0]);
            ans.emplace_back(i, *it);
            swap(a[i], a[*it]);
            s[1].erase(i);
            s[1].emplace(*it);
            s[0].erase(*it);
        }
        s[0].erase(i);
    }
    for (int i = c0 + 1; i <= c0 + c1; i ++) {
        if (a[i] != 1) {
            auto it = rbegin(s[1]);
            ans.emplace_back(i, *it);
            swap(a[i], a[*it]);
            s[2].erase(i);
            s[2].emplace(*it);
            s[1].erase(*it);
        }
        s[1].erase(i);
    }

    cout << ssize(ans) << '\n';
    for (auto &[u, v]: ans) {
        cout << u << ' ' << v << '\n';
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