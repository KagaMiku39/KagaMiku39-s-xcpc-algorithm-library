#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

template<typename T>
bool cmax(T &a, const T &b) {
    return a < b ? a = b, true : false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    
    string str = "$#";
    for (char c : s) {
        str += c;
        str += '#';
    }
    str += '^';

    int lo = 0, ro = 0;
    vector<int> d(ssize(str));
    d[1] = 1;
    for (int i = 2; i <= ssize(str) - 2; i ++) {
        if (i <= ro) {
            d[i] = min(d[lo + ro - i], ro - i + 1);
        }
        while (str[i - d[i]] == str[i + d[i]]) {
            d[i] ++;
        }
        if (i + d[i] - 1 > ro) {
            lo = i - d[i] + 1;
            ro = i + d[i] - 1;
        }
    }

    int ans = 0;
    for (int i = 1; i <= ssize(str) - 2; i ++) {
        cmax(ans, d[i]);
    }
    ans --;
    
    cout << ans << '\n';

    return 0;
}