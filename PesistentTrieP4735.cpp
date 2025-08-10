#include <bits/stdc++.h>

using namespace std;

struct PersistentTrie {
    int idx{};
    
    struct Node {
        int sz;

        array<int, 2> edges;
    }; 
    vector<Node> tr;

    vector<int> rt;
    
    PersistentTrie() {
        tr.emplace_back();
        rt.emplace_back();
        insert(0);
        tr[rt[0]].sz = 0;
    }
    
    void insert(int val) {
        int last = rt.back(), now = ++ idx;
        tr.emplace_back(tr[last]);
        tr[now].sz ++;
        rt.emplace_back(now);
        for (int i = 23; ~i; i --) {
            bool j = (val >> i) & 1;
            int nxlast = tr[last].edges[j];
            int nxnow = ++ idx;
            tr.emplace_back(tr[nxlast]);
            tr[nxnow].sz ++;
            tr[now].edges[j] = nxnow;
            last = tr[last].edges[j];
            now = tr[now].edges[j];
        }
    }

    int query(int lo, int ro, int val) {
        int res = 0, last = rt[lo], now = rt[ro];
        for (int i = 23; ~i; i --) {
            bool j = (val >> i) & 1;
            if (tr[tr[now].edges[!j]].sz > tr[tr[last].edges[!j]].sz) {
                res |= (1 << i);
                last = tr[last].edges[!j];
                now = tr[now].edges[!j];
            } else {
                last = tr[last].edges[j];
                now = tr[now].edges[j];
            }
        }
        return res;
    }
};

void solve() {   
    int n, m;
    cin >> n >> m;
    
    PersistentTrie pt;
    
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
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}