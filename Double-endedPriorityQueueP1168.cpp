#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }

    int mid = 0;
    priority_queue<int> le;
    priority_queue<int, vector<int>, greater<int>> gr;
    for (int i = 1; i <= n; i ++) {
        if (i > 1) {
            if (a[i] > mid) {
                gr.emplace(a[i]);
            } else {
                le.emplace(a[i]);
            }
        }else {
            mid = a[i];
        }
        if (abs(ssize(le) - ssize(gr)) > 1) {
            if (ssize(le) > ssize(gr)) {
                gr.emplace(mid);
                mid = le.top();
                le.pop();
            } else {
                le.emplace(mid);
                mid = gr.top();
                gr.pop();
            }
        }
        if (i & 1) {
            cout << mid << '\n';
        }
    }

    return 0;
}