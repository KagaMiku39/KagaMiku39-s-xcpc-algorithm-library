#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

template<typename T>
bool cmin(T &a, const T &b) {
    return a > b ? a = b, true : false;
}

template<typename T>
bool cmax(T &a, const T &b) {
    return a < b ? a = b, true : false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<i64>> w(n + 1, vector<i64>(n + 1, LLONG_MIN));
    for (int i = 1; i <= m; i ++) {
        int y, c;
        i64 h;
        cin >> y >> c >> h;
        w[y][c] = h;
    }

    vector<i64> la(n + 1, LLONG_MIN), lb(n + 1);
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= n; j++) {
            cmax(la[i], w[i][j]);
        }
    }

    vector<int> mat(n + 1);
    for (int i = 1; i <= n; i ++) {
        vector<i64> d(n + 1, LLONG_MAX);
        vector<int> p(n + 1), vb(n + 1);
        mat[0] = i;
        int v = 0;
        while (true) {
            vb[v] = true;
            int u = mat[v], nx = 0;
            i64 del = LLONG_MAX;
            for (int j = 1; j <= n; j++) {
                if (!vb[j]) {
                    if (w[u][j] > LLONG_MIN) {
                        if (cmin(d[j], la[u] + lb[j] - w[u][j])) {
                            p[j] = v;
                        }
                    }
                    if (cmin(del, d[j])) {
                        nx = j;
                    }
                }
            }
            for (int j = 0; j <= n; j++) {
                if (vb[j]) {
                    la[mat[j]] -= del;
                    lb[j] += del;
                } else {
                    d[j] -= del;
                }
            }
            v = nx;
            if (!mat[v]) {
                break;
            }
        }
        while (v) {
            mat[v] = mat[p[v]];
            v = p[v];
        }
    }

    i64 ans = 0;
    for (int i = 1; i <= n; i ++) {
        if (w[mat[i]][i] > LLONG_MIN) {
            ans += w[mat[i]][i];
        }
    }
    
    cout << ans << '\n';
    for (int i = 1; i <= n; i ++) {
        cout << mat[i] << " \n"[i == n];
    }

    return 0;
}