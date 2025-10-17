#include <bits/stdc++.h>

using namespace std;

struct SegmentTreeWithSegmentTree {
    int k, rtx{}, idxx{}, idxy{};

    struct NodeX {
        int rty{};
        
        array<int, 2> ch{};
    };
    vector<NodeX> segx;
    
    struct NodeY {
        int sum;

        array<int, 2> ch;
    };
    vector<NodeY> segy;

    SegmentTreeWithSegmentTree(int n, int mx) : k(mx), segx(20 * n), segy(200 * n) {}

    void updatey(int &cur, int s, int t, int c) {
        if (!cur) {
            cur = ++ idxy;
        }
        segy[cur].sum ++;
        if (s == t) {
            return;
        }
        int mid = s + (t - s) / 2;
        if (c <= mid) {
            updatey(segy[cur].ch[0], s, mid, c);
        } else {
            updatey(segy[cur].ch[1], mid + 1, t, c);
        }
    }

    void updatex(int & cur, int s, int t, tuple<int, int, int> &ele) {
        if (!cur) {
            cur = ++ idxx;
        }
        updatey(segx[cur].rty, 1, k, get<2>(ele));
        if (s == t) {
            return;
        }
        int mid = s + (t - s) / 2;
        if (get<1>(ele) <= mid) {
            updatex(segx[cur].ch[0], s, mid, ele);
        } else {
            updatex(segx[cur].ch[1], mid + 1, t, ele);
        }
    }

    int gety(int cur, int s, int t, int mxc) {
        if (!cur || mxc == 0) {
            return 0;
        }
        if (t <= mxc) {
            return segy[cur].sum;
        }
        int mid = s + (t - s) / 2;
        int res = gety(segy[cur].ch[0], s, mid, mxc);
        if (mxc > mid) {
            res += gety(segy[cur].ch[1], mid + 1, t, mxc);
        }
        return res;
    }

    int getx(int cur, int s, int t, int mxb, int mxc) {
        if (!cur || mxb == 0) {
            return 0;
        }
        if (t <= mxb) {
            return gety(segx[cur].rty, 1, k, mxc);
        }
        int mid = s + (t - s) / 2,  
            res = getx(segx[cur].ch[0], s, mid, mxb, mxc);
        if (mxb > mid) {
            res += getx(segx[cur].ch[1], mid + 1, t, mxb, mxc);
        }
        return res;
    }

    void add(tuple<int, int, int> &ele) {
        updatex(rtx, 1, k, ele);
    }

    int query(int b, int c) {
        return getx(rtx, 1, k, b, c);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<tuple<int, int, int>> ele(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> get<0>(ele[i]) >> get<1>(ele[i]) >> get<2>(ele[i]);
    }

    sort(next(begin(ele)), end(ele));

    SegmentTreeWithSegmentTree seg2d(n, k);
    
    int last = 1;
    vector<int> ans(n + 1);
    for (int i = 1; i <= n; i ++) {
        seg2d.add(ele[i]);
        if (i == n || get<0>(ele[i]) != get<0>(ele[i + 1])) {
            for (int j = last; j <= i; ++j) {
                int cnt = seg2d.query(get<1>(ele[j]), get<2>(ele[j]));
                if (cnt > 0) {
                   ans[cnt] ++;
                }
            }
            last = i + 1;
        }
    }

    for (int i = 1; i <= n; i ++) {
        cout << ans[i] << "\n";
    }

    return 0;
}