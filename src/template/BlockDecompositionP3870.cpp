#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

struct SqrtDecomposition {
    int n, sq;

    struct Node {
        int val, bel;
    };
    vector<Node> vec;
    
    struct Block {
        int lo, ro, sz, tag, cnt;
    };
    vector<Block> sd;

    SqrtDecomposition(int n) : n(n), sq(sqrt(n)), vec(n + 1), sd((n + sq - 1) / sq + 1) {
        for (int i = 1; i < ssize(sd); i ++) {
            auto &[lo, ro, sz, _, __] = sd[i];
            lo = (i - 1) * sq + 1;
            ro = i + 1 != ssize(sd) ? i * sq : n;
            sz = ro - lo + 1;
            for (int j = lo; j <= ro; j ++) {
                vec[j].bel = i;
            }
        }
    }
    
    void update(int lo, int ro) {
        if (vec[lo].bel == vec[ro].bel) {
            Block &tmp = sd[vec[lo].bel];
            for (int i = lo; i <= ro; i ++) {
                tmp.cnt += vec[i].val ^ tmp.tag ? -1 : 1;
                vec[i].val ^= 1;
            }
        }else {
            Block &a = sd[vec[lo].bel], &b = sd[vec[ro].bel];
            for (int i = lo; i <= a.ro; i ++) {
                a.cnt += vec[i].val ^ a.tag ? -1 : 1;
                vec[i].val ^= 1;
            }
            for (int i = b.lo; i <= ro; i ++) {
                b.cnt += vec[i].val ^ b.tag ? -1 : 1;
                vec[i].val ^= 1;
            }
            for (int i = vec[lo].bel + 1; i < vec[ro].bel; i ++) {
                sd[i].cnt = sd[i].sz - sd[i].cnt;
                sd[i].tag ^= 1;
            }
        }
    }

    int query(int lo, int ro) {
        int res = 0;
        if (vec[lo].bel == vec[ro].bel) {
            Block &tmp = sd[vec[lo].bel];
            for (int i = lo; i <= ro; i ++) {
                res += vec[i].val ^ tmp.tag;
            }
        }else {
            Block &a = sd[vec[lo].bel], &b = sd[vec[ro].bel];
            for (int i = lo; i <= a.ro; i ++) {
                res += vec[i].val ^ a.tag;
            }
            for (int i = b.lo; i <= ro; i ++) {
                res += vec[i].val ^ b.tag;
            }
            for (int i = vec[lo].bel + 1; i < vec[ro].bel; i ++) {
                res += sd[i].cnt;
            }
        }
        return res; 
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    SqrtDecomposition sd(n);

    while (m --) {
        int c, a, b;
        cin >> c >> a >> b;
        if (c == 0) {
            sd.update(a, b);
        }
        if (c == 1) {
            cout << sd.query(a, b) << '\n';
        }
    }

    return 0;
}