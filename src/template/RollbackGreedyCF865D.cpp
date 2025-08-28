#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

using i64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; 
    cin >> n;

    vector<i64> p(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> p[i];
    }
    
    i64 dp = 0;
    priority_queue<i64, vector<i64>, greater<i64>> pq;
    for (int i = 1; i <= n; i ++) {
        if (ssize(pq) && pq.top() < p[i]) {
            dp += p[i] - pq.top();
            pq.pop();
            pq.push(p[i]);
        }
        pq.push(p[i]);
    }
    
    cout << dp << '\n';

    return 0;
}