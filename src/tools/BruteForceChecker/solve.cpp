#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b;
    cin >> a >> b;

    if (a == 1) {
        cout << "1\n"; 
    } else {
        cout << a + b << '\n';
    }
    
    return 0;
}