#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    string s;
    cin >> s;

    s = ' ' + s;

    int a = 0, b = 0, c = 0;
    i64 xx = 0, yy = 0, zz = 0, sum = 0;
    vector<int> x(2 * n + 1), y(2 * n + 1), z(2 * n + 1);
    map<pair<int, int>, int> mp;
    x[n] = 1;
    y[n] = 1;
    z[n] = 1;
    mp[{0, 0}] = 1;
    for (int i = 1; i <= n; i ++) {
        a += s[i] == 'A';
        b += s[i] == 'B';
        c += s[i] == 'C';
        xx += x[a - b + n];
        yy += y[a - c + n];
        zz += z[b - c + n];
        sum += mp[{a - b, a - c}];
        x[a - b + n] ++;
        y[a - c + n] ++;
        z[b - c + n] ++;
        mp[{a - b, a - c}] ++;
    }

    i64 ans = n * (n + 1ll) / 2 - xx - yy - zz + 2 * sum;

    cout << ans << '\n';

    return 0;
}