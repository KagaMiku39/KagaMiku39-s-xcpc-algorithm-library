#include <bits/stdc++.h>

using namespace std;

struct PersistentTrie {
    static constexpr int loga = 24;

    int idx{};

    // int cnt{};
    
    struct Node {
        int sz;

        array<int, 2> adj;
    }; 
    vector<Node> tr;

    vector<int> rt;
    
    PersistentTrie() {
        tr.emplace_back();
        rt.emplace_back();
        insert(0);
    }

    // PersistentTrie(int n, int m) : tr((n + m) * loga + 1), rt(n + m + 1) {
    //     insert(0);
    // }
    
    void insert(int val) {
        int last = rt.back(), now = ++ idx;
        // int last = rt[cnt], now = ++ idx;
        tr.emplace_back(tr[last]);
        // tr[now] = tr[last];
        tr[now].sz ++;
        rt.emplace_back(now);
        // cnt ++;
        // rt[cnt] = now;
        for (int i = 23; ~i; i --) {
            bool j = (val >> i) & 1;
            int nxl = tr[last].adj[j], nxn = ++ idx;
            tr.emplace_back(tr[nxl]);
            // tr[nxn] = tr[nxl];
            tr[nxn].sz ++;
            tr[now].adj[j] = nxn;
            last = tr[last].adj[j];
            now = tr[now].adj[j];
        }
    }

    int query(int lo, int ro, int val) {
        int res = 0, last = rt[lo], now = rt[ro];
        for (int i = 23; ~i; i --) {
            bool j = (val >> i) & 1;
            if (tr[tr[now].adj[!j]].sz > tr[tr[last].adj[!j]].sz) {
                res |= (1 << i);
                last = tr[last].adj[!j];
                now = tr[now].adj[!j];
            } else {
                last = tr[last].adj[j];
                now = tr[now].adj[j];
            }
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    
    PersistentTrie pt;

    // PersistentTrie pt(n, m);
    
    int pre = 0;
    for (int i = 1; i <= n; i ++) {
        int a;
        cin >> a;
        pre ^= a;
        pt.insert(pre);
    }
    
    while (m --) {
        char opt;
        cin >> opt;
        if (opt == 'A') {
            int x;
            cin >> x;
            pre ^= x;
            pt.insert(pre);
        }
        if (opt == 'Q') {
            int l, r, x;
            cin >> l >> r >> x;
            cout << pt.query(l - 1, r, x ^ pre) << '\n';
        }
    }

    return 0;
}