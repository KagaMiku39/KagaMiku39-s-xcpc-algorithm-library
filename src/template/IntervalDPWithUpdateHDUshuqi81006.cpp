#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

template<typename T>
bool cmax(T &a, const T &b) {
    return a < b ? a = b, true : false;
}

template<typename T>
struct SegmentTree {
    #define lc 2 * cur
    #define rc 2 * cur + 1

    int n;
    
    vector<T> vec, seg;

    SegmentTree(int n, const vector<T> &vec) : n(n), vec(vec), seg(4 * n) {
        build(1, 1, n);
    }
    
    void pushup(int cur) {
        seg[cur] = T(seg[lc], seg[rc]);
    }

    void build(int cur, int s, int t) {
        if (s == t) {
            seg[cur] = vec[s];
            return;
        }
        int mid = (s + t) / 2;
        build(lc, s, mid);
        build(rc, mid + 1, t);
        pushup(cur);
    }
    
    void modify(int pos, int val) {
        modify(1, 1, n, pos, val);
    }

    void modify(int cur, int s, int t, int pos, int val) {
        if (s == t) {
            seg[cur].mat[1][1] = val;
            return; 
        }
        int mid = (s + t) / 2; 
        if (pos > mid) {
            modify(rc, mid + 1, t, pos, val);
        } else {
            modify(lc, s, mid, pos, val);
        }
        pushup(cur);
    }

    i64 query() {
        i64 res = 0;
        for (int i = 0; i <= 3; i ++) {
            for (int j = 0; i + j <= 3; j ++) {
                cmax(res, seg[1].mat[i][j]);
            }
        }
        return res;
    }
};

struct Node {
    int len{};
    
    array<array<i64, 4>, 4> mat{}; 
        
    Node() {} 
    
    Node(int val) : len(1) {
        mat[1][1] = val;
    }
    
    Node(Node &ln, Node &rn) {
        for (int i = 0; i <= min(ln.len, 3); i ++) {
            for (int j = 0; j <= min(rn.len, 3); j ++) {
                if (i == ln.len && j == rn.len) {
                    if (i + j > 3) {
                        continue;
                    }
                    mat[i + j][i + j] = ln.mat[i][i] + rn.mat[j][j];
                } else if (i == ln.len) {
                    for (int k = 0; k <= min(3 - i, rn.len - 1 - j); k ++) {
                        cmax(mat[i + k][j], ln.mat[i][i] + rn.mat[k][j]);
                    }
                } else if (j == rn.len) {
                    for (int k = 0; k <= min(3 - j, ln.len - 1 - i); k ++) {
                        cmax(mat[i][j + k], ln.mat[i][k] + rn.mat[j][j]);
                    }
                } else {
                    i64 mx = 0;
                    for (int k = 3; ~k; k --) {
                        cmax(mx, rn.mat[3 - k][j]);
                        cmax(mat[i][j], mx + ln.mat[i][k]);
                    }
                }
            }
        }
        len = ln.len + rn.len;
    }
};

void solve() {   
    int n, q;
    cin >> n >> q;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }
    
    vector<Node> vec{{}};

    for (int i = 1; i <= n; i ++) {
        vec.emplace_back(a[i]);
    }
    
    SegmentTree<Node> seg(n, vec); 

    cout << seg.query() << '\n';
    
    while (q --) {
        int x, v;
        cin >> x >> v;
        seg.modify(x, v);
        cout << seg.query() << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t --) {
        solve();
    }

    return 0;
}