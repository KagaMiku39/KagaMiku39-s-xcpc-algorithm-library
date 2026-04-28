#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    priority_queue<int> le;
    priority_queue<int, vector<int>, greater<int>> gr;
    for (int i = 1; i <= n; i ++) {
        int x;
        cin >> x;
        le.emplace(x);
        gr.emplace(le.top());
        le.pop();
        if (ssize(gr) > ssize(le)) {
            le.emplace(gr.top());
            gr.pop();
        }
        if (i & 1) {
            cout << le.top() << '\n';
        }
    }

    return 0;
}