#include <bits/stdc++.h>

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

    // void merge(int a, int b) {
    //     int pa = find(a), pb = find(b);
    //     if (pa == pb) {
    //         return;
    //     }
    //     if (rk[pa] > rk[pb]) {
    //         swap(pa, pb);
    //     }
    //     p[pa] = pb;
    //     rk[pb] += rk[pa] == rk[pb];
    // }

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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    DisjointSetUnion dsu(n);

    while (m --) {
        int z, x, y;
        cin >> z >> x >> y;
        if (z == 1) {
            dsu.merge(x, y);
        }
        if (z == 2) {
            cout << (dsu.find(x) == dsu.find(y) ? "Y\n" : "N\n");
        }
    }

    return 0;
}