#include <bits/stdc++.h>

using namespace std;

#include <ext/pb_ds/priority_queue.hpp>

namespace pbds = __gnu_pbds;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<pbds::priority_queue<int, greater<int>>> pq(n + 1);
    vector<pbds::priority_queue<int, greater<int>>::point_iterator> p(n + 1);
    for (int i = 1; i <= n; i ++) {
        int x;
        cin >> x;
        p[i] = pq[i].push(x);
    }

    while (m --) {
        int opt;
        cin >> opt;
        if (opt == 0) {
            int x, y;
            cin >> x >> y;
            pq[x].erase(p[y]);
        }
        if (opt == 1) {
            int x;
            cin >> x;
            cout << pq[x].top() << '\n';
        }
        if (opt == 2) {
            int x, y;
            cin >> x >> y;
            pq[x].join(pq[y]);
        }
        if (opt == 3) {
            int x, y, z;
            cin >> x >> y >> z;
            pq[x].modify(p[y], z); 
        }
    }

    return 0;
}