#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

#define lc(x) hjt[x].ch[0]
#define rc(x) hjt[x].ch[1]

struct PersistentSegmentTree {
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
    
    void append(int val) {
        rt.emplace_back(insert(rt.back(), 0, 1e9, val));
    }

    void pushup(int cur) {
        hjt[cur].cnt = hjt[lc(cur)].cnt + hjt[rc(cur)].cnt; 
    }
    
    int insert(int last, int s, int t, int val) {
        int now = ++ idx;
        hjt.emplace_back(hjt[last]);
        if (s == t) {
            hjt[now].cnt ++;
            return now; 
        }
        int mid = s + (t - s) / 2;
        if (val > mid) {
            rc(now) = insert(rc(last), mid + 1, t, val); 
        }else {
            lc(now) = insert(lc(last), s, mid, val);
        }
        pushup(now);
        return now;
    }

    int query(int ro, int lo, int rk) {
        return query(rt[ro], rt[lo], 0, 1e9, rk);
    }

    int query(int ro, int lo, int s, int t, int rk) {
        if (s == t) {
            return s;
        }
        int mid = s + (t - s) / 2, cnt = hjt[lc(ro)].cnt - hjt[lc(lo)].cnt;
        if (rk > cnt) {
            return query(rc(ro), rc(lo), mid + 1, t, rk - cnt);
        }else {
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
    PersistentSegmentTree hjt;
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
        hjt.append(a[i]);
    }   
     
    while (m --) {
        int l, r, k;
        cin >> l >> r >> k;
        cout << hjt.query(r, l - 1, k) << '\n';
    }

    return 0;
}