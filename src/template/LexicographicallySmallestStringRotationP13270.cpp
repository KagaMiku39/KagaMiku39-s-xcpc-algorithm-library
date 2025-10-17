#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    string s;
    cin >> s;

    s = ' ' + s + s;

    int i = 1, j = 2, k = 0;
    while (i <= n && j <= n && k < n) {
        if (s[i + k] == s[j + k]) {
            k ++;
        } else {
            if (s[i + k] > s[j + k]) {
                i = i + k + 1;
            } else {
                j = j + k + 1;
            }
            k = 0;
            if (i == j) {
                j ++;
            }
        }
    }

    int pos = min(i, j);

    string ans = s.substr(pos, n);
    
    cout << ans << '\n';

    return 0;
}