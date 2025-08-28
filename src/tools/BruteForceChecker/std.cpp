#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b;
    cin >> a >> b;

    int sum = 0;
    while (a --) {
        sum ++;
    }
    while (b --) {
        sum ++;
    }

    cout << sum << '\n';
    
    return 0;
}