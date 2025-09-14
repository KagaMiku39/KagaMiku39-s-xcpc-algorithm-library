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

    vector<int> d(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> d[i];
    }

    vector<int> l(n + 1), r(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> l[i] >> r[i];
    }

    vector<int> mi(n + 1), mx(n + 1);
    for (int i = 1; i <= n; i ++) {
        mi[i] = mi[i - 1];
        mx[i] = mx[i - 1];
        if (~d[i]) {
            mi[i] += d[i];
            mx[i] += d[i];
        } else {
            mx[i] ++;
        }
        cmax(mi[i], l[i]);
        cmin(mx[i], r[i]);
        if (mi[i] > r[i] || mx[i] < l[i]) {
            cout << "-1\n";
            return;
        }
    }

    int h = mx[n];
    vector<int> ans = d;
    for (int i = n; i; i --) {
        if (~d[i]) {
            h -= d[i];
            cmin(mx[i - 1], h);
            continue;
        } 
        if (h > mx[i - 1]) {
            ans[i] = 1;
            h --;
        } else {
            ans[i] = 0;
        }
    }

    for (int i = 1; i <= n; i ++) {
        cout << ans[i] << " \n"[i == n];
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
