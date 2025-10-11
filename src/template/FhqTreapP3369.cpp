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

        int sz;

        array<int, 2> ch;

        Node() : val{}, key{}, sz{}, ch{} {}
        
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

    void split(int cur, T val, int &lt, int &root) {
        if (!cur) {
            lt = root = 0;
            return;
        }
        if (fhq[cur].val <= val) {
            lt = cur;
            split(rc, val, fhq[lt].ch[1], root);
        } else {
            root = cur;
            split(lc, val, lt, fhq[root].ch[0]);
        }
        pushup(cur);
    }

    int merge(int lcur, int rcur) {
        if (!lcur || !rcur) {
            return lcur + rcur;
        }
        if (fhq[lcur].key > fhq[rcur].key) {
            fhq[lcur].ch[1] = merge(fhq[lcur].ch[1], rcur);
            pushup(lcur);
            return lcur;
        } else {
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

    void erase(T val) {
        int lt = 0, rt = 0, id = 0;
        split(root, val, lt, rt);
        split(lt, val - 1, lt, id);
        if (id) {
            id = merge(fhq[id].ch[0], fhq[id].ch[1]);
        }
        root = merge(merge(lt, id), rt);
    }

    int getrank(T val) {
        int lt = 0, rt = 0;
        split(root, val - 1, lt, rt);
        int rk = fhq[lt].sz + 1;
        root = merge(lt, rt);
        return rk;
    }

    T getval(int rk) {
        return fhq[getval(root, rk)].val;
    }
    
    int getval(int cur, int rk) {
        while (cur) {
            int sz = fhq[lc].sz;
            if (sz + 1 > rk) {
                cur = lc;
            } else if (sz + 1 == rk) {
                break;
            } else {
                rk -= sz + 1;
                cur = rc;
            }
        }
        return cur;
    }
    
    T getpre(T val) {
        int lt = 0, rt = 0;
        split(root, val - 1, lt, rt);
        T res = 0;
        if (lt) {
            int pre = getval(lt, fhq[lt].sz);
            res = fhq[pre].val;
        }
        root = merge(lt, rt);
        return res;
    }

    T getsuc(T val) {
        int lt = 0, rt = 0;
        split(root, val, lt, rt);
        T res = 0;
        if (rt) {
            int suc = getval(rt, 1);
            res = fhq[suc].val;
        }
        root = merge(lt, rt);
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n;
    cin >> n;

    FhqTreap<int> fhq;

    while (n--) {
        int opt, x;
        cin >> opt >> x;
        if (opt == 1) {
            fhq.insert(x);
        }
        if (opt == 2) {
            fhq.erase(x);
        }
        if (opt == 3) {
            cout << fhq.getrank(x) << '\n';
        }
        if (opt == 4) {
            cout << fhq.getval(x) << '\n';
        }
        if (opt == 5) {
            cout << fhq.getpre(x) << '\n';
        }
        if (opt == 6) {
            cout << fhq.getsuc(x) << '\n';
        }
    }

    return 0;
}