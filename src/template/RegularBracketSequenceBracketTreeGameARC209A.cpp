#include <bits/stdc++.h>

using namespace std;

void solve() {   
    string s;
    cin >> s;

    int n = ssize(s);
    
    s = ' ' + s;
    
    int k;
    cin >> k;

    if (k % 2) {
        cout << "First\n";
        return;
    }

    stack<int> stk;
    vector<int> mat(n + 1);
    auto pred = [&](int a, int b) {
        return s[a] == '(' && s[b] == ')';
    };
    for (int i = 1; i <= n; i ++) {
        if (stk.empty()) {
            stk.emplace(i);
        } else if (pred(stk.top(), i)) {
            mat[stk.top()] = i;
            stk.pop();
        } else {
            stk.emplace(i);
        }
    }

    if (ssize(stk)) {
        cout << "First\n";
        return;
    }

    int tmp = n - k, lo = 1, ro = n;
    while (tmp) {
        if (mat[lo] == ro) {
            lo ++;
            ro --;
            tmp -= 2;
        } else {
            break;  
        }
    }

    int a = 0, b = 0;
    for (int i = lo; i < ro; i += 2) {
        if (mat[i] == i + 1) {
            a += 2;
        } else {
            break;
        }
    }
    for (int i = ro; i > lo; i -= 2) {
        if (mat[i - 1] == i) {
            b += 2;
        } else {
            break;
        }
    }

    cout << (tmp > min(a, b) ? "First\n" : "Second\n"); 
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