#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

template<typename T>
struct ScapegoatTree {
    int rt{}, idx{};

    static constexpr double alpha = 0.7;

    struct Node {
        T val;
        
        int cnt;
        
        array<int, 2> sz, ch;

        Node() : val{}, cnt{}, sz{}, ch{} {}

        Node(T val) : val(val), cnt(1), sz{1, 1}, ch{} {}
    };
    vector<Node> sgt;

    vector<int> vec;

    ScapegoatTree() { 
        sgt.emplace_back();
    }

    int getrank(T val) {
        int cur = rt, rk = 1;
        while (cur) {
            if (val > sgt[cur].val) {
                rk += sgt[sgt[cur].ch[0]].sz[1] + sgt[cur].cnt;
                cur = sgt[cur].ch[1];
            } else if (val < sgt[cur].val) {
                cur = sgt[cur].ch[0];
            } else {
                rk += sgt[sgt[cur].ch[0]].sz[1];
                break;
            }
        }
        return rk;
    }

    T getval(int rk) {
        int cur = rt;
        while (true) {
            int sz = sgt[sgt[cur].ch[0]].sz[1];
            if (rk > sz + sgt[cur].cnt) {
                rk -= sz + sgt[cur].cnt;
                cur = sgt[cur].ch[1];
            } else if (sz < rk) {
                return sgt[cur].val;
            } else {
                cur = sgt[cur].ch[0];
            }
        }
    }

    void pushup(int cur) {
        if (!cur) {
            return;
        }
        int l = sgt[cur].ch[0], r = sgt[cur].ch[1];
        sgt[cur].sz[0] = sgt[l].sz[0] + sgt[r].sz[0] + (sgt[cur].cnt > 0 ? 1 : 0);
        sgt[cur].sz[1] = sgt[l].sz[1] + sgt[r].sz[1] + sgt[cur].cnt;
    }

    void flatten(int cur) {
        if (!cur) {
            return;
        }
        flatten(sgt[cur].ch[0]);
        if (sgt[cur].cnt) {
            vec.push_back(cur);
        }
        flatten(sgt[cur].ch[1]);
    }

    int build(int l, int r) {
        if (l > r) {
            return 0;
        }
        int mid = l + (r - l) / 2, cur = vec[mid];
        sgt[cur].ch[0] = build(l, mid - 1);
        sgt[cur].ch[1] = build(mid + 1, r);
        pushup(cur);
        return cur;
    }
    
    int rebuild(int cur) {
        vec.clear();
        flatten(cur);
        return build(0, vec.size() - 1);
    }
    
    bool isimbalanced(int cur) {
        return sgt[cur].sz[0] > 1 && (max(sgt[sgt[cur].ch[0]].sz[0], sgt[sgt[cur].ch[1]].sz[0]) > sgt[cur].sz[0] * alpha);
    }
    
    void insert(T val) {
        rt = insert(rt, val);
    }
    
    int insert(int cur, T val) {
        if (!cur) {
            sgt.emplace_back(val);
            idx ++;
            pushup(idx);
            return idx;
        }
        if (sgt[cur].val == val) {
            sgt[cur].cnt ++;
        } else if (val > sgt[cur].val) {
            sgt[cur].ch[1] = insert(sgt[cur].ch[1], val);
        } else {
            sgt[cur].ch[0] = insert(sgt[cur].ch[0], val);
        }
        pushup(cur);
        if (isimbalanced(cur)) {
            return rebuild(cur);
        }
        return cur;
    }

    void erase(T val) {
        rt = erase(rt, val);
    }
    
    int erase(int cur, T val) {
        if (!cur) {
            return 0;
        }
        if (sgt[cur].val == val) {
            if (sgt[cur].cnt > 0) sgt[cur].cnt --;
        } else if (val > sgt[cur].val) {
            sgt[cur].ch[1] = erase(sgt[cur].ch[1], val);
        } else {
            sgt[cur].ch[0] = erase(sgt[cur].ch[0], val);
        }
        pushup(cur);
        if (isimbalanced(cur)) {
           return rebuild(cur);
        }
        return cur;
    }

    T getpre(T val) {
        return getval(getrank(val) - 1);
    }

    T getsuc(T val) {
        return getval(getrank(val + 1));
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;

    ScapegoatTree<int> sgt;

    while (n--) {
        int opt, x;
        cin >> opt >> x;
        if (opt == 1) {
            sgt.insert(x);
        } 
        if (opt == 2) {
            sgt.erase(x);
        } 
        if (opt == 3) {
            cout << sgt.getrank(x) << '\n';
        } 
        if (opt == 4) {
            cout << sgt.getval(x) << '\n';
        } 
        if (opt == 5) {
            cout << sgt.getpre(x) << '\n';
        } 
        if (opt == 6) {
            cout << sgt.getsuc(x) << '\n';
        } 
    }

    return 0;
}