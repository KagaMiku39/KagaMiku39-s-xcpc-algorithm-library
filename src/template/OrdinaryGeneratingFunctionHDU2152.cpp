#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    while (cin >> n >> m) {
        vector<int> a(n + 1), b(n + 1);
        for (int i = 1; i <= n; i ++) {
            cin >> a[i] >> b[i];
        }
        
        vector<int> c(m + 1);
        for (int i = a[1]; i <= b[1]; i ++) {
            if (i <= m) {
                c[i] = 1;
            }
        }
        
        for (int i = 2; i <= n; i ++) {
            vector<int> d(m + 1);
            for (int j = 0; j <= m; j ++) {
                if (c[j] > 0) {
                    for (int k = a[i]; k <= b[i]; k ++) {
                        if (j + k <= m) {
                            d[j + k] += c[j];
                        }
                    }
                }
            }
            c = d;
        }

        cout << c[m] << '\n';
    }

    return 0;
}