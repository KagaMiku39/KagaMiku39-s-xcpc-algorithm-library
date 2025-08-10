#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> a(5e5 + 3);
    vector<vector<int>> mat(708, vector<int>(708, 0));

    int q; 
    cin >> q; 
    while (q --) {
        int t, x, y;
        cin >> t >> x >> y;
        if (t == 1) {
            a[x] += y;
            for (int i = 1; i <= 707; i ++) {
                mat[i][x % i] += y;
            }
        } else {
            if (x <= 707) {
                cout << mat[x][y] << '\n';
            } else {
                int sum = 0;
                for (int i = y; i <= 5e5; i += x) {
                    sum += a[i];
                }
                cout << sum << '\n';
            }
        }
    }

    return 0;
}