#include <bits/stdc++.h>

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

    void merge(int a, int b) {
        p[find(a)] = find(b);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> u(m + 1), v(m + 1), w(m + 1);
    for (int i = 1; i <= m; i ++) {
        cin >> u[i] >> v[i] >> w[i];
    }

    int ans = (1 << 30) - 1;
    for (int i = 29; ~i; i --) {
        DisjointSetUnion dsu(n);
        int tmp = ans ^ (1 << i); 
        for (int j = 1; j <= m; j ++) {
            if ((tmp | w[j]) == tmp) {
                dsu.merge(u[j], v[j]);
            }
        }
        if (dsu.find(1) == dsu.find(n)) {
            ans = tmp;
        }
    }

    cout << ans << '\n';

    return 0;
}