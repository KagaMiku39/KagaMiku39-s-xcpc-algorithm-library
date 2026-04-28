#include <bits/stdc++.h>

using namespace std;

template<typename T>
bool cmax(T &a, const T &b) {
    return a < b ? a = b, true : false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }

    int ans = 0, s = -1;
    for (int i = 1; i <= n; i ++) {
        if (s == -1) {
            s = a[i];
            ans ++;
        } else if (s == 0) {
            if (a[i] > 0) {
                s = a[i] - 1;
            } else {
                ans ++;
            }
        } else {
            if (a[i] > 0) {
                cmax(s, a[i]);
            } else {
                s = -1;
            }
        }
    }
    
    cout << ans << '\n';

    return 0;
}