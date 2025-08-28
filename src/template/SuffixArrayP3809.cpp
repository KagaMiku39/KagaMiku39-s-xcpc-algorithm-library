#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

using i64 = long long;

template<typename T>
bool cmax(T &a, const T &b) {
    return a < b ? a = b, true : false;
}

struct SuffixArray {
    string s;

    int n, m;

    vector<int> x, y, c, sa, rk, hei;

    SuffixArray(const string& str) : s(" " + str), n(ssize(str)), m(122), x(n + 1), y(n + 1), c(max(n, m) + 1), sa(n + 1), rk(n + 1), hei(n + 1) {}

    void getsa() {
        int i = 0, k = 0;
        for (i = 1; i <= m; i ++) {
            c[i] = 0;
        }
        for (i = 1; i <= n; i ++) {
            c[x[i] = s[i]] ++;
        }
        for (i = 1; i <= m; i ++) {
            c[i] += c[i - 1];
        }
        for (i = n; i; i --) {
            sa[c[x[i]] --] = i;
        }
        for (k = 1; k <= n; k <<= 1) {
            int p = 0;
            for (i = n - k + 1; i <= n; i ++) {
                y[++ p] = i;
            }
            for (i = 1; i <= n; i ++) {
                if (sa[i] > k) {
                    y[++ p] = sa[i] - k;
                }
            }
            for (i = 1; i <= m; i ++) {
                c[i] = 0;
            }
            for (i = 1; i <= n; i ++) {
                c[x[y[i]]] ++;
            }
            for (i = 1; i <= m; i ++) {
                c[i] += c[i - 1];
            }
            for (i = n; i; i --) {
                sa[c[x[y[i]]] --] = y[i];
            }
            for (i = 1; i <= n; i ++) {
                y[i] = x[i];
            }
            m = 0;
            x[sa[1]] = ++ m;
            for (i = 2; i <= n; i ++) {
                x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && (sa[i] + k <= n ? y[sa[i] + k] : 0) == (sa[i - 1] + k <= n ? y[sa[i - 1] + k] : 0)) ? m : ++ m;
            }
            if (m == n) {
                break;
            }
        }
    }

    void gethei() {
        int i = 0, k = 0;
        for (i = 1; i <= n; i ++) {
            rk[sa[i]] = i;
        }
        for (i = 1, k = 0; i <= n; i ++) {
            if (rk[i] == 1) {
                continue;
            }
            if (k) {
                k --;
            }
            int j = sa[rk[i] - 1];
            while (i + k <= n && j + k <= n && s[i + k] == s[j + k]) {
                k ++;
            }
            hei[rk[i]] = k;
        }
    }

    void build() {
        getsa();
        gethei();
    }
   
    void solve() {
        build();
        for (int i = 1; i <= n; i ++) {
            cout << sa[i] << " \n"[i == n];
        }
        // for (int i = 1; i <= n; i ++) {
        //     cout << hei[i] << " \n"[i == n];
        // }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
   
    string s;
    cin >> s;

    SuffixArray sa(s);
    sa.solve();

    return 0;
}