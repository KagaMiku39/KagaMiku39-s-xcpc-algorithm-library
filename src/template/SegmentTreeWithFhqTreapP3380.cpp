#include <bits/stdc++.h>

using namespace std;

using u64 = unsigned long long;

template<typename T>
bool cmin(T &a, const T &b) {
    return a > b ? a = b, true : false;
}

template<typename T>
bool cmax(T &a, const T &b) {
    return a < b ? a = b, true : false;
}

template<typename T>
struct SegmentTreeWithFhqTreap {
    #define lc cur * 2
    #define rc cur * 2 + 1

    inline static mt19937_64 rnd = mt19937_64(chrono::steady_clock::now().time_since_epoch().count());
    
    vector<T> vec;
    
    int n;

    struct Node {
        T val;

        u64 key;

        int sz;

        array<int, 2> ch{};

        Node() : val{}, key{}, sz{} {}

        Node(T val) : val(val), key(rnd()), sz(1) {}
    };
    vector<Node> fhq;

    int idx{};

    vector<int> seg;

    SegmentTreeWithFhqTreap(int n, const vector<T> &vec) : n(n), vec(vec), seg(4 * n) {
        fhq.emplace_back();
        build(1, 1, n);
    }

    void pushup(int cur) {
        if (cur) {
            fhq[cur].sz = fhq[fhq[cur].ch[0]].sz + fhq[fhq[cur].ch[1]].sz + 1;
        }
    }

    int newnode(T val) {
        idx ++;
        fhq.emplace_back(val);
        return idx;
    }

    void split(int cur, T val, int &lt, int &rt) {
        if (!cur) {
            lt = rt = 0;
            return;
        }
        if (fhq[cur].val <= val) {
            lt = cur;
            split(fhq[cur].ch[1], val, fhq[lt].ch[1], rt);
        } else {
            rt = cur;
            split(fhq[cur].ch[0], val, lt, fhq[rt].ch[0]);
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

    void insert(int &root, T val) {
        int lt = 0, rt = 0;
        split(root, val, lt, rt);
        root = merge(merge(lt, newnode(val)), rt);
    }

    void erase(int &root, T val) {
        int lt = 0, rt = 0, id = 0;
        split(root, val, lt, rt);
        split(lt, val - 1, lt, id);
        if (id) {
            id = merge(fhq[id].ch[0], fhq[id].ch[1]);
        }
        root = merge(merge(lt, id), rt);
    }

    int getrank(int &root, T val) {
        int lt = 0, rt = 0;
        split(root, val - 1, lt, rt);
        int rk = fhq[lt].sz + 1;
        root = merge(lt, rt);
        return rk;
    }

    int getval(int cur, int rk) {
        while (cur) {
            int sz = fhq[fhq[cur].ch[0]].sz;
            if (sz + 1 > rk) {
                cur = fhq[cur].ch[0];
            } else if (sz + 1 == rk) {
                break;
            } else {
                rk -= sz + 1;
                cur = fhq[cur].ch[1];
            }
        }
        return cur;
    }

    T getpre(int &root, T val) {
        int lt = 0, rt = 0;
        split(root, val - 1, lt, rt);
        T res = -numeric_limits<T>::max();
        if (lt) {
            int pre = getval(lt, fhq[lt].sz);
            res = fhq[pre].val;
        }
        root = merge(lt, rt);
        return res;
    }

    T getsuc(int &root, T val) {
        int lt = 0, rt = 0;
        split(root, val, lt, rt);
        T res = numeric_limits<T>::max();
        if (rt) {
            int suc = getval(rt, 1);
            res = fhq[suc].val;
        }
        root = merge(lt, rt);
        return res;
    }

    void build(int cur, int s, int t) {
        for (int i = s; i <= t; i ++) {
            insert(seg[cur], vec[i]);
        }
        if (s == t) {
            return;
        }
        int mid = (s + t) / 2;
        build(lc, s, mid);
        build(rc, mid + 1, t);
    }

    void update(int pos, T val) {
        update(1, 1, n, pos, val);
        vec[pos] = val;
    }

    void update(int cur, int s, int t, int pos, T val) {
        erase(seg[cur], vec[pos]);
        insert(seg[cur], val);
        if (s == t) {
            return;
        }
        int mid = (s + t) / 2;
        if (pos <= mid) {
            update(lc, s, mid, pos, val);
        } else {
            update(rc, mid + 1, t, pos, val);
        }
    }

    int queryrank(int lo, int ro, T val) {
        return queryrank(1, 1, n, lo, ro, val) + 1;
    }

    int queryrank(int cur, int s, int t, int lo, int ro, T val) {
        if (lo <= s && t <= ro) {
            return getrank(seg[cur], val) - 1;
        }
        int mid = (s + t) / 2, res = 0;
        if (lo <= mid) {
            res += queryrank(lc, s, mid, lo, ro, val);
        }
        if (ro > mid) {
            res += queryrank(rc, mid + 1, t, lo, ro, val);
        }
        return res;
    }

    T queryval(int lo, int ro, int rk) {
        return queryval(1, 1, n, lo, ro, rk);
    }

    T queryval(int cur, int s, int t, int lo, int ro, int rk) {
        int l = 0, r = 1e8 + 1, ans = -1;
        while (l + 1 < r) {
            int mid = l + (r - l) / 2;
            if (queryrank(1, 1, n, lo, ro, mid) + 1 <= rk) {
                l = mid;
            } else {
                r = mid;
            }
        }
        return l;
    }

    T querypre(int lo, int ro, T val) {
        return querypre(1, 1, n, lo, ro, val);
    }

    T querypre(int cur, int s, int t, int lo, int ro, T val) {
        if (lo <= s && t <= ro) {
            return getpre(seg[cur], val);
        }
        int mid = (s + t) / 2;
        T res = -numeric_limits<T>::max();
        if (lo <= mid) {
            cmax(res, querypre(lc, s, mid, lo, ro, val));
        }
        if (ro > mid) {
            cmax(res, querypre(rc, mid + 1, t, lo, ro, val));
        }
        return res;
    }

    T querysuc(int lo, int ro, T val) {
        return querysuc(1, 1, n, lo, ro, val);
    }

    T querysuc(int cur, int s, int t, int lo, int ro, T val) {
        if (lo <= s && t <= ro) {
            return getsuc(seg[cur], val);
        }
        int mid = (s + t) / 2;
        T res = numeric_limits<T>::max();
        if (lo <= mid) {
            cmin(res, querysuc(lc, s, mid, lo, ro, val));
        }
        if (ro > mid) {
            cmin(res, querysuc(rc, mid + 1, t, lo, ro, val));
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> vec(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> vec[i];
    }

    SegmentTreeWithFhqTreap<int> segfhq(n, vec);

    while (m --) {
        int opt;
        cin >> opt;
        if (opt == 1) {
            int x, y, k;
            cin >> x >> y >> k;
            cout << segfhq.queryrank(x, y, k) << '\n';
        }
        if (opt == 2) {
            int x, y, k;
            cin >> x >> y >> k;
            cout << segfhq.queryval(x, y, k) << '\n';
        }
        if (opt == 3) {
            int x, k;
            cin >> x >> k;
            segfhq.update(x, k);
        }
        if (opt == 4) {
            int x, y, k;
            cin >> x >> y >> k;
            cout << segfhq.querypre(x, y, k) << '\n';
        }
        if (opt == 5) {
            int x, y, k;
            cin >> x >> y >> k;
            cout << segfhq.querysuc(x, y, k) << '\n';
        }
    }

    return 0;
}