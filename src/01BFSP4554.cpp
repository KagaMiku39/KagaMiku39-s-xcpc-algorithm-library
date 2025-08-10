#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

template<typename T>
bool cmin(T &a, const T &b) {
    return a > b ? a = b, true : false;
}

bool solve() {
    int n, m;
    cin >> n >> m;

    if (!n && !m) {
        return false;
    }

    vector<vector<char>> mat(n, vector<char>(m));
    for (auto &i: mat) {
        for (char &j: i) {
            cin >> j;
        }
    }
    
    int x[2], y[2];
    for (int i = 0; i < 2; i ++) {
        cin >> x[i] >> y[i];
    }

    int off[][2]{0, 1, 1, 0, 0, -1, -1, 0};
    
    vector<vector<int>> vis(n, vector<int>(m)), dis(n, vector<int>(m, INT_MAX));
    deque<pair<int, int>> dq; 
    dis[x[0]][y[0]] = 0;
    dq.emplace_front(x[0], y[0]);
    while (ssize(dq)) {
        auto [r, c] = dq.front();
        dq.pop_front();
        if (vis[r][c]) {
            continue;
        }
        vis[r][c] = true;
        for (int i = 0; i < 4; i ++) {
            int nr = r + off[i][0], nc = c + off[i][1];
            if (nr < 0 || nr > n - 1 || nc < 0 || nc > m - 1 || vis[nr][nc]) {
                continue;
            } 
            int wei = mat[nr][nc] != mat[r][c];
            if (cmin(dis[nr][nc], dis[r][c] + wei)) {
                if (wei) {
                    dq.emplace_back(nr, nc);
                } else {
                    dq.emplace_front(nr, nc);
                }
            }
        }
    }

    cout << dis[x[1]][y[1]] << '\n';

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (solve()) ;

    return 0;
}