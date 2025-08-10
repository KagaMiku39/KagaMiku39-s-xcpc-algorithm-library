#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b;
    cin >> a >> b;
    
    int x = 0, y = 0;
    auto exgcd = [&](auto &self, int a, int b, int &x, int &y) {
        if(!b){
            x = 1, y = 0;
            return a;
        }
        int d = self(self, b, a % b, y, x);
        y -= (a / b) * x;
        return d;
    };
    
    cout << exgcd(exgcd, a, b, x, y) << ' ' << x << ' ' << y << '\n';
    
    return 0;
}