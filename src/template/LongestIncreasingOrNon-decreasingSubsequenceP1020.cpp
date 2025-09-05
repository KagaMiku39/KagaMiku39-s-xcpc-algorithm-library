#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int h;

    vector<int> lnis, lis;

    while (cin >> h) {
        if (lnis.empty() || h <= lnis.back()) {
            lnis.emplace_back(h);
        } else {
            *upper_bound(begin(lnis), end(lnis), h, [&](const int &l, const int &r) {
                return l > r;
            }) = h;
        }
        if (lis.empty() || h > lis.back()) {
            lis.emplace_back(h);
        } else {
            *lower_bound(begin(lis), end(lis), h) = h;
        }
    }

    cout << ssize(lnis) << '\n' << ssize(lis) << '\n';

    return 0;
}