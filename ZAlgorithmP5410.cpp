#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

using i64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string t, s;
    cin >> t >> s;
    s = ' ' + s;
    t = ' ' + t;
    
    vector<int> z(ssize(s));
    z[1] = ssize(s) - 1;
    for (int i = 2, lo = 0, ro = 0; i < ssize(s); i ++) {
        if (i <= ro) {
            z[i] = min(z[i - lo + 1], ro - i + 1);
        }
        while (i + z[i] < ssize(s) && s[1 + z[i]] == s[i + z[i]]) {
            z[i] ++;
        }
        if (i + z[i] - 1 > ro) {
            lo = i;
            ro = i + z[i] - 1;
        }
    }
    
    vector<int> p(ssize(t));
    for (int i = 1, lo = 0, ro = 0; i < ssize(t); i ++) {
        if (i <= ro) {
            p[i] = min(z[i - lo + 1], ro - i + 1);
        }
        while (i + p[i] < ssize(t) && 1 + p[i] < ssize(s) && s[1 + p[i]] == t[i + p[i]]) {
            p[i] ++;
        }
        if (i + p[i] - 1 > ro) {
            lo = i;
            ro = i + p[i] - 1;
        }
    }

    i64 ans[2]{};
    for (int i = 1; i < ssize(s); i ++) {
        ans[0] ^= 1ll * i * (z[i] + 1);
    }
    for (int i = 1; i < ssize(t); i ++) {
        ans[1] ^= 1ll * i * (p[i] + 1);
    }
    
    cout << ans[0] << '\n' << ans[1] << '\n';

    return 0;
}