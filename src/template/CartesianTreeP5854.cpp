#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

using i64 = long long;

void solve() {
    int n;
    cin >> n;
    
    vector<i64> vec(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> vec[i];
    }
    
    vector<int> stk;
    vector<i64> l(n + 1), r(n + 1);
    for (int i = 1; i <= n; i ++) {
        int last = 0;
        while (ssize(stk) && vec[stk.back()] > vec[i]) {
            last = stk.back();
            stk.pop_back();
        }
        if (ssize(stk)) {
            r[stk.back()] = i;
        }
        if (last) {
            l[i] = last;
        }
        stk.emplace_back(i);
    }
    
    i64 ans[2]{};
    for (int i = 1; i <= n; i ++) {
        ans[0] ^= 1ll * i * (l[i] + 1);
        ans[1] ^= 1ll * i * (r[i] + 1);
    }
    
    cout << ans[0] << ' ' << ans[1] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}