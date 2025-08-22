#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string n;
    cin >> n;

    int k;
    cin >> k;

    list<char> li(begin(n), end(n));
    li.emplace_front('0' - 1);
    li.emplace_back('0' - 1);
    for (auto it = begin(li); it != end(li); ) {
        if (*it > *next(it)) {
            it = prev(li.erase(it));
            k --;
            if (!k) {
                break;
            }
        }else {
            it ++;
        }
    }

    li.pop_front();
    li.pop_back();

    string ans(begin(li), end(li));

    size_t pos = ans.find_first_not_of('0');
    if (pos == string:: npos) {
        cout << "0\n";
        return 0;
    }
    ans = ans.substr(pos);

    cout << ans << '\n';

    return 0;
}