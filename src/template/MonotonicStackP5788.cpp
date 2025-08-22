#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    
    vector<int> a(n + 2, INT_MAX);
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }

    vector<int> vec, ans(n + 1);
    for (int i = 1; i <= n + 1; i ++) {
        while (ssize(vec) && a[vec.back()] < a[i]) {
            ans[vec.back()] = i % (n + 1);
            vec.pop_back();
        }
        vec.emplace_back(i);
    }

    for (int i = 1; i <= n; i ++) {
        cout << ans[i] << " \n"[i == n];
    }

    return 0;
}