#include <bits/stdc++.h>

using namespace std;

template<typename T>
bool cmax(T &a, const T &b) {
    return a < b ? a = b, true : false;
}

void solve() {   
    int n;
    cin >> n;

    vector<int> a(n + 1), b(n + 1), c(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> a[i] >> b[i] >> c[i];
    }

    double lo = 0, ro = 1000;
    auto pred = [&](double x) -> double {
        auto f = [&](int id) {
            return a[id] * x * x + b[id] * x + c[id];
        };
        double res = -DBL_MAX;
        for (int i = 1; i <= n; i ++) {
            cmax(res, f(i));
        }
        return res;
    };
    for (int i = 1; i <= 100; i ++) {
        double l = lo + (ro - lo) / 3, r = ro - (ro - lo) / 3;
        if (pred(l) < pred(r)) {
            ro = r;
        } else {
            lo = l;
        }
    }

    cout << fixed << setprecision(4) << pred(lo) << '\n';
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