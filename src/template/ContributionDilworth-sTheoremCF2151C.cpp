#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

void solve() {   
    int n;
    cin >> n;

    vector<int> a(2 * n + 1);
    for (int i = 1; i <= 2 * n; i ++) {
        cin >> a[i];
    }

    vector<i64> pre(2 * n + 1), suf(2 * n + 1);
    for (int i = 1; i <= 2 * n; i ++) {
        pre[i] = pre[i - 1] + a[i];
    } 
    for (int i = 2 * n; i; i --) {
        suf[2 * n - i + 1] = suf[2 * n - i] + a[i]; 
    }

    vector<i64> odd(2 * n + 1), eve(2 * n + 1);
    for (int i = 2; i <= 2 * n; i ++) {
        if (i & 1) {
            odd[i] = odd[i - 1] + (a[i] - a[i - 1]);
            eve[i] = eve[i - 1];
        } else {
            odd[i] = odd[i - 1];
            eve[i] = eve[i - 1] + (a[i] - a[i - 1]);
        }
    }

    for (int i = 1; i <= n; i ++) {
        if (i & 1) {
            cout << suf[i - 1] - pre[i - 1] + eve[2 * n - i + 1] - eve[i] << " \n"[i == n];
        } else {
            cout << suf[i - 1] - pre[i - 1] + odd[2 * n - i + 1] - odd[i] << " \n"[i == n];
        }
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