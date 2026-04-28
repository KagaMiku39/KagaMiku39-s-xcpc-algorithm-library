#include <bits/stdc++.h>

using namespace std;

template<typename T>
bool cmin(T &a, const T &b) {
    return a > b ? a = b, true : false;
}

template<typename T>
bool cmax(T &a, const T &b) {
    return a < b ? a = b, true : false;
}

void solve() {   
    int n;
    cin >> n;

    int mi = INT_MAX, mx = 0;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
        cmin(mi, a[i]);
        cmax(mx, a[i]);
    }
    
    vector<int> ans;
    while (mi != mx) {
        int x = mi % 2;
        mx = (mx + x) / 2;
        mi = (mi + x) / 2;
        ans.emplace_back(x);
    }

    cout << ssize(ans) << '\n';
    if (ssize(ans) <= n) {
        for (int j = 1; int &i: ans) {
            cout << i << " \n"[j ++ == ssize(ans)];
        }
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