#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;

    pair<int, int> bo, gi;
    vector<pair<int, int>> gh;
    vector<vector<char>> mat(n + 1, vector<char>(m + 1));
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= m; j ++) {
            cin >> mat[i][j];
            if (mat[i][j] == 'M') {
                bo = {i, j};
            } 
            if (mat[i][j] == 'G') {
                gi = {i, j};
            }
            if (mat[i][j] == 'Z') {
                gh.emplace_back(i, j);
            }
        }
    }

    if (bo == gi) {
        cout << "0\n";
        return;
    }
    
    int t = 0, off[][2] = {0, 1, 1, 0, 0, -1, -1, 0};
    queue<pair<int, int>> qb, qg;
    vector<vector<int>> vis(n + 1, vector<int>(m + 1));
    auto check = [&](int r, int c, int t) {
        if (r < 1 || r > n || c < 1 || c > m || mat[r][c] == 'X') {
            return false;
        }
        for (auto & [gr, gc] : gh) {
            if (abs(r - gr) + abs(c - gc) <= t * 2) {
                return false;
            }
        }
        return true;
    };
    qb.emplace(bo.first, bo.second);
    vis[bo.first][bo.second] = 1;
    qg.emplace(gi.first, gi.second);
    vis[gi.first][gi.second] = 2;
    while (ssize(qb) || ssize(qg)) {
        t ++;
        for (int i = 0; i < 3 && ssize(qb); i ++) {
            int s = ssize(qb);
            while (s --) {
                auto [r, c] = qb.front();
                qb.pop();
                if (!check(r, c, t)) {
                    continue;
                }
                for (int j = 0; j < 4; j ++) {
                    int nr = r + off[j][0], nc = c + off[j][1];
                    if (check(nr, nc, t)) {
                        if (vis[nr][nc] == 2) {
                            cout << t << '\n';
                            return;
                        }
                        if (!vis[nr][nc]) {
                            vis[nr][nc] = 1;
                            qb.emplace(nr, nc);
                        }
                    }
                }
            }
        }
        int s = ssize(qg);
        while (s --) {
            auto [r, c] = qg.front();
            qg.pop();
            if (!check(r, c, t)) {
                continue;
            }
            for (int j = 0; j < 4; j ++) {
                int nr = r + off[j][0], nc = c + off[j][1];
                if (check(nr, nc, t)) {
                    if (vis[nr][nc] == 1) {
                        cout << t << '\n';
                        return;
                    }
                    if (!vis[nr][nc]) {
                        vis[nr][nc] = 2;
                        qg.emplace(nr, nc);
                    }
                }
            }
        }
    }

    cout << "-1\n";
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