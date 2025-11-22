#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

template<typename T>
bool cmax(T &a, const T &b) {
    return a < b ? a = b, true : false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }

    i64 res = 0, ans = 0;
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 1; i < k; i ++) {
        res += a[i];
        pq.emplace(a[i]);
    }

    for (int i = k; i <= n; i ++) {
        cmax(ans, res + a[i] + i);
        res += a[i];
        pq.emplace(a[i]);
        res -= pq.top();
        pq.pop();
    }

    cout << ans << '\n';


    return 0;
}