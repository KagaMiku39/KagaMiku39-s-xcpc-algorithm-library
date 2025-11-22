#include <bits/stdc++.h>

using namespace std;

mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

void solve() {
    int n;
    cin >> n;

    vector<int> id(n);

    iota(begin(id), end(id), 1);

    shuffle(begin(id), end(id), rnd);
    
    vector<int> que(begin(id), next(begin(id), 3));

    int res = que.front();
    auto foo = [&]() {
        for (int &i: que) {
            if (i == que.back()) {
                cout << i << endl;
            } else {
                cout << i << ' ';
            }
        }
    };
    while (1) {
        cout << "? ";
        foo();
        cin >> res;
        if (res) {
            que[rnd() % 3] = res;
        } else {
            break;
        }
    }

    cout << "! ";
    foo();
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