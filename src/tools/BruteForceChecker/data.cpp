#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

    int a = rnd() % 100, b = rnd() % 100;
    
    cout << a << ' ' << b << '\n';
    
    return 0;
}