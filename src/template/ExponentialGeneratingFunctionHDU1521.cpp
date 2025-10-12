#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<double> fac(101);
    fac[0] = 1;
    for (int i = 1; i <= 100; i ++) {
        fac[i] = fac[i - 1] * i;
    }

    int n, m;
    while (cin >> n >> m) {
        vector<int> vec(n + 1);
        for (int i = 1; i <= n; i ++) {
            cin >> vec[i];
        }

        vector<double> a(m + 1), b(m + 1);
        for (int i = 0; i <= min(m, vec[1]); i ++) {
            a[i] = 1 / fac[i];
        }
        
        for (int i = 2; i <= n; i ++) {
            for (int j = 0; j <= m; j ++) {
                for (int k = 0; k <= vec[i] && j + k <= m; k ++) {
                    b[j + k] += a[j] / fac[k];
                }
            }
            for (int j = 0; j <= m; j ++) {
                a[j] = b[j];
                b[j] = 0;
            }
        }

        cout << fixed << setprecision(0) <<  a[m] * fac[m] << '\n';
    }

    return 0;
}