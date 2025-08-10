#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

struct DisjointSetUnion {
    vector<int> p, rk, sz;

    DisjointSetUnion(int n) : p(n + 1), rk(n + 1), sz(n + 1, 1) {
        iota(begin(p), end(p), 0);
    }

    int find(int x) {
        while (x != p[x]) {
            x = p[x] = p[p[x]];
        }
        return x;
    }

    bool merge(int a, int b) {
        int pa[2]{find(a), find(b)};
        if (pa[0] == pa[1]) {
            return false;
        }        
        if (rk[pa[0]] > rk[pa[1]]) {
            swap(pa[0], pa[1]);
        }
        p[pa[0]] = pa[1];
        rk[pa[1]] += rk[pa[0]] == rk[pa[1]];
        return true;
    }

    // void merge(int a, int b) {
    //     int pa[2]{find(a), find(b)};
    //     if (pa[0] == pa[1]) {
    //         return;
    //     }        
    //     if (sz[pa[0]] > sz[pa[1]]) {
    //         swap(pa[0], pa[1]);
    //     }
    //     p[pa[0]] = pa[1];
    //     sz[pa[1]] += sz[pa[0]];
    // }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
    for (int i = 1; i <= m; i ++) {
        int x, y, z;
        cin >> x >> y >> z;
        pq.emplace(z, x, y);
    }

    DisjointSetUnion dsu(n);

    int ans = 0;
    while (ssize(pq)) {
        auto [w, u, v] = pq.top();
        pq.pop();
        if (!dsu.merge(u, v)) {
            continue;
        }
        ans += w;
    }

    int cnt = 0;
    for (int i = 1; i <= n; i ++) {
        cnt += i == dsu.find(i);
    }

    if (cnt > 1) {
        cout << "orz\n";
        return 0;
    }

    cout << ans << '\n';

    return 0;
}