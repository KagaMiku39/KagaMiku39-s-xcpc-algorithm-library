#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

template<typename T>
struct PersistentSegmentTree {
    #define lc(x) hjt[x].ch[0]
    #define rc(x) hjt[x].ch[1]
    
    int idx{};
    
    vector<int> rt;
    
    struct Node{
        int cnt;
        
        array<int, 2> ch;
    };
    vector<Node> hjt;
    
    PersistentSegmentTree() {
        rt.emplace_back();
        hjt.emplace_back();
    }

    // PersistentSegmentTree(int n) : hjt(32 * n), rt(n + 1) {}
    
    void append(T val) {
    // void append(int ver, T val) {
    //     insert(rt[ver], rt[ver - 1], 0, 1e9, val);
        rt.emplace_back(insert(rt.back(), 0, 1e9, val));
    }

    void pushup(int cur) {
        hjt[cur].cnt = hjt[lc(cur)].cnt + hjt[rc(cur)].cnt; 
    }
    
    int insert(int last, int s, int t, T val) {
    // void insert(int &now, int last, int s, int t, int val) {
        int now = ++ idx;
        hjt.emplace_back(hjt[last]);
        // now = ++ idx
        // hjt[now] = hjt[last];
        if (s == t) {
            hjt[now].cnt ++;
            return now; 
            // return;
        }
        int mid = (s + t) / 2;
        if (val > mid) {
            rc(now) = insert(rc(last), mid + 1, t, val); 
            // insert(rc(now), rc(last), mid + 1, t, val);
        } else {
            lc(now) = insert(lc(last), s, mid, val);
            // insert(lc(now), lc(last), s, mid, val);
        }
        pushup(now);
        return now;
    }

    T query(int lo, int ro, int rk) {
        return query(rt[ro], rt[lo - 1], 0, 1e9, rk);
    }

    T query(int ro, int lo, int s, int t, int rk) {
        if (s == t) {
            return s;
        }
        int mid = (s + t) / 2, cnt = hjt[lc(ro)].cnt - hjt[lc(lo)].cnt;
        if (rk > cnt) {
            return query(rc(ro), rc(lo), mid + 1, t, rk - cnt);
        } else {
            return query(lc(ro), lc(lo), s, mid, rk);
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    
    vector<int> a(n + 1);
    PersistentSegmentTree<int> hjt;
    // PersistentSegmentTree<int> hjt(n);
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
        hjt.append(a[i]);
        // hjt.append(i, a[i]);
    }
     
    while (m --) {
        int l, r, k;
        cin >> l >> r >> k;
        cout << hjt.query(l, r, k) << '\n';
    }

    return 0;
}