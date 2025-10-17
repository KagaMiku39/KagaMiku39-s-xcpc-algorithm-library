#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

template<typename T>
struct ChtollyTree {
    map<int, T> odt;

    ChtollyTree(int n, const vector<T> &vec) {
        odt[0] = 0; 
        for (int i = 1; i <= n; i ++) {
            odt[i] = vec[i];
        }
        odt[n + 1] = 0;
    }

    auto split(int pos) {
        auto it = prev(odt.upper_bound(pos));
        if (it -> first == pos) {
            return it;
        }
        odt[pos] = it -> second;
        return odt.find(pos);
    }

    void assign(int lo, int ro, T val) {
        auto itl = split(lo), itr = split(ro + 1);
        odt.erase(itl, itr);
        odt[lo] = val;
    }

    void add(int lo, int ro, T val) {
        auto itl = split(lo), itr = split(ro + 1);
        for (; itl != itr; itl ++) {
            itl -> second += val;
        }
    }

    T getval(int lo, int ro, int k) {
        auto itl = split(lo), itr = split(ro + 1);
        vector<pair<i64, int>> vec;
        for (auto it = itl; it != itr; it ++) {
            vec.emplace_back(it -> second, next(it) -> first - it -> first);
        }
        sort(begin(vec), end(vec));
        for (auto &[val, cnt] : vec) {
            k -= cnt;
            if (k <= 0) {
                return val;
            }
        }
        return -1;
    }

    T getpowsum(int lo, int ro, int x, int mod) {
        int sum = 0;
        auto itl = split(lo), itr = split(ro + 1);
        auto binpow = [&](T a, int b) {
            int res = 1 % mod;
            a %= mod;
            while (b) {
                if (b & 1) {
                    res = res * a % mod;
                }
                a = a * a % mod;
                b /= 2;
            }
            return res;
        };
        for (auto it = itl; it != itr; it ++) {
            int len = next(it) -> first - it -> first;
            sum = (sum + 1ll * binpow(it -> second, x) * len % mod) % mod;
        }
        return sum;
    }
};

const int maxn = 1e5 + 3;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, seed, vmax;
    cin >> n >> m >> seed >> vmax;

    auto rnd = [&]() {
        int ret = seed;
        seed = (seed * 7ll + 13) % 1000000007;
        return ret;
    };

    vector<i64> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        a[i] = rnd() % vmax + 1;
    }

    ChtollyTree<i64> odt(n, a);

    while (m --) {
        int opt = rnd() % 4 + 1, l = rnd() % n + 1, r = rnd() % n + 1;   
        if (l > r) {
            swap(l, r);
        }
        if (opt == 1) {
            int x = rnd() % vmax + 1;
            odt.add(l, r, x);
        }
        if (opt == 2) {
            int x = rnd() % vmax + 1;
            odt.assign(l, r, x);
        } 
        if (opt == 3) {
            int x = rnd() % (r - l + 1) + 1;
            cout << odt.getval(l, r, x) << '\n';
        }
        if (opt == 4) {
            int x = rnd() % vmax + 1, y = rnd() % vmax + 1;
            cout << odt.getpowsum(l, r, x, y) << '\n';
        }
    }
    
    return 0;
}