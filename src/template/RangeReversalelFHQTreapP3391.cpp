#include <bits/stdc++.h>

using namespace std;

using u64 = unsigned long long;

template<typename T>
struct FhqTreap {
    #define lc fhq[cur].ch[0]
    #define rc fhq[cur].ch[1]
    
    inline static mt19937_64 rnd = mt19937_64(chrono::steady_clock::now().time_since_epoch().count());
    
    int root, idx{};

    struct Node {
        T val;

        u64 key;

        int sz, tag;

        array<int, 2> ch;

        Node() : val{}, key{}, sz{}, tag{}, ch{} {}
        
        Node(T val) : val(val), key(rnd()), sz(1), ch{} {}
    };
    vector<Node> fhq;

    FhqTreap() {
        fhq.emplace_back();
        root = 0;
        idx = 0;
    }

    void pushup(int cur) {
        if (cur) {
            fhq[cur].sz = fhq[lc].sz + fhq[rc].sz + 1;
        }
    }

    void pushdown(int cur) {
        if (!fhq[cur].tag) {
            return;
        }
        swap(lc, rc);
        fhq[lc].tag ^= 1;
        fhq[rc].tag ^= 1;
        fhq[cur].tag = 0;        
    }

    void split(int cur, int rk, int &lt, int &root) {
        if (!cur) {
            lt = root = 0;
            return;
        }
        pushdown(cur);
        if (fhq[lc].sz < rk) {
            rk -= fhq[lc].sz + 1;
            lt = cur;
            split(rc, rk, fhq[lt].ch[1], root);
        } else {
            root = cur;
            split(lc, rk, lt, fhq[root].ch[0]);
        }
        pushup(cur);
    }

    int merge(int lcur, int rcur) {
        if (!lcur || !rcur) {
            return lcur + rcur;
        }
        if (fhq[lcur].key > fhq[rcur].key) {
            pushdown(lcur);
            fhq[lcur].ch[1] = merge(fhq[lcur].ch[1], rcur);
            pushup(lcur);
            return lcur;
        } else {
            pushdown(rcur);
            fhq[rcur].ch[0] = merge(lcur, fhq[rcur].ch[0]);
            pushup(rcur);
            return rcur;
        }
    }

    int newnode(T val) {
        idx ++;
        fhq.emplace_back(val);
        return idx;
    }

    void insert(T val) {
        int lt = 0, rt = 0;
        split(root, val, lt, rt);
        root = merge(merge(lt, newnode(val)), rt);
    }

    void flip(int lo, int ro) {
        int lt = 0, rt = 0, lrt = 0;   
        split(root, ro, lt, rt);
        split(lt, lo - 1, lt, lrt);
        fhq[lrt].tag ^= 1;
        root = merge(merge(lt, lrt), rt);
    }

    void print(int n) {
        auto dfs = [&](auto &self, int cur) -> void {
            if (!cur) {
                return;
            }
            pushdown(cur);
            self(self, lc);
            cout << fhq[cur].val << " \n"[!-- n];
            self(self, rc);
        };
        dfs(dfs, root);
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n, m;
    cin >> n >> m;

    FhqTreap<int> fhq;

    for (int i = 1; i <= n; i ++) {
        fhq.insert(i);
    }
    
    while (m --) {
        int l, r;
        cin >> l >> r;
        fhq.flip(l, r);
    }

    fhq.print(n);

    return 0;
}