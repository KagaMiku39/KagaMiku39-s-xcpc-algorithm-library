#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

using i64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

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
    
    i64 ans1 = 0, ans2 = 0;
    for (int i = 1; i <= n; i ++) {
        ans1 ^= 1ll * i * (l[i] + 1);
        ans2 ^= 1ll * i * (r[i] + 1);
    }
    
    cout << ans1 << ' ' << ans2 << '\n';

    return 0;
}