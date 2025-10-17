#include <bits/stdc++.h>

using namespace std;

template<typename T>
struct PersistentSegmentTree {
    #define lc(x) hjt[x].ch[0]
    #define rc(x) hjt[x].ch[1]

    int n, idx{};
    
    vector<int> rt, vec;
    
    struct Node{
        T val; 

        array<int, 2> ch;
    };
    vector<Node> hjt;
    
    // PersistentSegmentTree(int n, vector<int> &vec) : n(n), vec(vec) {
    //     rt.emplace_back(build(1, n));
    //     hjt.emplace_back();
    // }

    PersistentSegmentTree(int n, int m, const vector<int> &vec) : n(n), hjt(2 * n + 21 * m), vec(vec), rt(m + 1) {
        build(rt[0], 1, n);
    }

    // int build(int s, int t) {
    void build(int &cur, int s, int t) {
        // int cur = ++ idx;
        // hjt.emplace_back();
        cur = ++ idx;
        if (s == t) {
            hjt[cur].val = vec[s];
            // return cur; 
            return;
        }
        int mid = (s + t) / 2;
        // lc(cur) = build(s, mid);
        build(lc(cur), s, mid);
        // rc(cur) = build(mid + 1, t); 
        build(rc(cur), mid + 1, t);
        // return cur;
    }

    void modify(int id, int ver, int pos, T val) {
        // rt.emplace_back(update(rt[ver], 1, n, pos, val));
        update(rt[id], rt[ver], 1, n, pos, val);
    }
    
    // int update(int last, int s, int t, int pos, T val) {
    void update(int &now, int last, int s, int t, int pos, T val) {
        // int now = ++ idx;
        // hjt.emplace_back(hjt[last]);
        now = ++ idx;
        hjt[now] = hjt[last];
        if (s == t) {
            hjt[now].val = val;
            // return now; 
            return;
        }
        int mid = (s + t) / 2;
        if (pos > mid) {
            // rc(now) = update(rc(last), mid + 1, t, pos, val); 
            update(rc(now), rc(last), mid + 1, t, pos, val);
        } else {
            // lc(now) = update(lc(last), s, mid, pos, val);
            update(lc(now), lc(last), s, mid, pos, val);
        }
        // return now;
    }

    // T query(int ver, int pos) {
    T query(int id, int ver, int pos) {
        // rt.emplace_back(rt[ver]);
        rt[id] = rt[ver];
        return query(rt[ver], 1, n, pos);
    }

    T query(int cur, int s, int t, int pos) {
        if (s == t) {
            return hjt[cur].val;
        }
        int mid = (s + t) / 2;
        if (pos > mid) {
            return query(rc(cur), mid + 1, t, pos);
        } else {
            return query(lc(cur), s, mid, pos);
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }

    // PersistentSegmentTree<int> hjt(n, a);
    
    PersistentSegmentTree<int> hjt(n, m, a);

    // while (m --) {
    //     int v, opt;
    //     cin >> v >> opt;
    //     if (opt == 1) {
    //         int p, c;
    //         cin >> p >> c;
    //         hjt.modify(v, p, c);
    //     }
    //     if (opt == 2) {
    //         int p;
    //         cin >> p;
    //         cout << hjt.query(v, p) << '\n';
    //     }
    // }

    for (int i = 1; i <= m; i ++) {
        int v, opt;
        cin >> v >> opt;
        if (opt == 1) {
            int p, c;
            cin >> p >> c;
            hjt.modify(i, v, p, c);
        }
        if (opt == 2) {
            int p;
            cin >> p;
            cout << hjt.query(i, v, p) << '\n';
        }
    }

    return 0;
}