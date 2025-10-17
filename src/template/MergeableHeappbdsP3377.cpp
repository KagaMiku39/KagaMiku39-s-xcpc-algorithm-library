#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

#include <ext/pb_ds/priority_queue.hpp>

namespace pbds = __gnu_pbds;

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
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    
    vector<pbds::priority_queue<pair<int, int>, greater<pair<int, int>>, __gnu_pbds::pairing_heap_tag>> pq(n + 1);
    for (int i = 1; i <= n; ++i) {
        int v;
        cin >> v;
        pq[i].push({v, i});
    }
    
    vector<bool> isdel(n + 1);

    DisjointSetUnion dsu(n);

    while (m --) {
        int opt;
        cin >> opt;
        if (opt == 1) {
            int x, y;
            cin >> x >> y;
            if (isdel[x] || isdel[y]) {
                continue;
            }
            int px = dsu.find(x), py = dsu.find(y);
            if (px != py) {
                if (ssize(pq[px]) < ssize(pq[py])) {
                    swap(px, py);
                }
                pq[px].join(pq[py]);
                dsu.p[py] = px;
            }
        } 
        if (opt == 2) {
            int x;
            cin >> x;
            if (isdel[x]) {
                cout << "-1\n";
            } else {
                int px = dsu.find(x);
                auto [val, id] = pq[px].top();
                cout << val << "\n";
                pq[px].pop();
                isdel[id] = true;
            }
        }
    }

    return 0;
}