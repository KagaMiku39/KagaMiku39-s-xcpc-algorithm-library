#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    mt19937_64 rnd = mt19937_64(chrono::steady_clock::now().time_since_epoch().count());

    int n;
    cin >> n;

    vector<int> x(n + 1), y(n + 1), w(n + 1);
    double ansx = 0.0, ansy = 0.0;
    for (int i = 1; i <= n; i ++) {
        cin >> x[i] >> y[i] >> w[i];
        ansx += x[i];
        ansy += y[i];
    }

    ansx /= n;
    ansy /= n;

    double dis = 1e18;
    auto calc = [&](double xx, double yy) {
        double res = 0;
        for (int i = 1; i <= n; i ++) {
            double dx = x[i] - xx, dy = y[i] - yy;
            res += sqrt(dx * dx + dy * dy) * w[i];
        }
        if (res < dis) {
            dis = res;
            ansx = xx;
            ansy = yy;
        }
        return res;
    };
    
    dis = calc(ansx, ansy);
    
    uniform_real_distribution<double> dst(0.0, 1.0);
    auto SimulateAnneal = [&]() {
        double t = 10000, nowx = ansx, nowy = ansy;
        while (t > 0.001) {
            double nxtx = nowx + t * (dst(rnd) * 2 - 1), nxty = nowy + t * (dst(rnd) * 2 - 1),
            del = calc(nxtx, nxty) - calc(nowx, nowy);
            if (exp(-del / t) > dst(rnd)) {
                nowx = nxtx;
                nowy = nxty;
            }
            t *= 0.9992;
        }
        for (int i = 1; i <= 1000; i ++) {
            double nxtx = ansx + t * (dst(rnd) * 2 - 1), nxty = ansy + t * (dst(rnd) * 2 - 1);
            calc(nxtx, nxty);
        }
    };
    
    constexpr double maxt = 0.95;
    
    while ((double)clock() / CLOCKS_PER_SEC < maxt) {
        SimulateAnneal();
    }
    
    cout << fixed << setprecision(3) << ansx << ' ' << ansy << '\n';

    return 0;
}