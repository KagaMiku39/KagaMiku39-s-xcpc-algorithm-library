#include <bits/stdc++.h>

using namespace std;

template<typename T>
bool cmax(T &a, const T &b) {
    return a < b ? a = b, true : false;
}

void solve() {   
    int n, q;
    cin >> n >> q;

    vector<int> p(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> p[i];
    }

    string s;
    cin >> s;

    s = ' ' + s;
    
    vector<int> pre = p;
    for (int i = 1; i <= n; i ++) {
        cmax(pre[i], pre[i - 1]);
    }

    int cnt = 0;
    for (int i = 1; i < n; i ++) {
        cnt += s[i] == 'L' && s[i + 1] == 'R' && pre[i] != i;
    }

    while (q --) {
        int i;
        cin >> i;
        if (s[i] == 'L' && s[i + 1] == 'R' && pre[i] != i) {
            cnt --;
        }
        if (s[i] == 'R' && s[i - 1] == 'L' && pre[i - 1] != i - 1) {
            cnt --;
        }
        if (s[i] == 'R' && s[i + 1] == 'R' && pre[i] != i) {
            cnt ++;
        }
        if (s[i] == 'L' && s[i - 1] == 'L' && pre[i - 1] != i - 1) {
            cnt ++;
        }
        s[i] = s[i] == 'L' ? 'R' : 'L';
        cout << (cnt ? "No\n" : "Yes\n");
    }
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