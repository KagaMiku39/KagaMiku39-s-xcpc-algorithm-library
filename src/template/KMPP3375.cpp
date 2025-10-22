#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s1, s2;
    cin >> s1 >> s2;

    s1 = ' ' + s1;
    s2 = ' ' + s2;

    vector<int> nx(ssize(s2));
    for (int i = 2, dp = 0; i < ssize(s2); i ++) {
        while (dp && s2[i] != s2[dp + 1]) {
            dp = nx[dp];
        }
        dp += s2[i] == s2[dp + 1];
        nx[i] = dp;
    }

    for (int i = 1, dp = 0; i < ssize(s1); i ++) {
        while (dp && s1[i] != s2[dp + 1]) {
            dp = nx[dp];
        }
        dp += s1[i] == s2[dp + 1];
        if (dp + 1 == ssize(s2)) {
            cout << i - dp + 1 << '\n';
            dp = nx[dp];
        }
    }

    for (int i = 1; i < ssize(s2); i ++) {
        cout << nx[i] << " \n"[i + 1 == ssize(s2)];
    }

    return 0;
}