#include <bits/stdc++.h>

using namespace std;

template<typename T>
bool cmax(T &a, const T &b) {
    return a < b ? a = b, true : false;
}

struct DisjointSetUnion {
    vector<int> p, sz;

    DisjointSetUnion(int n) : p(n + 1), sz(n + 1, 1) {
        iota(begin(p), end(p), 0);
    }

    int find(int x) {
        while (x != p[x]) {
            x = p[x] = p[p[x]];
        }
        return x;
    }

    void merge(int a, int b) {
        int pa = find(a), pb = find(b);
        if (pa == pb) {
            return;
        }
        if (sz[pa] > sz[pb]) {
            swap(pa, pb);
        }
        p[pa] = pb;
        sz[pb] += sz[pa];
    }
};

void solve() {   
    int n, m;
    cin >> n >> m;

    vector<vector<char>> mat(n + 1, vector<char>(m + 1));
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= m; j ++) {
            cin >> mat[i][j];
        }
    }
    
    auto foo = [&](vector<vector<char>> &mat) {
        DisjointSetUnion dsu(n * m);
        auto getid = [&](int r, int c) {
            return (r - 1) * (ssize(mat.front()) - 1) + c;
        };
        for (int i = 1; i < ssize(mat); i ++) {
            for (int j = 1; j < ssize(mat[i]); j ++) {
                if (mat[i][j] == '#') {
                    if (j && mat[i][j - 1] == '#') {
                        dsu.merge(getid(i, j), getid(i, j - 1));
                    }
                    if (i && mat[i - 1][j] == '#') {
                        dsu.merge(getid(i, j), getid(i - 1, j));
                    }
                }
            }
        }
        int ans = 0;
        for (int i = 1; i < ssize(mat); i ++) {
            int res = 0;
            map<int, bool> mp;
            for (int j = 1; j < ssize(mat[i]); j ++) {
                auto check = [&](int r, int c) {
                    if (r < 1 || r >= ssize(mat) || mat[r][c] != '#') {
                        return;
                    }
                    int p = dsu.find(getid(r, c));
                    if (mp[p]) {
                        return;
                    }
                    mp[p] = true;
                    res += dsu.sz[p];
                };
                if (mat[i][j] == '#') {
                    check(i, j);
                } else {
                    res ++;
                    check(i - 1, j);
                    check(i + 1, j);
                }
            }
            cmax(ans, res);
        }
        return ans;
    };

    auto getrev = [&]() {
        vector<vector<char>> tmp(ssize(mat.front()), vector<char>(ssize(mat)));
        for (int i = 1; i < ssize(mat.front()); i ++) {
            for (int j = 1; j < ssize(mat); j ++) {
                tmp[i][j] = mat[j][i];
            }
        }
        tmp.swap(mat);
    };
    
    int ans = 0;
    cmax(ans, foo(mat));
    getrev();
    cmax(ans, foo(mat));

    cout << ans << '\n';
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