#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s[2];
    cin >> s[0] >> s[1];
    s[0] = ' ' + s[0];
    s[1] = ' ' + s[1];

    vector<int> nx(ssize(s[0]));
    for (int i = 2, dp = 0; i < ssize(s[1]); i ++) {
        while (dp && s[1][i] != s[1][dp + 1]) {
            dp = nx[dp];
        }
        dp += s[1][i] == s[1][dp + 1];
        nx[i] = dp;
    }

    for (int i = 1, dp = 0; i < ssize(s[0]); i ++) {
        while (dp && s[0][i] != s[1][dp + 1]) {
            dp = nx[dp];
        }
        dp += s[0][i] == s[1][dp + 1];
        if (dp + 1 == ssize(s[1])) {
            cout << i - dp + 1 << '\n';
            dp = nx[dp];
        }
    }

    for (int i = 1; i < ssize(s[1]); i ++) {
        cout << nx[i] << " \n"[i + 1 == ssize(s[1])];
    }

    return 0;
}