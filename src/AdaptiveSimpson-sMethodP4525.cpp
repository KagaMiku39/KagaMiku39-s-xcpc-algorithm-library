#include <bits/stdc++.h>

using namespace std;

const double eps = 1e-10;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    double a, b, c, d, l, r;
    cin >> a >> b >> c >> d >> l >> r;
    
    auto f = [&](double x) {
        return (c * x + d) / (a * x + b);
    };

    auto simpson = [&](double lo, double ro) {
        double mid = (lo + ro) / 2;
        return (ro - lo) * (f(lo) + 4 * f(mid) + f(ro)) / 6.0;
    };

    auto asr = [&](auto &self, double lo, double ro, double res) -> double {
        double mid = (lo + ro) / 2, ans[2] = {simpson(lo, mid), simpson(mid, ro)};
        if (abs(ans[0] + ans[1] - res) < eps) {
            return res;
        }
        return self(self, lo, mid, ans[0]) + self(self, mid, ro, ans[1]);
    };

    cout << fixed << setprecision(6) << asr(asr, l, r, simpson(l, r)) << '\n';

    return 0;
}