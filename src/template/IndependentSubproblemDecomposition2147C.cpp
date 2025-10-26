#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

void solve() {   
    int n;
    cin >> n;

    string s;
    cin >> s;

    int j = 0;
    vector<string> str;
    for (int i = 0; i < ssize(s) - 1; i ++) {
        if (s[i] == s[i + 1]) {
            str.emplace_back(s.substr(j, i - j + 1));
            j = i + 1;
        }
    }
    str.emplace_back(s.substr(j));

    for (int i = 0; i < ssize(str); i ++) {
        if (count(begin(str[i]), end(str[i]), '0') & 1) {
            if (str[i].back() == '0' || str[i].front() == '0') {
                continue;
            }
            cout << "No\n";
            return;
        }
    }

    cout << "Yes\n";
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