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