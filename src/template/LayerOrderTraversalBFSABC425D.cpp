#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int h, w;
    cin >> h >> w;
    
    vector<vector<int>> vis(h + 1, vector<int>(w + 1));
    vector<vector<char>> s(h + 1, vector<char>(w + 1));
    vector<pair<int, int>> vec;
    for (int i = 1; i <= h; i ++) {
        for (int j = 1; j <= w; j ++) {
            cin >> s[i][j];
            if (s[i][j] == '#') {
                vec.emplace_back(i, j);
                vis[i][j] = true;
            }
        }
    }
    
    int off[][2]{0, 1, 1, 0, 0, -1, -1, 0};
    auto check = [&](int r, int c) {
        int cnt = 0;
        for (int i = 0; i < 4; i ++) {
            int nr = r + off[i][0], nc = c + off[i][1];
            if (nr < 1 || nr > h || nc < 1 || nc > w) {
                continue;
            }
            cnt += s[nr][nc] == '#';
        }
        return cnt == 1;
    };
    while (ssize(vec)) {
        queue<pair<int, int>> q;
        for (auto &[r, c]: vec) {
            q.emplace(r, c);
            s[r][c] = '#';
            vis[r][c] = true;
        }
        vec.clear();
        while (ssize(q)) {
            auto [r, c] = q.front();
            q.pop();
            for (int i = 0; i < 4; i ++) {
                int nr = r + off[i][0], nc = c + off[i][1];
                if (nr < 1 || nr > h || nc < 1 || nc > w || vis[nr][nc]) {
                    continue;
                }
                if (check(nr, nc)) {
                    vec.emplace_back(nr, nc);
                }
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= h; i ++) {
        for (int j = 1; j <= w; j ++) {
            ans += s[i][j] == '#';
        }
    }

    cout << ans << '\n';
    
    return 0;
}