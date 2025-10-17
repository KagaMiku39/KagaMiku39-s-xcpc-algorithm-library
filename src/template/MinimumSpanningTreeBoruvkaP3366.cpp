#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

struct DisjointSetUnion {
    vector<int> p;

    DisjointSetUnion(int n) : p(n + 1) {
        iota(begin(p), end(p), 0);
    }

    int find(int x) {
        while (x != p[x]) {
            x = p[x] = p[p[x]];
        }
        return x;
    }

    bool merge(int a, int b) {
        int pa = find(a), pb = find(b);
        if (pa == pb) {
            return false;
        }        
        p[pa] = pb;
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<tuple<int, int, int>> adj(m);
    for (auto &[w, u, v] : adj) {
        cin >> u >> v >> w;
    }

    DisjointSetUnion dsu(n);
    int ans = 0, cnt = n;

    while (cnt > 1) {
        vector<tuple<int, int, int>> vec(n + 1, {INT_MAX, -1, -1});
        for (auto &[w, u, v] : adj) {
            int pu = dsu.find(u), pv = dsu.find(v);
            if (pu == pv) continue;
            if (w < get<0>(vec[pu])) {
                vec[pu] = {w, u, v};
            }
            if (w < get<0>(vec[pv])) {
                vec[pv] = {w, u, v};
            }
        }
        bool tag = false;
        for (auto &[w, u, v] : vec) {
            if (w == INT_MAX) {
                continue;
            }
            if (dsu.merge(u, v)) {
                ans += w;
                cnt --;
                tag = true;
            }
        }
        if (!tag) {
            cout << "orz\n";
            return 0;
        }
    }

    cout << ans << '\n';
    
    return 0;
}