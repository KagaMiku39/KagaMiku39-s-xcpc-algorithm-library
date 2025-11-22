#include <bits/stdc++.h>

using namespace std;

template<typename T>
bool cmin(T &a, const T &b) {
    return a > b ? a = b, true : false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, l, x, y;
    cin >> n >> m >> l >> x >> y;

    vector<int> s(n + 1), t(n + 1);
    vector<tuple<int, int, double>> ele;
    for (int i = 1; i <= n; i ++) {
        cin >> s[i] >> t[i];
        double cst = double(t[i] - s[i]) / x + double(l - t[i]) / y;
        ele.emplace_back(s[i], -1, cst);
        ele.emplace_back(t[i], 1, cst);
    }

    vector<int> p(m + 1);
    for (int i = 1; i <= m; i ++) {
        cin >> p[i];
        ele.emplace_back(p[i], 0, i);
    }

    sort(begin(ele), end(ele));
    
    multiset<double> ms;
    
    vector<double> ans(m + 1, DBL_MAX);
    for (auto &[pos, tag, val]: ele) {
        if (!tag) {
            ans[val] = double(l - pos) / y;
            if (ssize(ms)) {
                cmin(ans[val], *begin(ms));
            }
        } else if (!~tag) {
            ms.emplace(val);
        } else {
            ms.erase(val);
        }
    }
    
    cout << fixed << setprecision(8);

    for (int i = 1; i <= m; i ++) {
        cout << ans[i] << '\n';
    }
    
    return 0;
}