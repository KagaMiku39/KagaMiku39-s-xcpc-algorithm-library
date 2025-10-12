#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

using i64 = long long;
using u64 = unsigned long long;

struct SegmentTree {
    #define lc 2 * cur
    #define rc 2 * cur + 1

    int n;
    
    vector<int> x, y, tag, vec;

    struct Node {
        int cnt, len, sum;

        array<bool, 2> tag;
    };
    vector<Node> seg;

    SegmentTree(int n) : n(n), x(2 * n + 1), y(2 * n + 1), tag(2 * n + 1), vec{}, seg(16 * (n + 1)) {}
    
    
    struct Hash {
        inline static u64 rnd{mt19937_64(chrono::steady_clock::now().time_since_epoch().count())()};

        size_t operator () (const int &x) const{
            return x ^ rnd;
        }
    };
    
    void pushup(int cur, int lo, int ro) {
        if(seg[cur].cnt) {
            seg[cur].len = vec[ro + 1] - vec[lo];
            seg[cur].sum = 2;
            seg[cur].tag.fill(true);
        } else {
            // if (lo == ro) {
            //     return;
            // } else {
            //     seg[cur].len = seg[lc].len + seg[rc].len;
            // }
            seg[cur].len = seg[lc].len + seg[rc].len;
            seg[cur].sum = seg[lc].sum + seg[rc].sum;
            seg[cur].tag[0] = seg[lc].tag[0];
            seg[cur].tag[1] = seg[rc].tag[1];
            if (seg[lc].tag[1] & seg[rc].tag[0]) {
                seg[cur].sum -= 2;
            }
        }
    }

    void modify(int cur, int s, int t, int lo, int ro, int val) {
        if (lo > t || ro < s) return;
        if (lo <= s && t <= ro) {
            seg[cur].cnt += val;
            pushup(cur, s, t);
            return;
        }
        int mid = (s + t) / 2;
        if (lo <= mid) {
            modify(lc, s, mid, lo, ro, val);
        }
        if (ro > mid) {
            modify(rc, mid + 1, t, lo, ro, val);
        }
        pushup(cur, s, t);
    }
      
    void solve() { 
        for (int i = 1; i <= n; i ++) {
            cin >> x[i] >> y[i] >> x[i + n] >> y[i + n];
            tag[i] = 1;
            tag[n + i] = -1;
        }

        vector<int> id(2 * n + 1);
        
        iota(begin(id), end(id), 0);

        sort(next(begin(id)), end(id), [&](const int &a, const int &b) {
            return tie(y[a], tag[b]) < tie(y[b], tag[a]);
        });
        
        vec = x;
        
        sort(next(begin(vec)), end(vec));

        vec.erase(unique(next(begin(vec)), end(vec)), end(vec));

        unordered_map<int, int, Hash> ump; 
        for (int i = 1; i < ssize(vec); i ++) {
            ump[vec[i]] = i;
        }

        int ans = 0, last = 0;
        for (int i = 1; i <= 2 * n; i ++) {
            int j = id[i], lo = 0, ro = 0;
            if (j > n) {
                lo = x[j - n], ro = x[j];
            } else {
                lo = x[j], ro = x[j + n];
            }
            if (i == 2 * n) {
                ans += ro - lo; 
                break;
            }
            int k = id[i + 1];
            modify(1, 1, ssize(vec) - 2, ump[lo], ump[ro] - 1, tag[j]);
            ans += abs(seg[1].len - last);
            last = seg[1].len;
            ans += seg[1].sum * (y[k] - y[j]);
        }

        cout << ans << '\n';
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    
    SegmentTree seg(n);
    
    seg.solve();

    return 0;
}