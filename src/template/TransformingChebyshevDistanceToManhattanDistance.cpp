#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

using i64 = long long;
using u64 = unsigned long long; 

template<typename T>
bool cmin(T &a, const T &b) {
    return a > b ? a = b, true : false;
}

template<typename T>
bool cmax(T &a, const T &b) {
    return a < b ? a = b, true : false;
}

const int mod = 1e9 + 7, inv = 5e8 + 4;

void solve() {   
    int n;
    cin >> n;

    vector<int> x(n + 1), y(n + 1), a(n + 1);
    for (int i = 1; i <= n; i ++) {
        int tx, ty;
        cin >> tx >> ty >> a[i];
        x[i] = tx + ty;
        y[i] = tx - ty;
        // 记得反过来不用除以2由于少一个字（
    }

    vector<int> id(n + 1);
    iota(begin(id), end(id), 0);
    
    sort(next(begin(id)), end(id), [&](const int &l, const int &r) {
        return x[l] < x[r];
    });
    
    int ans = 0, sum = 0, pre = 0;
    for (int i = 1; i <= n; i ++) {
        int j = id[i];
        sum = (1ll * sum + x[j]) % mod;
    }
    for (int i = 1; i <= n; i ++) {
        int j = id[i];
        ans = (ans + a[j] * (((2ll * i - n - 2) * x[j] + sum - 2 * pre) % mod) % mod) % mod;
        pre = (1ll * pre + x[j]) % mod;
    }
    
    sort(next(begin(id)), end(id), [&](const int &l, const int &r) {
        return y[l] < y[r];
    });
    
    sum = 0, pre = 0;
    for (int i = 1; i <= n; i ++) {
        int j = id[i];
        sum = (1ll * sum + y[j]) % mod;
    }
    for (int i = 1; i <= n; i ++) {
        int j = id[i];
        ans = (ans + a[j] * (((2ll * i - n - 2) * y[j] + sum - 2 * pre) % mod) % mod) % mod;
        pre = (1ll * pre + y[j]) % mod;
    }
    ans = (1ll * ans * inv % mod + mod) % mod;
    
    cout << ans << '\n';
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