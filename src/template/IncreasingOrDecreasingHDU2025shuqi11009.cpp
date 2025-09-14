#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long; 
using i128 = __int128; 

template<typename T>
bool cmin(T &a, const T &b) {
    return a > b ? a = b, true : false;
}

template<typename T>
bool cmax(T &a, const T &b) {
    return a < b ? a = b, true : false;
}

void solve() {   
    int n;
    cin >> n;

    vector<int> vec(n + 1), id(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> vec[i];
        id[vec[i]] = i;
    }

    int ans = 1, lo = id[n], ro = id[n]; 
    for (int i = n - 1; i; i --) {
        cmin(lo, id[i]);
        cmax(ro, id[i]);
        cmax(ans, ro - lo + 1 - n + i + 1);
    }

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