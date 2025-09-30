#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<double> ans(n + 1);
    vector<vector<double>> mat(n + 2, vector<double>(n + 1));
    for (int i = 1; i <= n + 1; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> mat[i][j];
            ans[j] += mat[i][j];
        }
    }

    for (int i = 1; i <= n; i++) {
        ans[i] /= (n + 1);
    }

    double tot = 0;
    vector<double> cans(n + 1), dis(n + 2);
    auto check = [&]() {
        tot = 0;
        fill(begin(cans), end(cans), 0);
        for (int i = 1; i <= n + 1; i++) {
            dis[i] = 0;
            for (int j = 1; j <= n; j++) {
                double diff = mat[i][j] - ans[j];
                dis[i] += diff * diff;
            }
            dis[i] = sqrt(dis[i]);
            tot += dis[i];
        }
        tot /= (n + 1);
        for (int i = 1; i <= n + 1; i++) {
            for (int j = 1; j <= n; j++) {
                cans[j] += (dis[i] - tot) * (mat[i][j] - ans[j]) / tot;
            }
        }
    };

    for (double t = 10001; t >= 0.0001; t *= 0.99995) {
        check();
        for (int i = 1; i <= n; i++) {
            ans[i] += cans[i] * t;
        }
    }

    cout << fixed << setprecision(3);
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << " \n"[i == n];
    }

    return 0;
}