#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

using u64 = unsigned long long;

constexpr int p = 131;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<string> s(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> s[i];
        s[i] = ' ' + s[i];
    }
    
    auto gethash = [&](string str) {
        u64 res = 0;
        for (int i = 1; i < ssize(str); i ++) {
            res = res * p + str[i];
        }
        return res;
    };

    vector<int> h(n + 1);
    for (int i = 1; i <= n; i ++) {
        h[i] = gethash(s[i]);
    }

    sort(next(begin(h)), end(h));

    h.erase(unique(next(begin(h)), end(h)), end(h)); 

    cout << ssize(h) - 1 << '\n';

    return 0;
}