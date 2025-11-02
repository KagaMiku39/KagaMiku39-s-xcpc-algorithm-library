#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

using u64 = unsigned long long;

constexpr int p = 13331;

constexpr int maxn = 1e5 + 1;

u64 po[maxn];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;

    string s;
    cin >> s;

    s = ' ' + s;

    po[0] = 1;
    for (int i = 1; i < maxn; i ++) {
        po[i] = po[i - 1] * p;
    }
    
    vector<u64> h(n + 1);
    auto gethash = [&](string s, vector<u64> &h) {
        for (int i = 1; i < ssize(s); i ++) {
            h[i] = h[i - 1] * p + s[i];
        }
    };
    gethash(s, h);

    auto query = [&](int lo, int ro) {
        return h[ro] - h[lo - 1] * po[ro - lo + 1]; 
    };

    while (m --) {
        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;
        cout << (query(l1, r1) == query(l2, r2) ? "Yes\n" : "No\n");
    }

    return 0;
}