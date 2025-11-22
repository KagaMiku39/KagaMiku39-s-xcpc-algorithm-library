#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

void solve() {   
    int n, m;
    cin >> n >> m;

    string s;
    cin >> s;

    s = ' ' + s;
    
    vector<int> a(m + 1);
    for (int i = 1; i <= m; i ++) {
        cin >> a[i];
    }

    set<int> se(next(begin(a)), end(a));
    
    if (s[1] == 'A') {
        se.emplace(2);
    } else {
        auto it = se.upper_bound(1);
        if (it == end(se)) {
            se.emplace(2);
        } else {
            int nx = 2;
            while (*it == nx) {
                it ++;
                nx ++;
            }
            se.emplace(nx);
        }
    }

    for (int i = 2, la = 1; i <= n; i ++) {
        int pos = la;
        if (s[i - 1] == 'A') {
            pos ++;
        } else {
            auto it = se.upper_bound(la);
            if (it == end(se)) {
                pos ++;
            } else {
                int nx = pos + 1;
                while (*it == nx) {
                    it ++;
                    nx ++;
                }
                pos = nx;
            }
        }
        la = pos;
        if (s[i] == 'A') {
            se.emplace(pos + 1);
        } else {
            auto it = se.upper_bound(pos);
            if (it == end(se)) {
                se.emplace(pos + 1);
            } else {
                int nx = pos + 1;
                while (*it == nx) {
                    it ++;
                    nx ++;
                }
                se.emplace(nx);
            }
        }
    }
    
    cout << ssize(se) << '\n';
    
    int ba = *rbegin(se);
    for (int i: se) {
        cout << i << " \n"[i == ba];
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