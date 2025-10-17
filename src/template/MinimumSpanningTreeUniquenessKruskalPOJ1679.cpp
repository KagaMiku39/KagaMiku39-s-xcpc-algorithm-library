#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <numeric>

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

void solve() {
    int n, m;
    cin >> n >> m;

    vector<tuple<int, int, int>> adj;
    for (int i = 1; i <= m; i ++) {
        int x, y, w;
        cin >> x >> y >> w;
        adj.emplace_back(w, x, y);
    }

    sort(begin(adj), end(adj));

    bool res = false;
    int ans = 0;
    DisjointSetUnion dsu(n + 1);
    for (int i = 0; i < ssize(adj); ) {
        int cnt1 = 0, j = i;
        for (; j < ssize(adj); j ++) {
            if (get<0>(adj[i]) != get<0>(adj[j])) {
                break;
            }
            cnt1 ++;
        }
        int cnt2 = 0;
        for (int k = i; k < j; k ++) {
            auto &[w, u, v] = adj[k];
            if (dsu.merge(u, v)) {
                cnt2 ++;
                ans += w;
            }
        }
        res |= cnt2 && cnt1 > cnt2;
        i = j;
    }

    if (res) {
        cout << "Not Unique!\n";
    } else {
        cout << ans << '\n';
    }
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